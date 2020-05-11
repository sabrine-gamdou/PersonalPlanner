#ifndef SQLCONNECTOR_H
#define SQLCONNECTOR_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class sqlconnector
{
public:
    sqlconnector();
    void openConnection();
    void createTableFromData();
    void queryDataAndPrintData();
};

#endif // SQLCONNECTOR_H
