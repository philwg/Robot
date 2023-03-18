// **********************************************************************
// * FILE  : UDP.cpp
// * GROUP : TecLibs/Network
// *---------------------------------------------------------------------
// * PURPOSE : Implementation
// * COMMENT : 
// *---------------------------------------------------------------------
// * DATES     : 20/07/2000
// * AUTHORS   : Loic Le Chevalier (llechevalier@fr.infogrames.com)
// * COPYRIGHT : (c) Infogrames/TecLab 2000
// **********************************************************************
#include "UDP.h"



// ----------------------------------------------------------------------
// +---------
// | Local includes
// +---------
// Permet de faire un fichier socket.h local avec c'que tu veux dedans pour
// definir les sockets (<winsosk.h>, <socket.h>, etc.)
#include "Network/net/sockets.h"


// La LibNet du DSG multimedia
extern "C"
{
#include "Network/net/net.h"
}




// ----------------------------------------------------------------------
// +---------
// | Local defines
// +---------
// Outils de socketage
SOCKET SendSocket;
SOCKET ListenSocket;
SOCKET newsocket;



// ----------------------------------------------------------------------
// +---------
// | Life-cycle
// +---------
// Constructor (<szIP>:<nPortOut> for sending, 10.0.0.127:<nPortIn> for listenning)
UDP::UDP( char* szIP , Int nPortIn , Int nPortOut )
{
    m_szIP      = szIP;
    m_nPortIn   = nPortIn;
    m_nPortOut  = nPortOut;


#ifdef _WIN32
  //---- Init de Winsock
  if ( -1 == ::InitWSA() )
    {
      DebugBox("Can't initialize Winsock.dll. So stop the Kernel or desactivate TCP trace.");
      return;
    }
#endif

//   //
//   // (On init la socket de Send apres celle de Recv, car le
//   // client fait l'inverse, apres le serveur)
//   // => ici l'inverse
//   //

  //-- Open RECV (ListenSocket)
  // Init du client et du port 
  int listen_port = m_nPortOut;

  // Connect
//   ListenSocket = ::ListenPortNumber(listen_port,10/*nb socket max*/);
//   if ( ListenSocket == INVALID_SOCKET )
//     return false;
  do 
    ListenSocket = ::ListenPortNumber(listen_port,10/*nb socket max*/);
  while ( ListenSocket == INVALID_SOCKET );

  // Non blocking enable (par defaut BSD les met en bloquante)
  ioctlsocket(ListenSocket,FIONBIO,reinterpret_cast<unsigned long*>(&listen_port));//Faut juste que le pointer soit pas null...


//   //-- Open SEND
//   // Maintenant on peut attendre l'autre qui a du etre fait
//   while (!Connect());
}

// Destructor (Close all connections)
UDP::~UDP()
{
//   //-- Close SEND
//   ::Disconnect();
// 
// 
  //-- Close RECV (ListenSocket)
  ::CloseSocket(ListenSocket);

#ifdef _WIN32
  //---- Close Winsock
  ::ClearWSA();
#endif
}



// +---------
// | Communication
// +---------
void UDP::Send( void* pData , Int nSize )
{
    while (!Connect());
    ::Send(SendSocket,reinterpret_cast<char*>(&nSize),sizeof(nSize));
    ::Send(SendSocket,reinterpret_cast<char*>(pData),nSize);
    Disconnect();
}
Bool UDP::TestAndRecv( void* pData , Int* pSize )
{
  //--aceptation
  static SOCKET newsocket;
  newsocket = accept(ListenSocket,NULL,NULL);
  if ( newsocket == INVALID_SOCKET )
    return false;

  //--reception (tests selon messages:)
//   if ( ::IsSocketReadable(newsocket) == 0 )
//     return false;
// 
  ::Recv(newsocket,reinterpret_cast<char*>(pSize),sizeof(*pSize));
  ::Recv(newsocket,reinterpret_cast<char*>(pData),*pSize);

  //-- close newsocket
  ::CloseSocket(newsocket);
   return true;
}


// +---------
// | Auxialary fnct
// +---------
Bool UDP::Connect()
{
  //-- Open SEND (SendSocket): une fois le server lance
  // Connect
  SendSocket = ::ConnectHost(m_szIP,m_nPortIn);
  if ( SendSocket == INVALID_SOCKET )
    {
//       DebugBox("Can't initialize connection: server not respond. Try again...");
      return false;
    }


  //---- TVB
  return true;
}
void UDP::Disconnect()
{
  //-- Close SEND
  ::CloseSocket(SendSocket);
}

