#include "sqlconnector.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

//sqlconnector::sqlconnector()
//{

//}

//void sqlconnector::openConnection() {
//    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
//    db.setHostName("personalplaner.c8g5ukkpvryv.eu-central-1.rds.amazonaws.com");
//    db.setDatabaseName("PersonalPlanner");
//    db.setUserName("anastasiya");
//    db.setPassword("personalplaner");
//    bool success = db.open();
//    qDebug()<<"Database connection established: "<<success;
//}


//void sqlconnector::createTableFromData() {
//    // Create table
//    QSqlQuery q ("CREATE TABLE monster( \
//                 id serial PRIMARY KEY, \
//                 name VARCHAR (50) NOT NULL, \
//                 healthpoints INTEGER NOT NULL, \
//                 healthpointsmax INTEGER NOT NULL \
//                 );");

//    qDebug() << "Creating table was successful: " << q.exec();


//    // Fill table with data
//    QFile file("data.txt");
//    if(!file.open(QIODevice::ReadOnly)) {
//        qDebug() << "Error: " << file.errorString();
//        return;
//    }


//    QTextStream in(&file);
//    while(!in.atEnd()) {
//        QString line = in.readLine();

//        if(line.contains('#'))
//            continue;

//        QStringList fields = line.split(",");

//        QSqlQuery query;
//        query.prepare("INSERT INTO monster (id, name, healthpoints, healthpointsmax) "
//                      "VALUES (:id, :name, :healthpoints, :healthpointsmax)");
//        query.bindValue(":id", fields[0]);
//        query.bindValue(":name", fields[1]);
//        query.bindValue(":healthpoints", fields[2].toInt());
//        query.bindValue(":healthpointsmax", fields[3].toInt());
//        query.exec();
//    }
//}


//void sqlconnector::queryDataAndPrintData() {
//    QSqlQuery query;
//    query.exec("SELECT name, healthpoints, healthpointsmax FROM monster WHERE id > 3");

//    while (query.next()) {
//        QString name = query.value(0).toString();
//        int healthpoints = query.value(1).toInt();
//        int healthpointsmax = query.value(2).toInt();
//        qDebug() << name << healthpoints << healthpointsmax;
//    }
//}


Sqlconnector::Sqlconnector()
{

}

Sqlconnector:: ~Sqlconnector()
{
    disconnect();
}

void Sqlconnector::connect()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("personalplaner.c8g5ukkpvryv.eu-central-1.rds.amazonaws.com");
    db.setDatabaseName("PersonalPlanner");
    db.setUserName("anastasiya");
    db.setPassword("personalplaner");
    bool success = db.open();
    qDebug()<<"Database connection established: "<<success;
}

bool Sqlconnector::disconnect()
{
    if (this->db.isOpen())
    {
        this->db.close();
        return true;
    }
    else
    {
        return false;
    }
}

QSqlQuery Query(QString q)
{
    QSqlQuery query(q);
    return query;
}
