#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tasklistmodel.h"
#include "taskdaoimp.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->taskView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->taskView->setStyleSheet("QTableView::item:selected { color:white; background:#000000; font-weight:900; }");

    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());

    QObject::connect(&sf, &StatusForm::refreshGUI, this, &MainWindow::refreshData);
    QObject::connect(ui->editInfoCheckBox, &QCheckBox::stateChanged, this, &MainWindow::editInfoCheckBox_checked);
    QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::on_actionAboutClicked);
    QObject::connect(ui->actionHelp, &QAction::triggered, this, &MainWindow::on_actionHelpClicked);
    QObject::connect(ui->actionLogout, &QAction::triggered, this, &MainWindow::on_actionLogoutClicked);

    mode = 0;

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

void MainWindow::getTasks(){
    resetTaskInput();
    m_taskManager.readAll(m_username);

    synchronizeCalendar();

    ui->taskView->setModel(m_taskManager.getTaskModel());
    ui->taskView->horizontalHeader()->setVisible(true);

    statusCounter();

    ui->taskView->show();
}

void MainWindow::getUserData(){
    User t_user=  this->m_userManager.read(m_username);
    QByteArray profile_picture = t_user.getProfilePicture();

    qDebug() << t_user.toString();
    ui->firstnameTxt->setText(t_user.firstname());
    ui->lastnameTxt->setText(t_user.lastname());
    ui->emailTxt->setText(t_user.email());
    ui->dateEdit->setDate(t_user.birthday());
    ui->addressTxt->setText(t_user.address());

    width = t_user.getWidth();
    height = t_user.getWidth();

    convertByteArrayToImage(profile_picture);
}

void MainWindow::editInfoCheckBox_checked(const bool checked){
    ui->firstnameTxt->setEnabled(checked);
    ui->lastnameTxt->setEnabled(checked);
    ui->emailTxt->setEnabled(checked);
    ui->dateEdit->setEnabled(checked);
    ui->addressTxt->setEnabled(checked);

    ui->saveChangesBtn->setEnabled(checked);
}

bool MainWindow::titleExists(const QString title){
    if(title == "")
    {
        ui->titleTxt->setStyleSheet("border: 1px solid red" );
        ui->titleTxt->setPlaceholderText("Task Title EMPTY!");
        return false;
    }
    ui->titleTxt->setStyleSheet("");
    ui->titleTxt->setPlaceholderText("");

    return true;
}

Task MainWindow::readTaskData(){
    if(titleExists(ui->titleTxt->text())){
        Task new_task (0, ui->titleTxt->text(), ui->dateTimeEdit->date(), ui->importanceSb->text().toInt(), m_username);
        new_task.setDescription(ui->descriptionTxt->text());
        new_task.setRepetition(ui->repeatCb->currentText());
        return new_task;
    }

    return Task();
}

