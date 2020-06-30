#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H

#include <QtSql/QSqlDatabase>
#include <QDebug>


class DatabaseSingleton{
public:
    /* Static Access Method.*/
    static QSqlDatabase getInstance();

private:
    /* Instance is stored here */
    static QSqlDatabase m_pInstance;

    /* Private constructor to prevent instancing. */
    DatabaseSingleton();
    ~DatabaseSingleton();

    /* Create and Open Connection to Database */
    static void openConnection();

    /* Close Connection to Database */
    static void closeConnection();
};



#endif // DATABASESINGLETON_H
