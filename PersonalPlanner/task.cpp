#include "task.h"
#include <iostream>

/*how to generate taskID? It shouldnt be the user who generates it! */


Task::Task(int t_taskID, QString t_title, QDate t_date, int t_importance, QString t_username) : m_taskID(t_taskID), m_title(t_title), m_date(t_date), m_importance(t_importance), m_username(t_username){

}

Task::~Task(){}

int Task::taskID() const
{
    return m_taskID;
}

void Task::setTaskID(int taskID)
{
    m_taskID = taskID;
}


QString Task::title() const
{
    return m_title;
}

void Task::setTitle(const QString &title)
{
    m_title = title;
}

QDate Task::date() const
{
    return m_date;
}

void Task::setDate(const QDate &date)
{
    m_date = date;
}

QString Task::description() const
{
    return m_description;
}

void Task::setDescription(const QString &description)
{
    m_description = description;
}

QImage Task::icon() const
{
    return m_icon;
}

void Task::setIcon(const QImage &icon)
{
    m_icon = icon;
}

int Task::importance() const
{
    return m_importance;
}

void Task::setImportance(int importance)
{
    m_importance = importance;
}

QString Task::status() const
{
    return m_status;
}

void Task::setStatus(const QString &status)
{
    m_status = status;
}

QString Task::repetition() const
{
    return m_repetition;
}

void Task::setRepetition(const QString &repetition)
{
    m_repetition = repetition;
}

QString Task::username() const
{
    return m_username;
}

void Task::setUsername(const QString &username)
{
    m_username = username;
}

QString Task::toString(){
    QString string ;
    string.append("TaskID: " );
    string.append(QString::number(m_taskID));
    string.append("\nTitle: ");
    string.append(m_title);
    string.append("\nDescription: ");
    string.append(m_description);
    string.append("\nImportance: ");
    string.append(QString::number(m_importance));
    string.append("\nStatus: ");
    string.append(m_status);
    string.append("\nDate: ");
    string.append(m_date.toString("dd.MM.yyyy"));
    string.append("\nRepetition: ");
    string.append(m_repetition);
    return string;

}





