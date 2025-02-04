#ifndef CALENDARMANAGER_H
#define CALENDARMANAGER_H

#include <QCalendarWidget>
#include <QBrush>
#include <QColor>
#include <QList>
#include <QDate>
#include <QPen>
#include <QPainter>

class CalendarManager : public QCalendarWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ getColor WRITE setColor)

public:
    CalendarManager(QWidget *parent = 0);
    ~CalendarManager();

    void setColor(const QColor &color);
    QColor getColor() const;
    void getDate(QDate &date);
    void setDates(const QList<QDate> &dates);

protected:
    virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

private:
    QList<QDate> m_dates;
    QPen m_outlinePen;
    QBrush m_transparentBrush;

};

#endif // CALENDARMANAGER_H
