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

class Circle : public QWidget
{
    Q_OBJECT
public:
    QColor brushColor;
    Circle(QWidget *parent = 0);
    ~Circle();
protected:
    void paintEvent(QPaintEvent *);

};

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
    QString m_strPath;
    int     m_xCoord;
    int     m_yCoord;
    Circle  m_yelCirc;
    Circle  m_greCirc;

    const QString c_szFileNameYellow = "yellow.png";
    const QString c_szFileNameGreen = "green.png";

    Clock(QWidget* pwgt = 0);
    ~Clock();

    void   mousePressEvent(QMouseEvent* pe);
    void   mouseMoveEvent(QMouseEvent* pe);
    bool   isDataReceived() const;


public slots:
    void slotUpdateDateTime();
};
#endif
