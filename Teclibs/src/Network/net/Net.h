#ifndef _LIBNET_INCLUDE_H_
#define _LIBNET_INCLUDE_H_

#define VERSION_LIBNET	"1.21"

#ifndef CR
#define CR 13
#endif
#ifndef LF
#define LF 10
#endif

#ifndef WIN32
#define INVALID_SOCKET	-1
#define SOCKET int
#define	closesocket(a)	close(a)
#else
extern UINT WSA_ACCEPT;
extern UINT WSA_READ;
#endif


#define MAX_DATA						254
#define MAX_DATA_EX					2048

#define MODE_BROADCAST	1

typedef struct trame
	{
	unsigned char len;
	unsigned char type;
	unsigned char data[MAX_DATA];
	}TRAME;


typedef struct trame_ex
	{
	unsigned char len1,len2;
	unsigned char type;
	unsigned char data[MAX_DATA_EX];
	}TRAME_EX;

typedef struct socket_udp
	{
	SOCKET sock;
	struct sockaddr_in sin;
	int len_addr;
	}SOCKET_UDP;


/* --> Version 1.20 */
typedef struct libnet_client
	{
	SOCKET	socket; /* client's socket */
	int index;                              /* index to datas */
	int ptr;                                /* ptr to current data */
	char buffer[sizeof(TRAME_EX)];              /* client's own datas */
	} LIBNET_CLIENT;
/* <-  Version 1.20 */




/* --> Version 1.20 */
extern int InitLibnetClient(LIBNET_CLIENT *ptclient,SOCKET socket);
extern int ManageLibnetClient(LIBNET_CLIENT *  ptclient,char *buffer,int len,void (*ReceiveCallback)(LIBNET_CLIENT *,TRAME_EX *,int) );
extern char IsSocketWritable(SOCKET socket);
extern char IsSocketReadable(SOCKET socket);
/* <--  Version 1.20 */

extern int Recv(SOCKET socket,char * buffer,int len);
extern int Send(SOCKET socket,char * buffer,int len);
extern int RecvTrame(SOCKET socket,struct trame * Trame,int * len,int * type);
extern int RecvTrame_Ex(SOCKET socket,struct trame_ex * Trame,int * len,int * type);
extern int SendTrame(SOCKET socket,struct trame * Trame,int len,int type);
extern int SendTrame_Ex(SOCKET socket,struct trame_ex * Trame,int len,int type);
extern int GetPort(char * service,char * type);
extern SOCKET ConnectHost(char * hostname,unsigned short port);
extern void CloseSocket(SOCKET socket);
extern int RecvLine(SOCKET socket,char * buffer,int maxlen);
extern SOCKET ListenPort(char * serv,char * type,int queue_size);
extern SOCKET ListenPortNumber(unsigned short port,int queue_size);
extern char IsWritable(SOCKET sock_in);

/* Socket UDP */
extern SOCKET ListenUDPPort(unsigned short port);
extern SOCKET_UDP *NewUDPSocket(char * hostname,unsigned short port);
extern int SendToUDPPort(SOCKET_UDP *sock_in,char * buffer_in,int len_in);


/* Outils de debug */
extern char SendComDebug(char * chaine,...);
extern char OpenComDebug(char * host);
extern void CloseComDebug();

#ifdef WIN32
extern int (*RecvSocketFonc)(HWND hWnd,SOCKET sock,int len,char * msg);
extern int (*SendSocketFonc)(HWND hWnd,SOCKET sock);
extern void (*CloseSocketFonc)(HWND hWnd,SOCKET sock);
extern void (*AcceptSocketFonc)(HWND hWnd,SOCKET sock,SOCKET socklistening);
extern void (*ConnectSocketFonc)(HWND hWnd,SOCKET sock,int err);


extern BOOL GereSocketsMsg(HWND hWnd,       /* window handle                   */
        UINT message,             /* type of message                 */
        UINT wParam,              /* additional information          */
        LONG lParam);              /* additional information          */

extern int InitWSA();
extern SOCKET AsyncConnectHost(HWND hwnd,char * hostname,unsigned short port);
extern int AsyncReceive(HWND hwnd,SOCKET sock);
extern void CancelAsyncReceive(HWND hwnd,SOCKET sock);
extern SOCKET AsyncListenPort(HWND hwnd,char * serv,char * type,int queue_size);
extern SOCKET AsyncListenPortNumber(HWND hwnd,unsigned short port,int queue_size);
extern void ClearWSA();
extern void DebugBox(char * chaine,...);

#endif


/* Extensions: en test */
extern int Verify(char * host,unsigned short port,char * passwd);



#endif
