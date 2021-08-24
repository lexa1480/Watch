#ifndef CIRCLE_H
#define CIRCLE_H
#include <QWidget>

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

#endif // CIRCLE_H
