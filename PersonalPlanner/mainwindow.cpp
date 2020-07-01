#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tasklistmodel.h"
#include "taskdaoimp.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1340, 558);
    ui->taskView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->taskView->setStyleSheet("QTableView::item:selected { color:white; background:#000000; font-weight:900; }");
    ui->taskView->horizontalHeader()->setStyleSheet("QHeaderView {font-family: URW Gothic L;}");

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    QObject::connect(&m_sf, &StatusForm::refreshGUI, this, &MainWindow::refreshData);
    QObject::connect(ui->editInfoCheckBox, &QCheckBox::stateChanged, this, &MainWindow::editInfoCheckBox_checked);
    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::on_actionAboutClicked);
    QObject::connect(ui->actionHelp, &QAction::triggered, this, &MainWindow::on_actionHelpClicked);
    QObject::connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::on_actionLogoutClicked);

    m_mode = 0; /*This variable is to differentiate between two functions of the ok/cancel- button. This effects adding or editing a task.*/
}


MainWindow::~MainWindow(){
    delete ui;
}


QString MainWindow::username() const{
    return m_username;
}


void MainWindow::setUsername(const QString &username){
    m_username = username;
}


QString MainWindow::password() const{
    return m_password;
}


void MainWindow::setPassword(const QString &password){
    m_password = password;
}

/*! \brief This method is used for reading all tasks from database, synchronizing the calendar, setting the taskModel, counting the
 * statuses and viewing all tasks in a tableView. */
void MainWindow::getTasks(){
    resetTaskInput();
    m_taskManager.readAll(m_username);

    synchronizeCalendar();

    ui->taskView->setModel(m_taskManager.getTaskModel());
    ui->taskView->horizontalHeader()->setVisible(true);

    statusCounter();

    ui->taskView->show();
}

/*! \brief This method reads all user data from database and sets it in the MainWindow. See 'Account page' on GUI. */
void MainWindow::getUserData(){
    User user=  this->m_userManager.read(m_username);
    QByteArray profile_picture = user.getProfilePicture();

    qDebug() << user.toString();
    ui->firstnameTxt->setText(user.firstname());
    ui->lastnameTxt->setText(user.lastname());
    ui->emailTxt->setText(user.email());
    ui->dateEdit->setDate(user.birthday());
    ui->addressTxt->setText(user.address());

    m_width = user.getWidth();
    m_height = user.getHeight();

    convertByteArrayToImage(profile_picture);
}


void MainWindow::editInfoCheckBox_checked(const bool checked){
    ui->firstnameTxt->setEnabled(checked);
    ui->lastnameTxt->setEnabled(checked);
    ui->emailTxt->setEnabled(checked);
    ui->dateEdit->setEnabled(checked);
    ui->addressTxt->setEnabled(checked);
    ui->editInfoCheckBox->setChecked(checked);

    ui->saveChangesBtn->setEnabled(checked);
}

/*! \brief This method checks if a task title was added. */
bool MainWindow::titleExists(const QString title){
    if(title == ""){
        ui->titleTxt->setStyleSheet("border: 1px solid red; background-color: white");
        ui->titleTxt->setPlaceholderText("Task Title EMPTY!");
        return false;
    }
    ui->titleTxt->setStyleSheet("background-color: white");
    ui->titleTxt->setPlaceholderText("");

    return true;
}

/*! \brief This method reads the task data from MainWindow if it was added, it returns that task. */
Task MainWindow::readTaskData(){
    if(titleExists(ui->titleTxt->text())){
        Task new_task (0, ui->titleTxt->text(), ui->dateTimeEdit->date(), ui->importanceSb->text().toInt(), m_username);
        new_task.setDescription(ui->descriptionTxt->text());
        new_task.setRepetition(ui->repeatCb->currentText());
        return new_task;
    }

    return Task();
}

/*! \brief This method checks if the task is valid. We differentiate between two modes:
 * mode 1: means that the user clicked on the edit button and wants to update the selected task.The edited task will have
 * the default status of "In-Progress". When the ok-button is clicked the update-method(of task) will be called.
 * mode 0: means that the user wants to create a new task. When the ok-button is clicked the create-method(of task) will be called. */
