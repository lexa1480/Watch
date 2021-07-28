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


Clock::Clock(QWidget *pwgt)
    : QLabel(pwgt)
    , m_bDataReceived(false)
    , m_timeReceived(QTime::currentTime())
    , m_pictY(this)
    , m_pictG(this)
    , m_yellow("../Watch/yellow.png")
    , m_green("../Watch/green.png")
    , m_ptPict(975,3)   
    , m_sizePict(20,20)
    , m_DataTimeForm("dd/MM/yyyy hh:mm:ss")
    , col(Qt::yellow)
{
    QTimer* ptimer = new QTimer(this);
    connect(ptimer,SIGNAL(timeout()),SLOT(slotUpdateDateTime()));
    ptimer->start(500);

    slotUpdateDateTime();
}
Clock::~Clock()
{}

void Clock::slotUpdateDateTime()
{
    QString str = QDateTime::currentDateTime().toString(m_DataTimeForm);
    setText("<H2><LEFT>" + str + "</LEFT></H2>");

    m_pictY.move(m_ptPict);
    m_pictG.move(m_ptPict);

    if (m_bDataReceived == isDataReceived())
    {
        m_pictY.setVisible(false);
        m_pictG.setPixmap(m_green.scaled(m_sizePict));
        m_pictG.setVisible(true);
    }else
    {
        m_pictY.setPixmap(m_yellow.scaled(m_sizePict));
        m_pictY.setVisible(true);
        m_pictG.setVisible(false);
    }
}

void Clock::paintEvent(QPaintEvent* paev)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(col);
    painter.drawEllipse(QRect(950,3,20,20));
}

bool Clock::isDataReceived()
{
    bool bRet = false;
    col = Qt::green;
    if(!m_timeReceived.isNull())
    {
        int iDelta_sec = m_timeReceived.secsTo(QTime::currentTime());
        if( iDelta_sec < 5 )
        {
            bRet = true;
            col = Qt::yellow;
        }
    }
    return bRet;
}

void Clock::mousePressEvent(QMouseEvent *pe)
{
    xCoord = pe->x();
    yCoord = pe->y();
}

void Clock::mouseMoveEvent(QMouseEvent *pe)
{
    if (pe->buttons() != Qt::NoButton)
    {
        move(pe->globalPos().x()-xCoord,pe->globalPos().y()-yCoord);
    }
}




