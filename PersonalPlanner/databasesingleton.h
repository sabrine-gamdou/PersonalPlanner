#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H
#include <QtSql/QSqlDatabase>

//namespace DatabaseLayer {


class DatabaseSingleton{
private:
    /* Instance is stored here */
    static DatabaseSingleton* volatile m_pInstance;

    /* SqlConnection Instance is stored here */
    // static SqlConnection connection;

    /* Private constructor to prevent instancing. */
    DatabaseSingleton(){}
public:
    // ~DatabaseSingleton();
    /* Static Access Method. */
    static DatabaseSingleton* getInstance();

    /* Create and Open Connection to Database */
    void openConnection();
};

//}

#endif // DATABASESINGLETON_H