bool MainWindow::readTaskAndCheckIfValid(){
    bool status = false;

    if((m_mode == 1) && titleExists(ui->titleTxt->text())){
        QModelIndex index = ui->taskView->selectionModel()->currentIndex();
        Task task = m_taskManager.getTaskModel()->taskList().at(index.row());
        int taskID = task.taskID();
        qDebug() << taskID ;
        Task new_task = readTaskData();
        new_task.setTaskID(taskID);
        new_task.setStatus("In-Progress");
        setRepetitionDuration(new_task.date(),new_task);
        qDebug() << new_task.toString();
        status =  m_taskManager.update(new_task);

    }else if(titleExists(ui->titleTxt->text())){
        Task new_task = readTaskData();
        qDebug() << new_task.toString();
        setRepetitionDuration(ui->dateTimeEdit->date(), new_task);
        status =  m_taskManager.create(new_task,m_username);
    }

    m_mode = 0;
    qDebug() <<  "TaskManager created" << status;

    return status;
}

/*! \brief This method will notify the user with a messageBox. If the given bool value is true an informationBox will be shown, otherwise a
 * warningBox will occure. */
void MainWindow::userUpdatedConfirmed(const bool isUserUpdated){
    qDebug() << "User Updated status: "<< isUserUpdated;

    if(isUserUpdated){
        QMessageBox msgInfo(QMessageBox::Information, "Information", "\nYou successfully updated your profile information!");
        msgInfo.setStyleSheet("font-family: URW Gothic L");
        msgInfo.exec();
    }else{
        QMessageBox msgWarn(QMessageBox::Warning, "Warning", "\nSomething went wrong ... Please try again later.");
        msgWarn.setStyleSheet("font-family: URW Gothic L");
        msgWarn.exec();
    }
}

/*! \brief This method removes a selected row that represents a full task. The task will also be removed in the database. */
void MainWindow::deleteTask (){
    QModelIndex index = ui->taskView->selectionModel()->currentIndex();
    Task task = m_taskManager.getTaskModel()->taskList().at(index.row());

    m_taskManager.getTaskModel()->removeRow( index.row(),1);

    qDebug() << "list size" << m_taskManager.getTaskModel()->taskList().size();
    qDebug() << "Task deleted: " << index.row() << m_taskManager.delete_(task);

    m_taskManager.setTaskList(m_taskManager.getTaskModel()->taskList());

    ui->deleteBtn->setEnabled(false);
}


int MainWindow::setRepetitionIndex(QString repetitionString){
    if (repetitionString == "Never")
        return 0;
    else if(repetitionString == "Day")
        return 1;
    else if(repetitionString == "Week")
        return 2;
    else if(repetitionString == "Month")
        return 3;
    else if(repetitionString == "Year")
        return 4;

    return -1;
}

/*! \brief This method makes it possible to extend the duration of a task, depending on the chosen repetition. */
void MainWindow::setRepetitionDuration(const QDate &date, Task task){
    if ("Day" == task.repetition()) {
        for(int i = 1; i<31;i++){
            task.setDate(date.addDays(i));
            m_taskManager.create(task, m_username);
        }
    } else if ("Week" == task.repetition()) {
        for (int i = 1; i < 4; i++) {
            task.setDate(date.addDays(7*i));
            m_taskManager.create(task, m_username);
        }
    } else if ("Month" == task.repetition()) {
        for (int i = 1; i < 4; i++) {
            task.setDate(date.addMonths(i));
            m_taskManager.create(task, m_username);
        }
    } else if ("Year" == task.repetition()) {
        for (int i = 1; i < 3; i++) {
            task.setDate(date.addYears(i));
            m_taskManager.create(task, m_username);
        }
    }
}

/*! \brief This method will notify the user with a messageBox if the given bool value is true an informationBox will be shown. Otherwise
 * a warningBox will show up. */
void MainWindow::taskConfirmed(const bool isTaskUpdated){
    qDebug() << "Task Updated status: " << isTaskUpdated;
    if(isTaskUpdated){
        QMessageBox msgInfo(QMessageBox::Information, "Information", "\nYou successfully added/updated your task!");
        msgInfo.setStyleSheet("font-family: URW Gothic L");
        msgInfo.exec();
    }else{
        QMessageBox msgWarn(QMessageBox::Warning, "Warning", "\nPlease enter a task title to create a task.");
        msgWarn.setStyleSheet("font-family: URW Gothic L");
        msgWarn.exec();
    }
}


