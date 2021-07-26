#include <Clock.h>
#include <QWidget>
#include <QMainWindow>
#include <QApplication>

int main(int argc, char *argv[])
{
    std::setlocale(LC_ALL, "");
    QApplication app(argc, argv);
    Clock lbl;
    lbl.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    lbl.resize(1000,26);
    lbl.show();
    return app.exec();
}
