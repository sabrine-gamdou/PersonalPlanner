#ifndef SQLCONNECTOR_H
#define SQLCONNECTOR_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class Sqlconnector
{
public:
    Sqlconnector();
    ~Sqlconnector();

    void connect();
    bool disconnect();
    QSqlQuery Query(QString q);
    //void openConnection();
    //void createTableFromData();
    //void queryDataAndPrintData();


    QSqlDatabase db;
};

#endif // SQLCONNECTOR_H
