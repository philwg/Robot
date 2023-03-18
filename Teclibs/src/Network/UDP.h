// **********************************************************************
// * FILE  : UDP.h
// * GROUP : TecLibs/Network
// *---------------------------------------------------------------------
// * PURPOSE : Send and recv data via UDP
// * COMMENT : 
// *---------------------------------------------------------------------
// * DATES     : 20/07/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#ifndef _UDP_h_
#define _UDP_h_



// ----------------------------------------------------------------------
// +---------
// | Global includes
// +---------
#include "TecLibs.h"        // To be Tec



// ----------------------------------------------------------------------
// **************************************************
// * UDP class
// *-------------------------------------------------
// * - 
// * - 
// **************************************************
class UDP
{
public:
    // +---------
    // | Life-cycle
    // +---------
    // Constructor (<szIP>:<nPortOut> for sending, 10.0.0.127:<nPortIn> for listenning)
    UDP( char* szIP , Int nPortIn , Int nPortOut );

    // Destructor (Close all connections)
    ~UDP();


    // +---------
    // | Communication
    // +---------
    // Send without AR
    void Send( void* pData , Int nSize );

    // Reception by polling (ie, block while not message)
    Bool TestAndRecv( void* pData , Int* pSize );



public:
    // +---------
    // | Auxiliary fnct
    // +---------
    Bool Connect();
    void Disconnect();


    // +---------
    // | Internal datas
    // +---------
    char*   m_szIP;
    Int     m_nPortIn;
    Int     m_nPortOut;
};


#endif//_UDP_h_
