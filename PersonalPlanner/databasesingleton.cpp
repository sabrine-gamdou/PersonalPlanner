#include "databasesingleton.h"
#include <QtSql/QSqlDatabase>
#include <QDebug>

//using namespace DatabaseLayer;


    DatabaseSingleton* volatile DatabaseSingleton::m_pInstance = 0;



    DatabaseSingleton* DatabaseSingleton::getInstance(){
        if(!m_pInstance){
            DatabaseSingleton* volatile temp = new DatabaseSingleton;
            m_pInstance = temp;
        }
        return m_pInstance;
    }

    void DatabaseSingleton::openConnection() {
//        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//        db.setHostName("personalplaner.c8g5ukkpvryv.eu-central-1.rds.amazonaws.com");
//        db.setDatabaseName("PersonalPlanner");
//        db.setUserName("anastasiya");
//        db.setPassword("personalplaner");
//        bool success = db.open();
//        qDebug()<<"Database connection established: "<<success;

                QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
                db.setHostName("127.0.0.1");
                db.setDatabaseName("postgres");
                db.setUserName("postgres");
                db.setPassword("1234");
                bool success = db.open();
                qDebug()<<"Database connection established: "<<success;
    }


