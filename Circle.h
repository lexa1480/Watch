#ifndef CIRCLE_H
#define CIRCLE_H
#include <QWidget>

class Circle : public QWidget
{
    Q_OBJECT
public:
    QColor brushColor;
    int timeDelay;
    Circle(QWidget *parent = 0);
    ~Circle();
protected:
    void paintEvent(QPaintEvent *) override;
    bool event(QEvent *event) override;

};

#endif // CIRCLE_H
