#ifndef SENDHELP_H
#define SENDHELP_H

#include <QObject>
#include <ip_st_x3.h>

class SendHelp : public QObject
{
    Q_OBJECT

private:
    ip_st_x::CStPlugMain &m_plugIpSt;
    ip_st_x::CStPlugClient &m_plugClient;

public:
    SendHelp(ip_st_x::CStPlugMain &m_plugIpSt, ip_st_x::CStPlugClient &m_plugClient, QObject* pwgt = 0);
    ~SendHelp();

public slots:
    void slotSendData(QString time);

signals:
    void signalHelp(QString time);
};

#endif // SENDHELP_H