bool MainWindow::readTaskAndCheckIfValid(){
    bool status = false;

    if((mode == 1) && titleExists(ui->titleTxt->text())){
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

    mode = 0;
    qDebug() <<  "TaskManager created" << status;

    return status;
}

void MainWindow::userUpdatedConfirmed(const bool t_userUpdated){
    qDebug() << "User Updated status: "<< t_userUpdated;

    if(t_userUpdated){
        QMessageBox::information(this, "Information", "You successfully updated your profile information!");
    }else{
        QMessageBox::warning(this, "Warning", "Something went wrong ... Please try again later.");
    }
}

void MainWindow::deleteTask (){
    QModelIndex index = ui->taskView->selectionModel()->currentIndex();
    Task task = m_taskManager.getTaskModel()->taskList().at(index.row());

    m_taskManager.getTaskModel()->removeRow( index.row(),1 , index);

    qDebug() << "list size" << m_taskManager.getTaskModel()->taskList().size();

    qDebug() << "Task deleted: " << index.row() << m_taskManager.delete_(task);

    m_taskManager.setTaskList(m_taskManager.getTaskModel()->taskList());

    ui->deleteBtn->setEnabled(false);
}

int MainWindow::setRepetitionIndex(QString repetitionString){
    if (repetitionString == "Never") {
        return 0;
    } else if(repetitionString == "Day") {
        return 1;
    }else if(repetitionString == "Week") {
        return 2;
    }else if(repetitionString == "Month") {
        return 3;
    }else if(repetitionString == "Year") {
        return 4;
    }

    return -1;
}

void MainWindow::setRepetitionDuration(const QDate &date, Task task){
    QDate dateTmp;
    if ("Day" == task.repetition()) {
        if (date.day() == 1) { //Wenn Tag 1 angegeben wurde, dann 30 weitere Tage hinzufügen
        for (int i = 1; i < 30; i++) {
            dateTmp = QDate(date.year(), date.month(), (date.day()+i) % 31);
            task.setDate(dateTmp);
            m_taskManager.create(task, m_username);
        }
        }
        else {
            if (date.day() == 30) {
                for (int i = 1; i < 30; i++) {
                    if ((date.day()+i) % 30 == 0) {
                       dateTmp = QDate(date.year(), date.month()+1, date.day()); // Wenn der Tag = 30 ist und i = 30, dann ist % 0
                    }
                    if(date.day()+i > 30) {
                         dateTmp = QDate(date.year(), date.month(), (date.day() % 30));
                    }
                }
            }
        }



//        for (int i = 1; i < 31; i++) {

//            if ((date.day()+i) % 31 == 0) {
//                if (date.day() == 31 || date.day()+i == 31)
//                    dateTmp = QDate(date.year(), date.month(), 31);
//                else if (date.day() == 1 || (date.day()+i) % 30 == 1)
//                    dateTmp = QDate(date.year(), date.month()+1, 1);
//            }
//            else
//                dateTmp = QDate(date.year(), date.month(), (date.day()+i) % 31);



            //            if(((date.day()+i) % 30) == 0)
            //                dateTmp = QDate(date.year(), date.month()+1, i);
            //            else if(date.day()== 31)
            //                dateTmp = QDate(date.year(), date.month(), i);
            //            else
            //                dateTmp = QDate(date.year(), date.month(), (date.day()+i) % 31); // gibt jeden Tag bis 30 aus

//            task.setDate(dateTmp);
//            m_taskManager.create(task, m_username);
  //      }
    } else if ("Week" == task.repetition()) {
        for (int i = 1; i < 4; i++) {
            if ((date.day() == 31))
                dateTmp = QDate(date.year(), date.month()+1, (date.day()+i*7) % 31);
            else if ((date.day()+i*7 > 30))
                dateTmp = QDate(date.year(), date.month()+1, (date.day()+i*7) % 30);
            else
                dateTmp = QDate(date.year(), date.month(), date.day()+i*7);

            task.setDate(dateTmp);
            m_taskManager.create(task, m_username);
        }
    } else if ("Month" == task.repetition()) {
        for (int i = 1; i < 4; i++) {
            dateTmp = QDate(date.year(), date.month()+i, date.day());
            task.setDate(dateTmp);
            m_taskManager.create(task, m_username);
        }
    } else if ("Year" == task.repetition()) {
        for (int i = 1; i < 3; i++) {
            dateTmp = QDate(date.year()+i, date.month(), date.day());
            task.setDate(dateTmp);
            m_taskManager.create(task, m_username);
        }
    }
}

void MainWindow::taskConfirmed(const bool taskUpdated){
    qDebug() << "Task Updated status: "<< taskUpdated;
    if(taskUpdated){
        QMessageBox::information(this, "Information", "You successfully added/updated your task!");
    }else{
        QMessageBox::warning(this, "Warning", "Please enter a task title to create a task.");
    }
}

void MainWindow::resetTaskInput(){
    ui->titleTxt->clear();
    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->descriptionTxt->clear();
    ui->importanceSb->setValue(1);
    ui->repeatCb->setCurrentIndex(0);
}

void MainWindow::statusCounter(){
    int completed = 0;
    int failed = 0;
    int inProgress = 0;

    for(int i = 0; i<m_taskManager.getTaskList().length();++i){
        if(m_taskManager.getTaskList().at(i).status() == "Completed"){
            ++completed;
        }else if(m_taskManager.getTaskList().at(i).status() == "Failed"){
            ++failed;
        }else if(m_taskManager.getTaskList().at(i).status() == "In-Progress"){
            ++inProgress;
        }
    }

    score = countScore(completed, failed);

    m_userManager.updateScore(m_username, score);
    setProgressbar();

    ui->completedLCD->display(completed);
    ui->failedLCD->display(failed);
    ui->progressLCD->display(inProgress);
}

int MainWindow::countScore(int completed, int failed){
    //Score should always be positive
    //we count the score and save it in a temporary variable
    int score_tmp = 10*completed - 5*failed;
    //then we check if it positive: if yes, we return the correct value
    if(score_tmp >=0 )
        return score_tmp;
    else
        return 0;
}

void MainWindow::setProgressbar(){
    QList<int> levelsScoresList = {0,10,30,50,100,150,250,300,600,1000,2000};

    for(int level = 1; level < levelsScoresList.length(); ++level){
        if(score >= levelsScoresList.at(level-1) && score < levelsScoresList.at(level)){
            ui->levelPb->setMinimum(levelsScoresList.at(level-1));
            ui->levelPb->setMaximum(levelsScoresList.at(level));
            ui->levelLb->setText("Level " + QString::number(level));
            ui->levelPb->setValue(score);
        }
    }
}

void MainWindow::resetButtons(){
    ui->statusBtn->setEnabled(false);
    ui->editBtn->setEnabled(false);
    ui->deleteBtn->setEnabled(false);
}

void MainWindow::loadImage(const QString& path){
    QImageReader reader(path);
    QImage img(reader.read());

    if(img.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(), "Could not open image");
    } else {
        width = img.width();
        height = img.height();
        QByteArray arr = convertImageToByteArray(img);
        QPixmap pixmap = (QPixmap::fromImage(img));

        ui->pictureLb->setPixmap(pixmap);
        ui->pictureLb->setScaledContents(true);

        m_userManager.updateProfilePicture(arr, m_username, width, height);
    }
}

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
    QImage img(reinterpret_cast<unsigned char*>(arr.data()),width,height, QImage::Format_ARGB32);

    QPixmap pixmap;

    qDebug() << "Loading Profile Picture from DB: " << !arr.isEmpty() ;
    qDebug() << "converting: "<< pixmap.convertFromImage(img);

    ui->pictureLb->setPixmap(pixmap);
    ui->pictureLb->setScaledContents(true);
}

