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
    , m_strPath("../Watch")
    , m_yellow("../Watch/yellow.png")
    , m_green("../Watch/green.png")
    , m_ptPict(975,3)   
    , m_sizePict(20,20)
    , m_DataTimeForm("dd/MM/yyyy hh:mm:ss")
    , m_yelCirc(this)
    , m_greCirc(this)

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

    m_yelCirc.brushColor = Qt::yellow;
    m_greCirc.brushColor = Qt::green;
    m_yelCirc.move(m_ptPict);
    m_greCirc.move(m_ptPict);
    m_pictY.move(m_ptPict);
    m_pictG.move(m_ptPict);

    if (m_bDataReceived == isDataReceived())
    {
        if (m_green.isNull())
        {
            m_pictG.setVisible(false);
            m_pictY.setVisible(false);
            m_yelCirc.setVisible(false);
            m_greCirc.setVisible(true);
        }else
        {
            m_yelCirc.setVisible(false);
            m_greCirc.setVisible(false);
            m_pictY.setVisible(false);
            m_pictG.setPixmap(m_green.scaled(m_sizePict));
            m_pictG.setVisible(true);
        }
    }else
    {
        if (m_yellow.isNull())
        {
            m_pictG.setVisible(false);
            m_pictY.setVisible(false);
            m_yelCirc.setVisible(true);
            m_greCirc.setVisible(false);
        }else
        {
            m_yelCirc.setVisible(false);
            m_greCirc.setVisible(false);
            m_pictY.setPixmap(m_yellow.scaled(m_sizePict));
            m_pictG.setVisible(false);
            m_pictY.setVisible(true);

        }

    }
}



bool Clock::isDataReceived() const
{
    bool bRet = false;
    if(!m_timeReceived.isNull())
    {
        int iDelta_sec = m_timeReceived.secsTo(QTime::currentTime());
        if( iDelta_sec < 5 )
        {
            bRet = true;         
        }
    }
    return bRet;
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




