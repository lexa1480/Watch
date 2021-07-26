#include "Clock.h"
#include <QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <string>
#include <QLabel>
#include <QTime>

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

bool Clock::isDataReceived() const
{
    bool bRet = false;
    if(!m_timeReceived.isNull())
    {
        int iDelta_sec = m_timeReceived.secsTo(QTime::currentTime());
        if( iDelta_sec < 5 )
            bRet = true;
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
        //setText("<H2><LEFT>" + QString::number(l.x()) + ", " + QString::number(l.y()) + " [] "+ QString::number(pe->globalPos().x()) + ", " + QString::number(pe->globalPos().y()) + "</LEFT></H2>");
        move(pe->globalPos().x()-xCoord,pe->globalPos().y()-yCoord);
    }
}




