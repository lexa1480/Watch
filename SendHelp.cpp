#include "SendHelp.h"
#include <iostream>

SendHelp::SendHelp(QObject* pwgt) : QObject(pwgt)
{

}

void SendHelp::slotSendData(QString time)
{
    emit signalHelp(time);
}

SendHelp::~SendHelp()
{

}
