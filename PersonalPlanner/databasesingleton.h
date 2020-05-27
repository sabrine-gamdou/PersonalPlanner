#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H
#include <QtSql/QSqlDatabase>

//namespace DatabaseLayer {


class DatabaseSingleton{
private:
    /* Instance is stored here */
    static QSqlDatabase m_pInstance;
    /* SqlConnection Instance is stored here */
    // static SqlConnection connection;

    /* Private constructor to prevent instancing. */
    DatabaseSingleton();
    ~DatabaseSingleton();

    static void openConnection();
    static void closeConnection();

public:
    // ~DatabaseSingleton();
    /* Static Access Method. */
    static QSqlDatabase getInstance();

    /* Create and Open Connection to Database */

};

//}

#endif // DATABASESINGLETON_H
