#include "databasesingleton.h"

QSqlDatabase DatabaseSingleton::m_pInstance ;

DatabaseSingleton::DatabaseSingleton(){

}

DatabaseSingleton::~DatabaseSingleton(){
    closeConnection();
}

void DatabaseSingleton::openConnection() {
    m_pInstance = QSqlDatabase::addDatabase("QPSQL");
    m_pInstance.setHostName("personalplaner.c8g5ukkpvryv.eu-central-1.rds.amazonaws.com");
    m_pInstance.setDatabaseName("PersonalPlanner");
    m_pInstance.setUserName("anastasiya");
    m_pInstance.setPassword("personalplaner");

    bool success = m_pInstance.open();
    qDebug()<<"Database connection established: "<<success;
}

void DatabaseSingleton::closeConnection(){
    if (m_pInstance.isOpen())
        m_pInstance.close();
}

QSqlDatabase DatabaseSingleton::getInstance(){
    if(!m_pInstance.isOpen())
        openConnection();

    return m_pInstance;
}