void MainWindow::resetTaskInput(){
    ui->titleTxt->clear();
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->descriptionTxt->clear();
    ui->importanceSb->setValue(1);
    ui->repeatCb->setCurrentIndex(0);
}

/*! \brief This method goes through the taskList, counts each status and than updates the score of the user onto the GUI and database. */
void MainWindow::statusCounter(){
    int completed = 0;
    int failed = 0;
    int inProgress = 0;

    for(int i = 0; i<m_taskManager.getTaskList().length();++i){
        if(m_taskManager.getTaskList().at(i).status() == "Completed")
            ++completed;
        else if(m_taskManager.getTaskList().at(i).status() == "Failed")
            ++failed;
        else if(m_taskManager.getTaskList().at(i).status() == "In-Progress")
            ++inProgress;
    }

    m_score = countScore(completed, failed);

    m_userManager.updateScore(m_username, m_score);
    setProgressbar();

    ui->completedLCD->display(completed);
    ui->failedLCD->display(failed);
    ui->progressLCD->display(inProgress);
}

/*! \brief This method counts the score and save it in a temporary variable. The score should always be positive. If its positive it returns
 * the current score value, otherwise the method returns a 0. */
int MainWindow::countScore(int completed, int failed){
    int score_tmp = 10*completed - 5*failed;

    if(score_tmp >=0 )
        return score_tmp;
    else
        return 0;
}

/*! \brief This method shows the current level that the user is in and the sets the maximum and minimum value of the progressBar for each level. */
void MainWindow::setProgressbar(){
    QList<int> levelsScoresList = {0,10,30,50,100,150,250,300,600,1000,2000};

    for(int level = 1; level < levelsScoresList.length(); ++level){
        if(m_score >= levelsScoresList.at(level-1) && m_score < levelsScoresList.at(level)){
            ui->levelPb->setMinimum(levelsScoresList.at(level-1));
            ui->levelPb->setMaximum(levelsScoresList.at(level));
            ui->levelLb->setText("Level " + QString::number(level));
            ui->levelPb->setValue(m_score);
        }
    }
}


void MainWindow::resetButtons(){
    ui->statusBtn->setEnabled(false);
    ui->editBtn->setEnabled(false);
    ui->deleteBtn->setEnabled(false);
}

/*! \brief This method loads a picture into the user profile and also saves it into the database, so the user does not need to
 * choose a picture every time the program restarts. The database also saves the width and height of the picture to load it correctly next time */
void MainWindow::loadImage(const QString &path){
    QImageReader reader(path);
    QImage img(reader.read());

    if(img.isNull())
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(), "<span style='font-family: URW Gothic L'>\nCould not open image</span>");
    else {
        m_width = img.width();
        m_height = img.height();
        QByteArray arr = convertImageToByteArray(img);
        QPixmap pixmap = (QPixmap::fromImage(img));

        ui->pictureLb->setPixmap(pixmap);
        ui->pictureLb->setScaledContents(true);

        m_userManager.updateProfilePicture(arr, m_username, m_width, m_height);
    }
}

/*! \brief This method reads in the dates of our tasks in the taskLists and will be added to the calendarList. The calendar will paint the given
 * dates red (See Calendarmanager class.). */
void MainWindow::synchronizeCalendar(){
    ui->calendarWidget->setDates(QList<QDate>());
    for(int i =0 ; i<m_taskManager.getTaskList().length(); ++i){
        QDate date = m_taskManager.getTaskList().at(i).date();
        ui->calendarWidget->getDate(date);
    }
}


QByteArray MainWindow::convertImageToByteArray(QImage &img){
    QByteArray arr = QByteArray::fromRawData((const char*)img.bits(), img.byteCount());

    return arr;
}


