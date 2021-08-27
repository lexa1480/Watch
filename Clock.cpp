#include "Clock.h"
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QTime>
#include <QApplication>
#include <QDesktopWidget>
#include <QRect>

Clock::Clock(QWidget *pwgt)
    : QLabel(pwgt)
    , m_ptPict(7.5, 3)
    , m_sizePict(20, 20)
    , m_yelCirc(this)
    , m_greCirc(this)
    , m_redCirc(this)
    , m_grayCirc(this)
    , intervalTime(60)
    , redLampTimer(this)
    , saveTimer(this)
{
    m_yelCirc.brushColor = Qt::yellow;
    m_greCirc.brushColor = Qt::green;
    m_redCirc.brushColor = Qt::red;
    m_grayCirc.brushColor = Qt::gray;
    m_yelCirc.move(m_ptPict);
    m_greCirc.move(m_ptPict);
    m_redCirc.move(m_ptPict);
    m_grayCirc.move(m_ptPict);

    connect(&redLampTimer, SIGNAL(timeout()), SLOT(slotRedSignal()));
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
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint );
}

Clock::~Clock()
{

}

void Clock::slotRedSignal()
{
    m_yelCirc.setVisible(false);
    m_greCirc.setVisible(false);
    m_redCirc.setVisible(true);
    m_grayCirc.setVisible(false);
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
        m_grayCirc.setVisible(false);
    }
    else
    {
        m_yelCirc.setVisible(true);
        m_greCirc.setVisible(false);
        m_redCirc.setVisible(false);
        m_grayCirc.setVisible(false);
    }
    redLampTimer.start(2000);
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



