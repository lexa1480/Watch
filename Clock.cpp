#include "Clock.h"
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QTime>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

#include <iostream>

Clock::Clock(QWidget *pwgt)
    : QLabel(pwgt)
    , m_ptPict(7.5,3)
    , m_sizePict(20,20)
    , m_yelCirc(this)
    , m_greCirc(this)
    , m_redCirc(this)
    , intervalTime(60)
    , seter(true)
{
    m_yelCirc.brushColor = Qt::yellow;
    m_greCirc.brushColor = Qt::green;
    m_redCirc.brushColor = Qt::red;
    m_yelCirc.move(m_ptPict);
    m_greCirc.move(m_ptPict);
    m_redCirc.move(m_ptPict);
    QTimer* ptimer = new QTimer(this);
    connect(ptimer,SIGNAL(timeout()),SLOT(slotCheckData()));
    ptimer->start(1000);
}

Clock::~Clock()
{

}

void Clock::slotCheckData(){
    if(seter)
    {
        m_yelCirc.setVisible(false);
        m_greCirc.setVisible(false);
        m_redCirc.setVisible(true);
    }
    seter = true;
}

void Clock::slotUpdateDateTime(QString time)
{
    setText("<H2><LEFT>" + time + "</LEFT></H2>");

    QTime realTime = QTime::fromString(time, "hh:mm:ss");

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
    seter = false;
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
        int x = pe->globalPos().x()-m_xCoord;
        int y = pe->globalPos().y()-m_yCoord;
        QRect screen = QApplication::desktop()->availableGeometry(0);
        if(x < 0){
            x = 0;
        }
        if(y < 0){
            y = 0;
        }
        if(x > (screen.width() - 125)){
            x = screen.width() - 125;
        }
        if(y > (screen.height() - 26)){
            y = screen.height() - 26;
        }
        move(x,y);
    }
}




