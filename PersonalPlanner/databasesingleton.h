#ifndef DATABASESINGLETON_H
#define DATABASESINGLETON_H

#include <QSqlDatabase>
#include <QDebug>


class DatabaseSingleton{
public:
    /*! \brief Static Access Method.*/
    static QSqlDatabase getInstance();

private:
    /*! \brief Instance is stored here */
    static QSqlDatabase m_pInstance;

    /*! \brief Private constructor to prevent instancing. */
    DatabaseSingleton();
    ~DatabaseSingleton();

    /*! \brief Create and Open Connection to Database */
    static void openConnection();

    /*! \brief Close Connection to Database */
    static void closeConnection();
};



#endif // DATABASESINGLETON_H