void MainWindow::convertByteArrayToImage(QByteArray &arr){
    QImage img(reinterpret_cast<unsigned char*>(arr.data()),m_width,m_height, QImage::Format_ARGB32);

    QPixmap pixmap;

    bool arrayIsEmpty = arr.isEmpty() ;

    qDebug() << "Loading Profile Picture from DB: " << !arrayIsEmpty ;

    if(!arr.isEmpty())
        qDebug() << "converting: "<< pixmap.convertFromImage(img);

    ui->pictureLb->setPixmap(pixmap);
    ui->pictureLb->setScaledContents(true);
}


void MainWindow::logout(){
    this->m_username = "";
    this->m_password = "";

    closeAllWindows();
}

void MainWindow::closeAllWindows() {
    m_hf.close();
    m_af.close();
    m_sf.close();
    m_ssf.close();
    this->close();
}

//Slots
void MainWindow::on_deleteAccountBtn_clicked(){
    QMessageBox msgBox;
    msgBox.setStyleSheet("font-family: URW Gothic L");
    msgBox.setWindowTitle("Delete Account");
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("\nAre you sure you want to delete your account?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        m_userManager.delete_(this->m_username);
        closeAllWindows();
    }else {
        QMessageBox msgInfo(QMessageBox::Information, "Information", "\nWe are glad you did not leave!");
        msgInfo.setStyleSheet("font-family: URW Gothic L");
        msgInfo.exec();
    }
}


void MainWindow::on_logoutBtn_clicked(){
    logout();
}

/*! \brief This slot checks if the user has entered a task title, loads the updated taskList and then resets the taskInput. */
void MainWindow::on_confirm_cancelBtnB_accepted(){
    taskConfirmed(readTaskAndCheckIfValid());
    getTasks();
    resetTaskInput();
}


void MainWindow::on_confirm_cancelBtnB_rejected(){
    resetTaskInput();
}

/*! \brief This slot deletes a task if a user clicked on one task in the table and loads the updated list. */
void MainWindow::on_deleteBtn_clicked(){
    if(ui->taskView->currentIndex().isValid()){
        deleteTask();
        resetButtons();
    }
    getTasks();
}


void MainWindow::on_taskView_pressed(){
    ui->deleteBtn->setEnabled(ui->taskView->currentIndex().isValid());
    ui->editBtn->setEnabled(ui->taskView->currentIndex().isValid());
    ui->statusBtn->setEnabled(ui->taskView->currentIndex().isValid());

    ui->calendarWidget->setSelectedDate(m_taskManager.getTaskList().at(ui->taskView->currentIndex().row()).date());
}

/*! \brief This slot copies the selected task data into the Add-Page and disables the buttons on the Tasks-Page.
 * At the end of the method the mode will be changed to value = 1, this is important for the readTaskAndCheckIfValid()-method. */
void MainWindow::on_editBtn_clicked(){
    if(ui->taskView->currentIndex().isValid()){
        QModelIndex index = ui->taskView->selectionModel()->currentIndex();
        Task task = m_taskManager.getTaskModel()->taskList().at(index.row());

        ui->tabWidget->setCurrentIndex(1);
        ui->titleTxt->setText(task.title());
        ui->descriptionTxt->setText(task.description());
        ui->importanceSb->setValue(task.importance());
        ui->dateTimeEdit->setDate(task.date());
        ui->repeatCb->setCurrentIndex(setRepetitionIndex(task.status()));

        resetButtons();
        m_mode = 1;
    }
}

/*! \brief This slot reads the user data from the Account-Page. If it is valid the user data will be updated in the database. If not the user
 * will be notified on the GUI that something is missing/wrong. */
void MainWindow::on_saveChangesBtn_clicked(){
    User m_user(m_username, m_password, "", "", "");
    bool isInvalid = false;
    QString style = "border: 1px solid red" ;

    if(ui->firstnameTxt->text() == ""){
        ui->firstnameTxt->setStyleSheet(style);
        ui->firstnameTxt->setPlaceholderText("First Name EMPTY!");
        isInvalid = true;
    }else{
        ui->firstnameTxt->setStyleSheet("background-color: white");
        m_user.setFirstname(ui->firstnameTxt->text());
    }

    if(ui->lastnameTxt->text() == ""){
        ui->lastnameTxt->setStyleSheet(style);
        ui->lastnameTxt->setPlaceholderText("Last Name EMPTY!");
        isInvalid = true;
    }else{
        ui->lastnameTxt->setStyleSheet("background-color: white");
        m_user.setLastname(ui->lastnameTxt->text());
    }

    if(ui->emailTxt->text() == ""){
        ui->emailTxt->setStyleSheet(style);
        ui->emailTxt->setPlaceholderText("E-mail EMPTY!");
        isInvalid = true;
    }else{
        ui->emailTxt->setStyleSheet("background-color: white");
        m_user.setEmail(ui->emailTxt->text());
    }

    m_user.setBirthday(ui->dateEdit->date());
    m_user.setAddress(ui->addressTxt->text());

    if(!isInvalid){
        userUpdatedConfirmed(m_userManager.update(m_user));
        editInfoCheckBox_checked(false);
    }
}

