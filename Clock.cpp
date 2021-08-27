#include "Clock.h"
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QTime>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

#include <iostream>

int Fun1(){
    //LOAD
    return 1000;
}

Clock::Clock(QWidget *pwgt)
    : QLabel(pwgt)
    , m_ptPict(7.5,3)
    , m_sizePict(20,20)
    , m_yelCirc(this)
    , m_greCirc(this)
    , m_redCirc(this)
    , intervalTime(60)
    , bsignal(true)
    , saveTimer(this)
{
    m_yelCirc.brushColor = Qt::yellow;
    m_greCirc.brushColor = Qt::green;
    m_redCirc.brushColor = Qt::red;
    m_yelCirc.move(m_ptPict);
    m_greCirc.move(m_ptPict);
    m_redCirc.move(m_ptPict);

    QTimer* ptimer = new QTimer(this);
    connect(ptimer, SIGNAL(timeout()), SLOT(slotCheckSignal()));
    ptimer->start(1000);

    connect(&saveTimer, SIGNAL(timeout()), SLOT(slotSaveCoord()));

    coordXml.Init();
    coordXml.RegRead();

    this->setGeometry(coordXml.getX(), coordXml.getY(), 125, 26);
    this->setStyleSheet("QLabel {"
                            "border-style: solid;"
                            "border-width: 1px;"
                            "border-color: black; "
                        "}");
    this->setAlignment(Qt::AlignRight);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

Clock::~Clock()
{

}

void Clock::slotCheckSignal()
{
    if(bsignal)
    {
        m_yelCirc.setVisible(false);
        m_greCirc.setVisible(false);
        m_redCirc.setVisible(true);
    }
    bsignal = true;
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
    bsignal = false;
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
        QRect screenSize = QApplication::desktop()->availableGeometry(0);
        if(x < 0)
        {
            x = 0;
        }
        if(y < 0)
        {
            y = 0;
        }
        if(x > (screenSize.width() - 125))
        {
            x = screenSize.width() - 125;
        }
        if(y > (screenSize.height() - 26))
        {
            y = screenSize.height() - 26;
        }
        move(x,y);
    }

    saveTimer.start(5000);
}

void Clock::slotSaveCoord()
{
    saveTimer.stop();
    coordXml.setX(this->x());
    coordXml.setY(this->y());
    coordXml.RegWrite();

}



