#include "SendHelp.h"

SendHelp::SendHelp(ip_st_x::CStPlugMain &m_plugIpSt, ip_st_x::CStPlugClient &m_plugClient, QObject* pwgt)
    : QObject(pwgt)
    , m_plugIpSt(m_plugIpSt)
    , m_plugClient(m_plugClient)
{

}

void SendHelp::slotSendData(QString time)
{
    emit signalHelp(time);
}

SendHelp::~SendHelp()
{
    m_plugClient.CloseStClient();
    m_plugIpSt.Stop();
    m_plugIpSt.Free();
}