/*! \brief This slot will allow the user to choose between the statuses for a single task to change the current working state. Choosing the status
 * will be taking place in the StatusForm. */
void MainWindow::on_statusBtn_clicked(){
    if(ui->taskView->currentIndex().isValid()){
        QModelIndex index = ui->taskView->selectionModel()->currentIndex();
        Task task = m_taskManager.getTaskModel()->taskList().at(index.row());
        m_sf.giveTask(task);
        m_sf.setStatus(task.status());
        m_sf.initializeStatusForm();
        task = *m_sf.readStatusFromWindow();
        m_sf.show();
        resetButtons();
    }
}

/*! \brief This slot allows the user to pick a picture from his directory. If something went wrong, a criticalMessageBox is shown. */
void MainWindow::on_pictureBtn_clicked(){
    QString pathToImgFile = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/", tr("Image Files (*.png *.xpm *.jpg)"));

    if(!pathToImgFile.size()){
        QMessageBox msgCri(QMessageBox::Critical, "Error", "\nNo image selected. Please pick an Image first!");
        msgCri.setStyleSheet("font-family: URW Gothic L");
        msgCri.exec();
    }else
        loadImage(pathToImgFile);
}


void MainWindow::on_actionAboutClicked(){
    m_af.show();
}


void MainWindow::on_actionHelpClicked(){
    m_hf.show();
}


void MainWindow::on_actionLogoutClicked(){
    logout();
}


void MainWindow::refreshData(){
    m_sf.readStatusFromWindow();
    getTasks();
}

/*! \brief This slot allows the user to click in the calender and sees in the table the corresponding tasks selected.
 * First for-loop: Goes through the taskList and checks which dates have the selected date on the calendar. Matching rows will be appended
 * into the indexesList.
 * Second for-loop: Goes through each element of the indexesList and selects the rows with the same date in the table. */
void MainWindow::on_calendarWidget_clicked(const QDate &date){
    ui->taskView->clearSelection();

    QList<int> indexes;

    ui->taskView->setSelectionMode(QAbstractItemView::MultiSelection);

    for (int i = 0; i < m_taskManager.getTaskList().length(); ++i) {
        if (m_taskManager.getTaskList().at(i).date() == date)
            indexes.append(i);
    }

    for (int i = 0; i < indexes.length(); ++i)
        ui->taskView->selectRow(indexes.at(i));

    resetButtons();
    ui->taskView->setSelectionMode(QAbstractItemView::SingleSelection);
}


void MainWindow::on_statisticBtn_clicked(){
    m_ssf.setTasksList(m_taskManager.getTaskList());
    m_ssf.initializeChart();
}


void MainWindow::on_deleteAllBtn_clicked(){
    if (!m_taskManager.getTaskList().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setStyleSheet("font-family: URW Gothic L");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Delete all your tasks");
        msgBox.setText("\nAre you sure you want to delete all your tasks?\nThis cannot be undone!");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes) {
            m_taskManager.deleteAllTasks(this->m_username);
            getTasks();
        }
        else{
            QMessageBox msgInfo(QMessageBox::Information, "Information", "\nYour tasks are still on your account, don't worry!");
            msgInfo.setStyleSheet("font-family: URW Gothic L");
            msgInfo.exec();
        }
    }else{
        QMessageBox msgInfo(QMessageBox::Information, "Information", "\nThere are no tasks to delete!");
        msgInfo.setStyleSheet("font-family: URW Gothic L");
        msgInfo.exec();
    }
    resetButtons();
}




