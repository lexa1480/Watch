#ifndef CLOCK_H
#define CLOCK_H

#include <QMouseEvent>
#include <QPixmap>
#include <string>
#include <QLabel>
#include <QTime>
#include <QTimer>
#include <Circle.h>
#include "CoordXml.h"


class Clock : public QLabel
{
    Q_OBJECT

public:
    QPoint  m_ptPict;
    QSize   m_sizePict;
    int     m_xCoord;
    int     m_yCoord;
    Circle  m_yelCirc;
    Circle  m_greCirc;
    Circle  m_redCirc;
    int intervalTime;
    bool bsignal;
    QTimer saveTimer;
    CoordXml coordXml;

    Clock(QWidget* pwgt = 0);
    ~Clock();

    void   mousePressEvent(QMouseEvent* pe);
    void   mouseMoveEvent(QMouseEvent* pe);

public slots:
    void slotUpdateDateTime(QString a);
    void slotCheckSignal();
    void slotSaveCoord();
};
#endif
