#include "Clock.h"
#include <QPainter>
#include <QRect>
#include <QColor>

#include <QToolTip>
#include <QString>

Circle::Circle(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(7, 3, 20, 20);
    this->setAttribute(Qt::WA_AlwaysShowToolTips);
    timeDelay = 0;
}

Circle::~Circle()
{}



void Circle::paintEvent(QPaintEvent *)
{
        QPainter painter;
        painter.begin(this);
        painter.setRenderHint(QPainter::Antialiasing,true);
        painter.setPen(Qt::NoPen);
        painter.setBrush(brushColor);
        painter.drawEllipse(QRect(0, 0, 20, 20));
        painter.end();
}

bool Circle::event(QEvent *event)
{
    if(event->type() == QEvent::ToolTip)
    {
        int x = this->mapToGlobal(QPoint(0, 0)).x();
        int y = this->mapToGlobal(QPoint(0, 0)).y();
        if(brushColor == Qt::green || brushColor == Qt::gray)
        {
            x = x - 10;
            y = y - 45;
            QToolTip::showText(QPoint(x, y), "CEB");
        }
        if(brushColor == Qt::yellow)
        {
            x = x - 10;
            y = y - 65;
            QToolTip::showText(QPoint(x, y), "CEB\nВремя отличается на " + QVariant(timeDelay/60).toString() + " минут");
        }
        if(brushColor == Qt::red)
        {
            x = x - 10;
            y = y - 65;
            QToolTip::showText(QPoint(x, y), "CEB\nОтсутствует связь с CEB");
        }
    }

    return QWidget::event(event);
}
