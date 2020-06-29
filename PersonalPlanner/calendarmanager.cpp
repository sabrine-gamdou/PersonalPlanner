#include "calendarmanager.h"

CalendarManager::CalendarManager(QWidget *parent)
    : QCalendarWidget(parent)
{
    m_outlinePen.setColor(Qt::red);
    m_outlinePen.setWidth(5);
    m_transparentBrush.setColor(Qt::transparent);
}


CalendarManager::~CalendarManager(){

}


void CalendarManager::setColor(const QColor &color){
    m_outlinePen.setColor(color);
}


QColor CalendarManager::getColor() const{
    return m_outlinePen.color();
}


void CalendarManager::getDate(QDate &date){
    if(!m_dates.contains(date))
        m_dates.append(date);
}


void CalendarManager::setDates(const QList<QDate> &dates){
    m_dates = dates;
}


void CalendarManager::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const{
    QCalendarWidget::paintCell(painter, rect, date);

    if( m_dates.contains(date) ) {
        painter->setPen(m_outlinePen);
        painter->setBrush(m_transparentBrush);
        painter->drawRect(rect.adjusted(0, 0, -1, -1));
    }
}




