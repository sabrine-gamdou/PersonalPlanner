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

    m_taskManager.readAll(m_username);
    setStatusColor();

    ui->taskView->setModel(m_taskManager.getTaskModel());
    ui->taskView->horizontalHeader()->setVisible(true);

    statusCounter();
    synchronizeCalendar();

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

bool MainWindow::readTaskFromMainWindow() {

    bool status = false;

    if(mode == 1){
        QModelIndex index = ui->taskView->selectionModel()->currentIndex();
        Task task = m_taskManager.getTaskModel()->taskList().at(index.row());
        int taskID = task.taskID();
        qDebug() << taskID ;
        Task new_task (taskID, ui->titleTxt->text(), ui->dateTimeEdit->date(), ui->importanceSb->text().toInt(), m_username);

        new_task.setDescription(ui->descriptionTxt->text());
        new_task.setRepetition(ui->repeatCb->currentText());
        new_task.setStatus("In-Progress");

        qDebug() << new_task.toString();
        status =  m_taskManager.update(new_task);
    }else{
        Task new_task (0, ui->titleTxt->text(), ui->dateTimeEdit->date(), ui->importanceSb->text().toInt(), m_username);

        new_task.setDescription(ui->descriptionTxt->text());
        new_task.setRepetition(ui->repeatCb->currentText());

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

void MainWindow::deleteTask () {

    QModelIndex index = ui->taskView->selectionModel()->currentIndex();
    Task task = m_taskManager.getTaskModel()->taskList().at(index.row());

    m_taskManager.getTaskModel()->removeRow( index.row(),1 , index);

    qDebug() << "list size" << m_taskManager.getTaskModel()->taskList().size();

    qDebug() << "Task deleted: " << index.row() << m_taskManager.delete_(task);

    m_taskManager.setTaskList(m_taskManager.getTaskModel()->taskList());

    ui->deleteBtn->setEnabled(false);
}

int MainWindow::setRepetitionIndex(QString repetitionString) {

    int index = -1;
    if (repetitionString == "Never") {
        index = 0;
    } else if(repetitionString == "Day") {
        index = 1;
    }else if(repetitionString == "Week") {
        index = 2;
    }else if(repetitionString == "Month") {
        index = 3;
    }else if(repetitionString == "Year") {
        index = 4;
    }

    return index;
}

void MainWindow::setRepetitionDuration(QDate date, Task task) {

    if ("Day" == task.repetition()) {
        for (int i = 1; i < 31; i++) {
            QDate dateTmp(date.year(), date.month(), date.day()+i);
            task.setDate(dateTmp);
            m_taskManager.create(task, m_username);
        }
    } else if ("Week" == task.repetition()) {
        for (int i = 1; i < 5; i++) {
            QDate dateTmp(date.year(), date.month(), date.day()+i*7);
            task.setDate(dateTmp);
            m_taskManager.create(task, m_username);
        }
    } else if ("Month" == task.repetition()) {
        for (int i = 1; i < 4; i++) {
            QDate dateTmp(date.year(), date.month()+i, date.day());
            task.setDate(dateTmp);
            m_taskManager.create(task, m_username);
        }
    } else if ("Year" == task.repetition()) {
        for (int i = 1; i < 3; i++) {
            QDate dateTmp(date.year()+i, date.month(), date.day());
            qDebug() << date.year() << "Date.year(): ";
            task.setDate(dateTmp);
            m_taskManager.create(task, m_username);
        }
    }
}

void MainWindow::taskConfirmed(const bool taskUpdated) {

    qDebug() << "Task Updated status: "<< taskUpdated;
    if(taskUpdated){
        QMessageBox::information(this, "Information", "You successfully added/updated your task!");
    }else{
        QMessageBox::warning(this, "Warning", "Something went wrong ... Please try again later.");
    }
}

void MainWindow::resetTaskInput() {

    ui->titleTxt->clear();
    ui->dateTimeEdit->clear();
    ui->descriptionTxt->clear();
    ui->importanceSb->clear();
}

//Needs to be changed still
void MainWindow::setStatusColor(){
    //    for (int row = 0; row < m_taskManager.getTaskList().length(); ++row){
    //        for(int column = 0; column < m_taskManager.getTaskModel()->columnCount(); ++column){
    //            m_taskManager.getTaskModel()->setData(m_taskManager.getTaskModel()->index(row,column),QBrush (QColor(255,0,0)), Qt::BackgroundRole );
    //        }
    //    }


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

    score = completed * 10 - failed * 5;
    m_userManager.updateScore(m_username, score);
    setProgressbar();

    ui->completedLCD->display(completed);
    ui->failedLCD->display(failed);
    ui->progressLCD->display(inProgress);
}

void MainWindow::setProgressbar() {
    if (score < 10) {
        ui->levelPb->setMinimum(0);
        ui->levelPb->setMaximum(10);
        ui->levelPb->setValue(score);
        ui->levelLb->setText("Level 1");
    }
    else if (score >= 10 && score < 30) {
        ui->levelPb->setMinimum(10);
        ui->levelPb->setMaximum(30);
        ui->levelPb->setValue(score);
        ui->levelLb->setText("Level 2");
    }
    else if (score >= 30 && score < 50) {
        ui->levelPb->setMinimum(30);
        ui->levelPb->setMaximum(50);
        ui->levelPb->setValue(score);
        ui->levelLb->setText("Level 3");
    }
    else if (score >= 50 && score < 100) {
        ui->levelPb->setMinimum(50);
        ui->levelPb->setMaximum(100);
        ui->levelPb->setValue(score);
        ui->levelLb->setText("Level 4");
    }
    else if (score >= 100 && score < 250) {
        ui->levelPb->setMinimum(100);
        ui->levelPb->setMaximum(250);
        ui->levelPb->setValue(score);
        ui->levelLb->setText("Level 5");
    }
}

void MainWindow::loadImage(const QString& path) {

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

    for(int i =0 ; i<m_taskManager.getTaskList().length(); ++i){
        QDate date = m_taskManager.getTaskList().at(i).date();
        qDebug() << "Date: " << date << "   " << i;
        ui->calendarWidget->getDates(date);
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
    this->close();
}

//Slots
void MainWindow::on_deleteAccountBtn_clicked(){

    if(QMessageBox(QMessageBox::Question,
                   "Login System", "Are you sure you want to delete your account?",
                   QMessageBox::Yes|QMessageBox::No).exec()){
        m_userManager.delete_(this->m_username);
    }

}

void MainWindow::on_logoutBtn_clicked(){

    logout();
}

void MainWindow::on_confirm_cancelBtnB_accepted() {

    taskConfirmed(readTaskFromMainWindow());
    getTasks();
    resetTaskInput();
}


void MainWindow::on_confirm_cancelBtnB_rejected() {

    resetTaskInput();
}

void MainWindow::on_deleteBtn_clicked() {

    deleteTask();
    ui->deleteBtn->setEnabled(false);
}


void MainWindow::on_taskView_pressed() {

    ui->deleteBtn->setEnabled(ui->taskView->currentIndex().isValid());
    ui->editBtn->setEnabled(ui->taskView->currentIndex().isValid());
    ui->statusBtn->setEnabled(ui->taskView->currentIndex().isValid());
}

void MainWindow::on_editBtn_clicked() {

    QModelIndex index = ui->taskView->selectionModel()->currentIndex();
    Task task = m_taskManager.getTaskModel()->taskList().at(index.row());

    ui->tabWidget->setCurrentIndex(1);

    ui->titleTxt->setText(task.title());
    ui->descriptionTxt->setText(task.description());
    ui->importanceSb->setValue(task.importance());
    ui->dateTimeEdit->setDate(task.date());
    ui->repeatCb->setCurrentIndex(setRepetitionIndex(task.status()));

    m_taskManager.setTaskList(m_taskManager.getTaskModel()->taskList());
    ui->editBtn->setEnabled(false);
    mode = 1;
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
        stop = false;
    }


    if(ui->lastnameTxt->text() == "")
    {
        ui->lastnameTxt->setStyleSheet(style);
        ui->lastnameTxt->setPlaceholderText("Last Name EMPTY!");
        stop = false;
    }else{
        ui->lastnameTxt->setStyleSheet("");
        m_user.setLastname(ui->lastnameTxt->text());
        stop = false;
    }


    if(ui->emailTxt->text() == "")
    {
        ui->emailTxt->setStyleSheet(style);
        ui->emailTxt->setPlaceholderText("E-mail EMPTY!");
        stop = true;
    }else{
        ui->emailTxt->setStyleSheet("");
        m_user.setEmail(ui->emailTxt->text());
        stop = false;
    }

    m_user.setBirthday(ui->dateEdit->date());
    m_user.setAddress(ui->addressTxt->text());

    if(!stop){
        userUpdatedConfirmed(m_userManager.update(m_user));
    }
}

void MainWindow::on_statusBtn_clicked(){

    QModelIndex index = ui->taskView->selectionModel()->currentIndex();
    Task task = m_taskManager.getTaskModel()->taskList().at(index.row());
    sf.giveTask(task);
    task = *sf.readStatusFromWindow();
    sf.show();

    //  m_taskManager.setTaskList(m_taskManager.getTaskModel()->taskList());
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

    ui->taskView->setSelectionMode(QAbstractItemView::SingleSelection);
}

void MainWindow::sort_() {

    TaskListModel model;
    QSortFilterProxyModel proxyModel;
    proxyModel.setSourceModel(&model);
    ui->taskView->setModel(&proxyModel);
}


void MainWindow::on_statisticBtn_clicked()
{
    ssf.setUsername(m_username);
    ssf.setTasksList(m_taskManager.getTaskList());
    ssf.initializeData();

    //setCentralWidget(ssf);
    //    ssf.layout()->addWidget(chartView);
    //    ssf.layout()->setAlignment(Qt::AlignCenter);
    // ssf.resize(480, 300);
    // ssf.show();
}
