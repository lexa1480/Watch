#include "Clock.h"
#include <QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <string>
#include <QLabel>
#include <QTime>
#include <QPainter>
#include <QColor>
#include <QPen>

#include <iostream>

Clock::Clock(QWidget *pwgt)
    : QLabel(pwgt)
    , m_ptPict(975,3)
    , m_sizePict(20,20)
    , m_yelCirc(this)
    , m_greCirc(this)
    , m_redCirc(this)
    , intervalTime(60)
{
    m_yelCirc.brushColor = Qt::yellow;
    m_greCirc.brushColor = Qt::green;
    m_redCirc.brushColor = Qt::red;
    m_yelCirc.move(m_ptPict);
    m_greCirc.move(m_ptPict);
    m_redCirc.move(m_ptPict);
    QTimer* ptimer = new QTimer(this);
    connect(ptimer,SIGNAL(timeout()),SLOT(slotCheckData()));
    ptimer->start(5000);
}

Clock::~Clock()
{

}

void Clock::slotCheckData(){
    m_yelCirc.setVisible(false);
    m_greCirc.setVisible(false);
    m_redCirc.setVisible(true);
}

void Clock::slotUpdateDateTime(QString time)
{
    setText("<H2><LEFT>" + time + "</LEFT></H2>");

    QTime realTime = QTime::fromString(time, "hh:mm:ss:zzz");

    if(realTime.secsTo(QTime::currentTime()) < intervalTime)
    {
        m_yelCirc.setVisible(false);
        m_greCirc.setVisible(true);
        m_redCirc.setVisible(false);
    }
    else
    {
        m_yelCirc.setVisible(true);
        m_greCirc.setVisible(false);
        m_redCirc.setVisible(false);
    }
}

void Clock::mousePressEvent(QMouseEvent *pe)
{
    m_xCoord = pe->x();
    m_yCoord = pe->y();
}

void Clock::mouseMoveEvent(QMouseEvent *pe)
{
    if (pe->buttons() != Qt::NoButton)
    {
        move(pe->globalPos().x()-m_xCoord,pe->globalPos().y()-m_yCoord);
    }
}




