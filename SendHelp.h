#ifndef SENDHELP_H
#define SENDHELP_H

#include <QObject>

class SendHelp : public QObject
{
    Q_OBJECT

private:

public:
    SendHelp(QObject* pwgt = 0);
    ~SendHelp();

public slots:
    void slotSendData(QString time);

signals:
    void signalHelp(QString time);
};

#endif // SENDHELP_H