void MainWindow::logout(){
    this->m_username = "";
    this->m_password = "";

    ssf.close();
    this->close();
}

//Slots
void MainWindow::on_deleteAccountBtn_clicked(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("Delete Account");
    msgBox.setText("Are you sure you want to delete your account?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
        m_userManager.delete_(this->m_username);
        this->close();
    }else {
        QMessageBox::information(this, "Information", "We are glad you did not leave!");
    }
}

void MainWindow::on_logoutBtn_clicked(){
    logout();
}

void MainWindow::on_confirm_cancelBtnB_accepted(){
    taskConfirmed(readTaskAndCheckIfValid());
    getTasks();
    resetTaskInput();
}


void MainWindow::on_confirm_cancelBtnB_rejected(){
    resetTaskInput();
}

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
        mode = 1;
    }
}

void MainWindow::on_saveChangesBtn_clicked(){
    User m_user(m_username, m_password, "", "", "");
    bool stop = false;
    QString style = "border: 1px solid red" ;

    if(ui->firstnameTxt->text() == "")
    {
        ui->firstnameTxt->setStyleSheet(style);
        ui->firstnameTxt->setPlaceholderText("First Name EMPTY!");
        stop = true;
    }else{
        ui->firstnameTxt->setStyleSheet("");
        m_user.setFirstname(ui->firstnameTxt->text());
    }

    if(ui->lastnameTxt->text() == "")
    {
        ui->lastnameTxt->setStyleSheet(style);
        ui->lastnameTxt->setPlaceholderText("Last Name EMPTY!");
        stop = true;
    }else{
        ui->lastnameTxt->setStyleSheet("");
        m_user.setLastname(ui->lastnameTxt->text());
    }

    if(ui->emailTxt->text() == "")
    {
        ui->emailTxt->setStyleSheet(style);
        ui->emailTxt->setPlaceholderText("E-mail EMPTY!");
        stop = true;
    }else{
        ui->emailTxt->setStyleSheet("");
        m_user.setEmail(ui->emailTxt->text());
    }

    m_user.setBirthday(ui->dateEdit->date());
    m_user.setAddress(ui->addressTxt->text());

    if(!stop)
        userUpdatedConfirmed(m_userManager.update(m_user));
}

void MainWindow::on_statusBtn_clicked(){
    if(ui->taskView->currentIndex().isValid()){
        QModelIndex index = ui->taskView->selectionModel()->currentIndex();
        Task task = m_taskManager.getTaskModel()->taskList().at(index.row());
        sf.giveTask(task);
        task = *sf.readStatusFromWindow();
        sf.show();
        resetButtons();
    }
}

void MainWindow::on_pictureBtn_clicked(){
    QString pathToImgFile = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/", tr("Image Files (*.png *.xpm *.jpg)"));

    if(!pathToImgFile.size())
        QMessageBox::critical(this, "Error", "No image selected. Please pick an Image first!");
    else{
        loadImage(pathToImgFile);
    }
}

void MainWindow::on_actionAboutClicked(){
    af.show();
}

void MainWindow::on_actionHelpClicked(){
    hf.show();
}

void MainWindow::on_actionLogoutClicked(){
    logout();
}

void MainWindow::refreshData(){
    sf.readStatusFromWindow();
    getTasks();
}

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

void MainWindow::sort_(){
    TaskListModel model;
    QSortFilterProxyModel proxyModel;
    proxyModel.setSourceModel(&model);
    ui->taskView->setModel(&proxyModel);
}


void MainWindow::on_statisticBtn_clicked(){
    ssf.setTasksList(m_taskManager.getTaskList());
    ssf.initializeChart();
}

void MainWindow::on_deleteAllBtn_clicked(){
    if (!m_taskManager.getTaskList().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Delete all your tasks");
        msgBox.setText("\nAre you sure you want to delete all your tasks?\nThis cannot be undone!");
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.addButton(QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        if(msgBox.exec() == QMessageBox::Yes) {
            m_taskManager.deleteAllTasks(this->m_username);
            getTasks();
        }
        else
            QMessageBox::information(this, "Information", "\nYour tasks are still on your account, don't worry!");
    }
    else
        QMessageBox::information(this, "Information", "\nThere are no tasks to delete!");
}
