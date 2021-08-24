#include "Clock.h"
#include <QPainter>
#include <QRect>
#include <QColor>


Circle::Circle(QWidget *parent) : QWidget(parent)
{

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
        painter.drawEllipse(QRect(0,0,20,20));
        painter.end();
}

