#include <QWidget>
#include <QMainWindow>
#include <QApplication>

#include "nmea/nmea_zda.h"
#include "SendHelp.h"
#include "Clock.h"

class CStClientProcessor : public ip_st_x::CStClientSubscriber
{
public:
    virtual NVoid OnPacket(NByte* pBufIn, NDword dwSizeIn, ip_st_x::CDataPacketBuffer& dpb)
    {
        std::string sPacket((const char*)(pBufIn));
        sPacket = sPacket.substr(7, 10);
        sPacket = sPacket.substr(0, 2) + ":" + sPacket.substr(2, 2) + ":" + sPacket.substr(4, 2);
        QString result = sPacket.c_str();


        QObject::connect(sendHelp, SIGNAL(signalHelp(QString)), clock, SLOT(slotUpdateDateTime(QString)), Qt::QueuedConnection);
        sendHelp->slotSendData(result);
    }

    Clock *clock;
    SendHelp *sendHelp;

    CStClientProcessor(SendHelp &sendHlp, Clock &clk){
        sendHelp = &sendHlp;
        clock = &clk;
    }
};



int main(int argc, char *argv[])
{
    std::setlocale(LC_ALL, "");
    QApplication app(argc, argv);

    Clock clock;
    clock.show();

    ip_st_x::CStPlugMain m_plugIpSt;
    ip_st_x::CStPlugClient m_plugClient;
    SendHelp sendHlp(m_plugIpSt, m_plugClient);
    CStClientProcessor m_processor(sendHlp, clock);

    try
    {
        if(!m_plugIpSt.Load())
        {
            throw "Load";
        }
        m_plugIpSt.SetAppName("StTestApp");
        m_plugIpSt.SetSockMcAddr( "234.0.1.0" );
        if(!m_plugIpSt.Start())
        {
            throw "Start";
        }
        if(!m_plugIpSt.GetStClient(m_plugClient))
        {
            throw "Get Client";
        }
        m_plugClient.SetClientName("TestStPlugin");
        if(!m_plugClient.AssignSource("NmeaTime", ip_st_x::ST_READER))
        {
            throw "Assign Source";
        }
        m_plugClient.Subscribe(&m_processor);
        if(!m_plugClient.OpenStClient())
        {
            throw "Open Client";
        }
    }
    catch (char const* str)
    {
        std::cout << "Error: " << str << std::endl;
    }


    return app.exec();
}
