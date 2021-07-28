#ifndef CLOCK_H
#define CLOCK_H
#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QPixmap>
#include <string>
#include <QLabel>
#include <QTime>
#include <QTimer>


class Clock : public QLabel
{
    Q_OBJECT

public:
    bool    m_bDataReceived;
    QTime   m_timeReceived;
    QLabel  m_pictY;
    QLabel  m_pictG;
    QPixmap m_yellow;
    QPixmap m_green;
    QPoint  m_ptPict;
    QSize   m_sizePict;
    QString m_DataTimeForm;
    int     xCoord;
    int     yCoord;
    QColor  col;


    Clock(QWidget* pwgt = 0);
    ~Clock();

    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent* pe);
    bool isDataReceived();
    void paintEvent(QPaintEvent* paev);

public slots:
    void slotUpdateDateTime();
};
#endif
