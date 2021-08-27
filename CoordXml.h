#ifndef COORDXML_H
#define COORDXML_H

#include "boost/filesystem.hpp"
#include <reg_12.h>
#include <ModeInfo.h>

#include <iostream>

class CoordXml
{
protected:
    std::string    m_sXmlPath;
    int            m_iX;
    int            m_iY;

public:
    CoordXml()
        : m_iX(500)
        , m_iY(700)
    {

    }
    inline void Init();
    inline void RegRead();
    inline void RegWrite();
    inline int getX();
    inline int getY();
    inline void setX(int x);
    inline void setY(int y);
};


inline void CoordXml::Init()
{
    plug_key::CModeInfoPlug libModeInfo;
    libModeInfo.Load();
    m_sXmlPath = libModeInfo.GetExpanded("$(NITADATA)/[CFG]/ship-clock.xml");
    libModeInfo.Free();
}

inline void CoordXml::RegRead()
{
    registry::CXMLProxy proxy;
    if( !proxy.load( m_sXmlPath ) )
    {
        std::cout << "INF> Data-file is not loaded: " << m_sXmlPath << std::endl;
    }
    else
    {
        registry::CNode nodeRoot( &proxy, "" );
        if( nodeRoot.isValid() )
        {
            std::string sCoords;// "100, 300"
            nodeRoot.getValue( "ScreenCoords",  sCoords );
            sscanf(sCoords.c_str(), "%d,%d", &m_iX, &m_iY);
        }
    }
}

inline void CoordXml::RegWrite()
{
    namespace fs = boost::filesystem;
    fs::path pathFull = m_sXmlPath;
    fs::path path = pathFull.parent_path();
    bool bExists = false;
    try{ bExists = fs::exists( path ); } catch(...){}
    if(!bExists)
    {
        try{fs::create_directories(path);}catch(...){}
    }

    registry::CXMLProxy proxy;
    registry::CNode nodeRoot( &proxy, "");
    if( nodeRoot.isValid() )
    {
        std::stringstream ss;
        ss << m_iX << ", " << m_iY;
        std::string sCoords = ss.str();
        nodeRoot.setValue( "ScreenCoords",  sCoords );
    }
    if( !proxy.save( m_sXmlPath ) )
    {
        std::cout << "ERR> Data-file can't be loaded: " << m_sXmlPath << std::endl;
    }
}

inline int CoordXml::getX()
{
    return m_iX;
}

inline int CoordXml::getY()
{
    return m_iY;
}

inline void CoordXml::setX(int x)
{
    m_iX = x;
}

inline void CoordXml::setY(int y)
{
    m_iY = y;
}


#endif

