/*********************************/
/* Module de comm TCP/IP         */
/* Windows / Linux / SunOS       */
/* Copyright IT 1996             */
/*                               */
/*                               */
/* Auteur:Franck Maestre 1996    */
/*********************************/

/* ------------------------------------------------------------------
	Attention:
	----------
	Le but de cette librairie est d'apporter la base Client/Serveur
	au niveau  connexion, envoi et reception de trames, ceci sans
	protocole appliqué.
	Cette librairie contient toutes les fonctions de base pour utiliser
	les sockets TCP/IP en mode "Connecté", c'est a dire qu'il faut 
	necessairement faire un ConnectHost("ftp.infogrames.fr",...) par
	exemple pour obtenir un handle sur une socket avant de negocier
	avec le serveur. Les fonctionnalités en mode "non connecté" sont 
	pour bientot, bien que moins necessaires.
	Cette librairie a l'avantage de se compiler aisement sous Windows
	(define WIN32 a inclure) , Linux  et SunOs. Sans avoir pu tester
	encore, je pense qu'elle doit se compiler sous SCO Unix, et Irix 
	(serveurs Silicon Graphics).

	La version Windows necessite Wsock32.dll , qui se trouve normalement
	sous Win3.1 (+ Win32S) , Windows 95, et Windows NT. La librairie
	a ete faite sous Visual C++ 2,et se compile sans modifs sous 
	Visual C++ 4 , BC++5 et Watcom (testé). Cette version comprend
	l'utilisation du mode asynchrone pour la reception de trame, 
	l'acceptation de clients, et la fermeture de connexion.(cf les 
	fonctions Async_xxxx () .

	Les fonctions SendTrame(), SendTrame_Ex(), RecvTrame() et
	RecvTrame_Ex() sont un protocole "de base" tres utilisé:
		Le(s) premier(s) octet(s) de la trame contient(nent) le nombre
		d'octects a lire pour que la reception du paquet soit complete.

	Ce protocole bypasse le phenomene de fragmentation qui peut 
	s'averer frequent sur Internet. Tous les routeurs par exemple ont
	une MTU (Maximum Transmit Unit) definie, lorsqu'un paquet de taille
	superieure au MTU "passe" par ce routeur, il est decoupé en plusieurs
	fragments qui doivent etre re-assemblés ulterieurement.
	Certains routeurs ou passerelles peuvent avoir des MTU de 256 octets,
	la valeur standard etant d'environ 1500 octets.

   ------------------------------------------------------------------ */
#ifdef	WIN32
//#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <process.h>
#else
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/time.h>
#endif


#include "net.h"


/* Prototypages et qques globales */
SOCKET sockdebug=INVALID_SOCKET;
char IsSocketWritable(SOCKET socket);
char IsSocketReadable(SOCKET socket);
int Recv(SOCKET socket,char * buffer,int len);
int Send(SOCKET socket,char * buffer,int len);
int RecvTrame(SOCKET socket,struct trame * Trame,int * len,int * type);
int RecvTrame_Ex(SOCKET socket,struct trame_ex * Trame,int * len,int * type);
int SendTrame(SOCKET socket,struct trame * Trame,int len,int type);
int SendTrame_Ex(SOCKET socket,struct trame_ex * Trame,int len,int type);
int GetPort(char * service,char * type);
SOCKET ConnectHost(char * hostname,unsigned short port);
void CloseSocket(SOCKET socket);
int RecvLine(SOCKET socket,char * buffer,int maxlen);
SOCKET ListenPort(char * serv,char * type,int queue_size);
SOCKET ListenPortNumber(unsigned short port,int queue_size);
char SendComDebug(char * chaine,...);
char OpenComDebug(char * host);
void CloseComDebug();

#ifdef WIN32
static char libnet_wsa_accept[] = "libnet_wsa_accept";
static char libnet_wsa_read[] = "libnet_wsa_read";
static char libnet_wsa_connect[] = "libnet_wsa_connect";
UINT WSA_ACCEPT=0;
UINT WSA_READ=0;
UINT WSA_CONNECT=0;
char buf_interne[2048];
int (*RecvSocketFonc)(HWND hWnd,SOCKET sock,int len,char * msg)=NULL;
int (*SendSocketFonc)(HWND hWnd,SOCKET sock)=NULL;
void (*CloseSocketFonc)(HWND hWnd,SOCKET sock)=NULL;
void (*AcceptSocketFonc)(HWND hWnd,SOCKET sock,SOCKET socklisten)=NULL;
void (*ConnectSocketFonc)(HWND hWnd,SOCKET sock,int err)=NULL;


BOOL GereSocketsMsg(HWND hWnd,    /* handle de la fenetre            */
        UINT message,             /* type de message                 */
        UINT wParam,              /* wParam classique                */
        LONG lParam);             /* lParam classique                */

int InitWSA();
void ClearWSA();
SOCKET AsyncConnectHost(HWND hwnd,char * hostname,unsigned short port);
int AsyncReceive(HWND hwnd,SOCKET sock);
SOCKET AsyncListenPort(HWND hwnd,char * serv,char * type,int queue_size);
SOCKET AsyncListenPortNumber(HWND hwnd,unsigned short port,int queue_size);
void DebugBox(char * chaine,...);
#endif


/*------------------------------------------------------------------------------------------
	Verifie que la socket soit disponible en ecriture
	2 erreur socket non valide
	1 si la socket est disponible
	0 sinon
  ------------------------------------------------------------------------------------------- */
char IsSocketWritable(SOCKET socket)
{
int err;
fd_set write_set;
struct timeval tv;

tv.tv_sec=0;
tv.tv_usec=0;

FD_ZERO(&write_set);
FD_SET(socket,&write_set);

err=select(socket + 1,(struct fd_set *)0,&write_set,(struct fd_set *)0,&tv);

#ifdef	WIN32
if (err == SOCKET_ERROR) return 2;
#else
if (err < 0) return 2;
#endif

if (FD_ISSET(socket,&write_set)) return 1;

return 0;
}

/*------------------------------------------------------------------------------------------
	Verifie que la socket soit disponible en Lecture
	2 erreur socket non valide
	1 si disponible
	0 sinon
  ------------------------------------------------------------------------------------------- */
char IsSocketReadable(SOCKET socket)
{
int err;
fd_set read_set;
struct timeval tv;

tv.tv_sec=0;
tv.tv_usec=0;

FD_ZERO(&read_set);
FD_SET(socket,&read_set);

err=select(socket + 1,(struct fd_set *)&read_set,0,(struct fd_set *)0,&tv);
#ifdef	WIN32
if (err == SOCKET_ERROR) return 2;
#else
if (err < 0) return 2;
#endif
if (FD_ISSET(socket,&read_set)) return 1;
return 0;
}


/*------------------------------------------------------------------------------------------
	Initialise la structure ptclient pour ManageLibnetClient 
  ------------------------------------------------------------------------------------------- */
int InitLibnetClient(LIBNET_CLIENT *ptclient,SOCKET socket)
{
if (ptclient == NULL) return -1;

memset(ptclient,0,sizeof(LIBNET_CLIENT));
ptclient->socket=socket;
ptclient->index=-2;
return 0;
}

/*------------------------------------------------------------------------------------------
	Permet de reassembler des packets provenant du
	client "ptclient" pour traiter les defragmentations des 
	trames. TRAME_EX uniquement
  ------------------------------------------------------------------------------------------- */
int ManageLibnetClient(LIBNET_CLIENT *  ptclient,char *buffer,int len,void (*ReceiveCallback)(LIBNET_CLIENT *,TRAME_EX *,int) )
{
int err=0,reste,curr;

if (ptclient == NULL) return -1;

#ifdef LIBNET_DEBUG
SendComDebug("Entree Windows_Client_ManageDatas(SOCKET %d,len=%d)",ptclient->socket,len);
#endif

reste=len;

while(reste > 0)
	{
	curr=len - reste;
	/* on recoit le maximum de donnees a la fois */
	switch(ptclient->index)
		{
		case -2:
			{
			if (reste > 0)
				{
				ptclient->index=-1;
				ptclient->buffer[0]=buffer[curr];
				ptclient->ptr=0;
				reste--;
				}
			else
				err=-1;
			}
		break;
		case -1:
			{
			if (reste > 0)
				{
				ptclient->buffer[1]=buffer[curr];
				ptclient->index=(int)(unsigned char)buffer[curr];
				ptclient->index+=(int)((unsigned char)ptclient->buffer[0])*256 - 2;
				ptclient->ptr=0;
				reste--;
				}
			else
				err=-1;
			}
			break;


		default:
			{
			if (reste >= ptclient->index)
				{
				memcpy(&(ptclient->buffer[ptclient->ptr+2]),&buffer[curr],ptclient->index);
				reste-=ptclient->index;
				ptclient->ptr+=ptclient->index;
				ptclient->index=0;

				ReceiveCallback(ptclient,(TRAME_EX *)ptclient->buffer,ptclient->ptr+1);

				ptclient->index=-2;
				}
			else
				{ 
				memcpy(&(ptclient->buffer[ptclient->ptr+2]),&buffer[curr],reste);
				ptclient->ptr+=reste;
				ptclient->index-=reste;
				err=1;
				}
			}
		break;
		}

	if (err==1)
		{
/*		SendComDebug("Err=1 ? wow buffer libnet atteint !"); */
		break;
		}
	if (err == -1) /* probleme de comm avec ce client */
		{
		/* probleme au reassemblage des  packets */
		break;
		}

	}

return 0;
}



/*--------------------------------------------------------------------
  Reception d'une trame de longueur len en evitant les fragmentations 
	return 0 si la trame a ete envoyee
		-1 si erreur de comm
  --------------------------------------------------------------------*/
int Recv(SOCKET socket,char * buffer,int len)
{
int err,total=0;

while((len - total) > 0)
	{
	err=recv(socket,&buffer[total],len - total,0);
		
#ifdef WIN32
	if (err == SOCKET_ERROR)
#else
	if (err <= 0)
#endif
		{
#ifdef WIN32
  #ifdef LIBNET_DEBUG
		char mess[128];
		sprintf(mess,"Erreur Recv=%d",WSAGetLastError());
		MessageBox(0,mess,"Recv():",MB_OK);
  #endif
#else
		perror("Recv:recv");
#endif
		return -1; /* Probleme grave */
		}
	total+=err;
	}
return (0);
}

/*--------------------------------------------------------------------
  Send : Envoie d'une trame de longueur len sans fragments
  	renvoie 0 si trame envoyee
  		-1 si probleme de comm
  --------------------------------------------------------------------*/
int Send(SOCKET socket,char * buffer,int len)
{
int err,total=0;

while ( (len - total) > 0 )
	{
	err=send(socket,&(buffer[total]),len - total,0);
#ifdef WIN32
	if (err == SOCKET_ERROR)
		{
		err=WSAGetLastError();
		SendComDebug("Erreur Send() GetLastError=%d",err);
		if (err == 10035) /* WSA_EWOULDBLOCK */
			{
			if (total != 0) return -1; /* irreparable */
			return -2; /* Socket non dispo */
			}
		}
#else
	/* On teste s'il ne s'agit pas d'une saturation */
	if (err == -1)
		{
		if (errno==EWOULDBLOCK)
			{
			return -2;
			}
		}
#endif
	if (err <= 0) return -1; /* Probleme grave  */
	total+=err;
	}
	
return (0);
}

/*--------------------------------------------------------------------
  CloseSocket : Termine une connexion.
  	renvoie 0 si trame envoyee
  		-1 si probleme de comm
  --------------------------------------------------------------------*/
void CloseSocket(SOCKET socket)
{
#ifdef WIN32
closesocket(socket);
#else
close(socket);
#endif
}

/*--------------------------------------------------------------------
  RecvLine : Reception d'une trame se terminant par CR LF
	retourn le nombre de caracteres lus
		-1 si prob de comm
  --------------------------------------------------------------------*/
int RecvLine(SOCKET socket,char * buffer,int maxlen)
{
int total=0,mode=0;
char car;

while(1)
	{
	
	if (Recv(socket,&car,1) != 0) return -1;
	buffer[total]=car;
	total++;
	if ((car == LF) && (mode)) break;
	if (car == CR)
		mode=1;
	else
		mode=0; 
	if (total == maxlen) break;
	}
return total;
}

/*--------------------------------------------------------------------
  RecvTrame : Reception d'une trame totale avec entete (256 cars maxi)
 	renvoie 0 si trame recue
 		-1 si erreur de communication
  --------------------------------------------------------------------*/
int RecvTrame(SOCKET socket,struct trame * Trame,int * len,int * type)
{
if (Recv(socket,(char *)Trame,2) != 0)
	{
	perror("RecvTrame(2)");
	return -1;
	}

*type=(unsigned char)(int)Trame->type;
*len=(unsigned char)(int)Trame->len;

if (Recv(socket,(char *)&(Trame->data),(unsigned char)(int)Trame->len-2) != 0)
	{
	perror("RecvTrame(longueur)");
	return -1;
	}

return 0;
}

/*--------------------------------------------------------------------
  SendTrame : Envoie une trame avec entete (256 cars maxi)
  	renvoie 0 si trame envoyee
  		-1 si probleme de comm
  --------------------------------------------------------------------*/
int SendTrame(SOCKET socket,struct trame * Trame,int len,int type)
{
	if (len > 250) return -1;

Trame->len=(unsigned char)(len + 2);
Trame->type=(unsigned char)type;

return Send(socket,(char *)Trame,len + 2);
}

/*--------------------------------------------------------------------
  RecvTrame_Ex : Reception d'une trame etendue totale avec son entete
 	renvoie 0 si trame recue
 		-1 si erreur de communication
  --------------------------------------------------------------------*/
int RecvTrame_Ex(SOCKET socket,struct trame_ex * Trame,int * len,int * type)
{
if (Recv(socket,(char *)Trame,3) != 0)
	{
	perror("RecvTrame_Ex(3)");
	return -1;
	}

*type=(unsigned char)(int)Trame->type;
*len=(unsigned char)(int)(Trame->len1*256) + (unsigned char)(int)(Trame->len2);


if (Recv(socket,(char *)&(Trame->data),*len - 3) != 0)
	{
	perror("RecvTrame_Ex(longueur)");
	return -1;
	}

return 0;
}

/*--------------------------------------------------------------------
  SendTrame_Ex: Envoie une trame etendue(longueur > 256) avec entete
  	renvoie 0 si trame envoyee
  		-1 si probleme de comm
  --------------------------------------------------------------------*/
int SendTrame_Ex(SOCKET socket,struct trame_ex * Trame,int len,int type)
{
int lenloc;

lenloc=len+3;
Trame->len1=(unsigned char)(lenloc / 256);
Trame->len2=(unsigned char)(lenloc - ((lenloc / 256) * 256) );
Trame->type=(unsigned char)type;

return Send(socket,(char *)Trame,lenloc);
}

/*--------------------------------------------------------------------
  Renvoie le numero de port IP associe au service type "tcp" ou "udp"
    -1 si non trouve
  --------------------------------------------------------------------*/
int GetPort(char * service,char * type)
{
struct servent * sp;

sp=getservbyname(service,type);
if (sp==NULL) return(-1);
return (int)(sp->s_port);
}

/*--------------------------------------------------------------------
  ConnectHost Renvoie une socket si connecte a l'hote "hostname"
  	-1 si err de connexion
  --------------------------------------------------------------------*/
SOCKET ConnectHost(char * hostname,unsigned short port)
{
struct sockaddr_in sin;
struct hostent * hp=NULL;
SOCKET s;
int err;

#ifdef LIBNET_DEBUG
MessageBox( 0, "Passage ConnectHost", "", MB_OK);
#endif
memset((char *)&sin,0,sizeof(sin));

/* Verifie s'il s'agit d'une adresse IP */
sin.sin_addr.s_addr=inet_addr(hostname);
#ifdef WIN32
if (sin.sin_addr.s_addr==INADDR_NONE) 	
	{
	hp = gethostbyname(hostname);
	if (hp == NULL)
		return INVALID_SOCKET;
	else memcpy((char *)&sin.sin_addr,hp->h_addr,hp->h_length);
	}
#else
if (sin.sin_addr.s_addr==(unsigned long)-1)
	{
	hp = gethostbyname(hostname);
	if (hp == NULL)
		return INVALID_SOCKET;
	else memcpy((char *)&sin.sin_addr,hp->h_addr,hp->h_length);
	}
#endif

#ifdef LIBNET_DEBUG
MessageBox( 0, "Passage ConnectHost2", hostname , MB_OK);
#endif

sin.sin_family = AF_INET;
sin.sin_port = htons(port);

#ifdef WIN32
if ((s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET) return INVALID_SOCKET;
#else
if ((s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0) return INVALID_SOCKET;
#endif


#ifdef LIBNET_DEBUG
MessageBox( 0, "Passage ConnectHost3", "socket OK" , MB_OK);
#endif

err=connect(s , (struct sockaddr *)&sin ,sizeof(sin));
if (err != 0)
	{
	closesocket(s);
	return INVALID_SOCKET;
	}
#ifdef LIBNET_DEBUG
MessageBox( 0, "Passage ConnectHost4", "connect OK" , MB_OK);
#endif 
return (s);
}

/*--------------------------------------------------------------------
  ListenPort Renvoie une socket a l'ecoute de connection sur le 
  		service serv de type "tcp" ou "udp".
  		queue_size specifie le nombre de connexion pouvant etre
  		en attente.
  	-1 si err de connexion
  --------------------------------------------------------------------*/
SOCKET ListenPort(char * serv,char * type,int queue_size)
{
SOCKET sock;
int namelen;
struct servent * service;
struct sockaddr_in sin={ AF_INET };

#ifdef WIN32
if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
#else
if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
#endif
	{
	perror("ListenPort:socket");
	return INVALID_SOCKET;
	}
if ((service=getservbyname(serv,type))==NULL)
	{
	perror("ListenPort:getservbyname");
	closesocket(sock);
	return INVALID_SOCKET;
	}

sin.sin_port = service->s_port;
if (bind(sock,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
	perror("ListenPort:bind");
	closesocket(sock);
	return INVALID_SOCKET;
	}
namelen=sizeof(sin);
if (getsockname(sock,(struct sockaddr *)&sin,&namelen) < 0)
	{
	perror("ListenPort:getsockname");
	closesocket(sock);
	return INVALID_SOCKET;
	}
if (listen(sock,queue_size) < 0)
	{
	perror("ListenPort:getsockname");
	closesocket(sock);
	return INVALID_SOCKET;
	}

return (sock);
}

/*--------------------------------------------------------------------
  ListenPortNumber Renvoie une socket a l'ecoute de connection sur le 
  		port [port].
  		queue_size specifie le nombre de connexion pouvant etre
  		en attente.
  	-1 si err de connexion
  --------------------------------------------------------------------*/
SOCKET ListenPortNumber(unsigned short port,int queue_size)
{
SOCKET sock;
int namelen;
struct sockaddr_in sin={ AF_INET };

#ifdef WIN32
if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
#else
if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
#endif
	{
	perror("ListenPort:socket");
	return INVALID_SOCKET;
	}

sin.sin_port = htons(port);
if (bind(sock,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
	perror("ListenPort:bind");
	closesocket(sock);
	return INVALID_SOCKET;
	}
namelen=sizeof(sin);
if (getsockname(sock,(struct sockaddr *)&sin,&namelen) < 0)
	{
	perror("ListenPort:getsockname");
	closesocket(sock);
	return INVALID_SOCKET;
	}
if (listen(sock,queue_size) < 0)
	{
	perror("ListenPort:getsockname");
	closesocket(sock);
	return INVALID_SOCKET;
	}

return (sock);
}



/* ----------------------------------------------------------------
	ListenUDPPort : Non documentée pour l'instant
   ---------------------------------------------------------------- */
SOCKET ListenUDPPort(unsigned short port)
{
SOCKET sock;
struct sockaddr_in me;
struct hostent *myhost;

if ((myhost=gethostbyname("localhost"))==NULL)
	{
	perror("ListenUDPPort:gethostbyname");
	return INVALID_SOCKET;
	}

sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
#ifdef WIN32
if (sock==INVALID_SOCKET)
#else
if (sock < 0)
#endif
	{
	perror("ListenUDPPort:socket");
	return INVALID_SOCKET;
	}

memset(&me,0,sizeof(me));
me.sin_family=AF_INET;
me.sin_port=htons(port);
memcpy(&me.sin_addr,myhost->h_addr,myhost->h_length);
if (bind(sock,(struct sockaddr *)&me,sizeof(me)) != 0)
	{
	perror("ListenUDPPort:bind");
	closesocket(sock);
	return INVALID_SOCKET;
	}


return (sock);
}


/* ----------------------------------------------------------------
	Creation d'une socket passive  UDP pour faire des envois sur
	un host particulier
   ---------------------------------------------------------------- */
SOCKET_UDP *NewUDPSocket(char * hostname,unsigned short port)
{
SOCKET sock;
struct sockaddr_in sin;
struct hostent * hp=NULL;
SOCKET_UDP * retour;

if ((retour=(SOCKET_UDP *)malloc(sizeof(SOCKET_UDP))) == NULL) return NULL;

memset((char *)&sin,0,sizeof(sin));

// La socket
retour->sin.sin_family = AF_INET;
retour->sin.sin_port = htons(port);

sock=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
#ifdef WIN32
if (sock==INVALID_SOCKET)
	{
#ifdef LIBNET_DEBUG
	DebugBox("NewUDPSocket:\nError during socket()");
#endif

#else
if (sock < 0)
	{
	perror("NewUDPSocket:socket");
#endif
	free(retour);
	return NULL;
	}
retour->sock=sock;

/* Verifie s'il s'agit d'une adresse IP */
retour->sin.sin_addr.s_addr=inet_addr(hostname);
#ifdef WIN32
if (retour->sin.sin_addr.s_addr==INADDR_NONE) 	
	{
	hp = gethostbyname(hostname);
	if (hp == NULL)
		{
#ifdef LIBNET_DEBUG
		DebugBox("NewUDPSocket:\nError during gethostbyname()");
#endif
		free(retour);
		return NULL;
		}
	memcpy((char *)&retour->sin.sin_addr,hp->h_addr,hp->h_length);
	retour->len_addr=hp->h_length;
	}
#else
if (retour->sin.sin_addr.s_addr==(unsigned long)-1)
	{
	hp = gethostbyname(hostname);
	if (hp == NULL)
		{
		free(retour);
		return NULL;
		}
	memcpy((char *)&retour->sin.sin_addr,hp->h_addr,hp->h_length);
	retour->len_addr=hp->h_length;
	}
#endif


return (retour);
}

/* ----------------------------------------------------------------
	Envoi de donnees sur une socket UDP
   ---------------------------------------------------------------- */
int SendToUDPPort(SOCKET_UDP *sock_in,char * buffer_in,int len_in)
{
int err;

err=sendto(sock_in->sock,buffer_in,len_in,0,(struct sockaddr *)&sock_in->sin,sock_in->len_addr);

if (err <= 0)
	{
#ifdef LIBNET_DEBUG
	DebugBox("SendToUDPPort:\nError during sendto()");
#endif
	}

#ifdef WIN32
if (WSAGetLastError() == WSAEWOULDBLOCK) return -2;
#else
if (errno==EWOULDBLOCK) return -2;
#endif
if (err <= 0) return -1;

return 0;
}

//
// Test de disponibilite en ecriture d'une socket
//
char IsWritable(SOCKET sock_in)
{
int err;
fd_set write_set;
struct timeval tv;

tv.tv_sec=0;
tv.tv_usec=0;

FD_ZERO(&write_set);
FD_SET(sock_in,&write_set);

err=select(sock_in + 1,(struct fd_set *)0,&write_set,(struct fd_set *)0,&tv);

if (err < 0) return 0;

if (FD_ISSET(sock_in,&write_set)) return 1;

return 0;
}




/*--------------------------------------------------------------------
	Fonctions specifiques a Windows
  --------------------------------------------------------------------*/

#ifdef WIN32

int InitWSA()
{
int status;
WSADATA WSAData;

if ((status=WSAStartup(MAKEWORD(1,1), &WSAData)) == 0) 
	{
	//MessageBox( hWnd, WSAData.szDescription, WSAData.szSystemStatus, MB_OK);
	if ((WSA_READ=RegisterWindowMessage(libnet_wsa_read)) != 0)
		if ((WSA_ACCEPT=RegisterWindowMessage(libnet_wsa_accept)) != 0)
			if ((WSA_CONNECT=RegisterWindowMessage(libnet_wsa_connect)) != 0)
				return 0;
	}
else 
	{
#ifdef LIBNET_DEBUG
	DebugBox( "erreur WSAStartup:%d", status);
#endif
	}

return -1;
}

void ClearWSA()
{
WSACleanup();
}

/*--------------------------------------------------------------------
  AsyncConnectHost: Connexion Asynchrone a une socket
  	-1 si err de a l'initialisation
  --------------------------------------------------------------------*/
SOCKET AsyncConnectHost(HWND hwnd,char * hostname,unsigned short port_in)
{
struct sockaddr_in sin;
struct sockaddr_in sin_bind;
struct hostent * hp=NULL;
SOCKET s;
int err;

#ifdef LIBNET_DEBUG
MessageBox( 0, "Passage AsyncConnectHost", "", MB_OK);
#endif

memset(&sin_bind, 0, sizeof(struct sockaddr_in));
sin_bind.sin_addr.s_addr = htonl(INADDR_ANY);
sin_bind.sin_family = AF_INET;
sin_bind.sin_port = htons(0);

memset((char *)&sin,0,sizeof(struct sockaddr_in));
sin.sin_family = AF_INET;
sin.sin_port = htons(port_in);

/* Verifie s'il s'agit d'une adresse IP */
sin.sin_addr.s_addr=inet_addr(hostname);
if (sin.sin_addr.s_addr==INADDR_NONE) 	
	{
	/* acces DNS si necessaire */
	hp = gethostbyname(hostname);
	if (hp == NULL)
		return INVALID_SOCKET;
	else memcpy((char *)&sin.sin_addr,hp->h_addr,hp->h_length);
	}

#ifdef LIBNET_DEBUG
MessageBox( 0, "Passage AsyncConnectHost2", hostname , MB_OK);
#endif

if ((s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET) return INVALID_SOCKET;

#ifdef LIBNET_DEBUG
MessageBox( 0, "Passage AsyncConnectHost3", "socket OK" , MB_OK);
#endif


// On binde
if (bind(s, (struct sockaddr *)&sin_bind, sizeof(struct sockaddr_in)) == SOCKET_ERROR)
	{
	closesocket(s);
#ifdef LIBNET_DEBUG
	MessageBox( 0, "Erreur Bind AsyncConnectHost3", "socket ERR" , MB_OK);
#endif
	return INVALID_SOCKET;
	}

// Mode Asynchrone
if (WSAAsyncSelect(s, hwnd, WSA_CONNECT,FD_CONNECT) ==SOCKET_ERROR)
	{
#ifdef LIBNET_DEBUG
	MessageBox( 0, "Erreur WSAAsyncSelect() AsyncConnectHost4", "socket ERR" , MB_OK);
#endif
	closesocket(s);
	return INVALID_SOCKET;
	}


#ifdef LIBNET_DEBUG
MessageBox( 0, "Passage AsyncConnectHost4", hostname , MB_OK);
#endif

// On connecte et Windows nous enverra un message
if (connect(s, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)) != 0) 
	{
	err=WSAGetLastError();
	if(err!=WSAEWOULDBLOCK)
		{
		closesocket(s);
#ifdef LIBNET_DEBUG
		DebugBox("Erreur connect() AsyncConnectHost6 WSAGetLastError=%d errno=%d",err,errno);
#endif
		return INVALID_SOCKET;
		}
	}
else
	{
#ifdef LIBNET_DEBUG
	DebugBox("connect() OK");
#endif
	}	

return (s);
}


/*--------------------------------------------------------------------
  AsyncReceive Renvoie un message FD_READ ou FD_CLOSE a la fenetre
  	hwnd en cas d'evenement sur la socket sock.

  	-1 si err de connexion
  --------------------------------------------------------------------*/

int AsyncReceive(HWND hwnd,SOCKET sock)
{
int status;
char tmp[128];
 
if ((status = WSAAsyncSelect( sock, hwnd, WSA_READ, FD_READ | FD_CLOSE | FD_WRITE )) > 0)
	{
	wsprintf(tmp, "Erreur WSAAsyncSelect %d (0x%x) FD_READ",status,status);
	MessageBox( hwnd, "AsyncReceive:", tmp , MB_OK);
	closesocket( sock );
	return -1;
	}

return 0;
}

/*--------------------------------------------------------------------
  CancelAsyncReceive : Annule la reception Asynchrone
  --------------------------------------------------------------------*/
void CancelAsyncReceive(HWND hwnd,SOCKET sock)
{
WSAAsyncSelect( sock, hwnd, 0,0);
}


/*--------------------------------------------------------------------
  AsyncListenProt Renvoie une socket a l'ecoute de connection sur le 
  		service serv de type "tcp" ou "udp".
  		queue_size specifie le nombre de connexion pouvant etre
  		en attente.

  	-1 si err de connexion
  --------------------------------------------------------------------*/
SOCKET AsyncListenPort(HWND hwnd,char * serv,char * type,int queue_size)
{
int status;
char tmp[128];
SOCKET sock;
int namelen;
struct servent * service;
struct sockaddr_in sin={ AF_INET };


#ifdef WIN32
if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
#else
if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
#endif
	{
	perror("ListenPort:socket");
	return INVALID_SOCKET;
	}
if ((service=getservbyname(serv,type))==NULL)
	{
	perror("ListenPort:getservbyname");
	closesocket(sock);
	return INVALID_SOCKET;
	}

sin.sin_port = service->s_port;
if (bind(sock,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
	perror("ListenPort:bind");
	closesocket(sock);
	return INVALID_SOCKET;
	}
namelen=sizeof(sin);
if (getsockname(sock,(struct sockaddr *)&sin,&namelen) < 0)
	{
	perror("ListenPort:getsockname");
	closesocket(sock);
	return INVALID_SOCKET;
	}
if (listen(sock,queue_size) < 0)
	{
	perror("ListenPort:getsockname");
	closesocket(sock);
	return INVALID_SOCKET;
	}

if ((status = WSAAsyncSelect( sock, hwnd, WSA_ACCEPT, FD_ACCEPT)) > 0)
	{
	wsprintf( tmp, "%d (0x%x)");
	MessageBox( hwnd, "Erreur WSAAsyncSelect()", tmp, MB_OK);
	SetWindowText( hwnd, "AsyncListenPort");
	closesocket( sock );
	}

return (sock);
}

/*--------------------------------------------------------------------
  AsyncListenPortNumber Renvoie une socket a l'ecoute de connection sur le 
  		port tcp [port].
  		queue_size specifie le nombre de connexion pouvant etre
  		en attente.

  	-1 si err de connexion
  --------------------------------------------------------------------*/
SOCKET AsyncListenPortNumber(HWND hwnd,unsigned short port,int queue_size)
{
int status;
char tmp[128];
SOCKET sock;
int namelen;
struct sockaddr_in sin={ AF_INET };


#ifdef WIN32
if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
#else
if ((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) < 0)
#endif
	{
	perror("ListenPort:socket");
	return INVALID_SOCKET;
	}

sin.sin_port = htons(port);
if (bind(sock,(struct sockaddr *)&sin,sizeof(sin)) < 0)
	{
	perror("ListenPort:bind");
	closesocket(sock);
	return INVALID_SOCKET;
	}
namelen=sizeof(sin);
if (getsockname(sock,(struct sockaddr *)&sin,&namelen) < 0)
	{
	perror("ListenPort:getsockname");
	closesocket(sock);
	return INVALID_SOCKET;
	}
if (listen(sock,queue_size) < 0)
	{
	perror("ListenPort:getsockname");
	closesocket(sock);
	return INVALID_SOCKET;
	}

if ((status = WSAAsyncSelect( sock, hwnd, WSA_ACCEPT, FD_ACCEPT)) > 0)
	{
	wsprintf( tmp, "%d (0x%x)");
	MessageBox( hwnd, "Erreur WSAAsyncSelect()", tmp, MB_OK);
	SetWindowText( hwnd, "AsyncListenPort");
	closesocket( sock );
	}

return (sock);
}

/*--------------------------------------------------------------------
  --------------------------------------------------------------------*/
BOOL GereSocketsMsg(HWND hWnd,       /* window handle                   */
        UINT message,             /* type of message                 */
        UINT wParam,              /* additional information          */
        LONG lParam)              /* additional information          */
{

if(message==WSA_CONNECT)
	{
	switch(WSAGETSELECTEVENT(lParam))
		{
		case FD_CONNECT: // nouvelle connection
			{
			SOCKET socktmp;
			int err;
			socktmp=(SOCKET)wParam;
			err = (int)WSAGETSELECTERROR(lParam);
			if (err != 0) // erreur a la connexion 
				WSAAsyncSelect( socktmp, hWnd,0,0);

			if (ConnectSocketFonc != NULL) ConnectSocketFonc(hWnd,socktmp,err);
			}
			return TRUE;

		default:// ??? pas pour moi
#ifdef LIBNET_DEBUG
			MessageBox(hWnd,"Erreur WSA_CONNECT: Unknown Event ?","WSA_CONNECT",MB_OK);
#endif
			return TRUE;
		}
	}
else if(message==WSA_ACCEPT)
	{
	if (WSAGETSELECTERROR( lParam ) == 0) 
	    {
		SOCKADDR_IN acc_sin;    /* Accept socket address */
		int acc_sin_len;        /* Accept socket address length */
		SOCKET socklisten;		/* Listening Socket */
		SOCKET newsock;			/* New accepted Socket */
		
		acc_sin_len = sizeof( acc_sin );
		socklisten=(SOCKET)wParam;

		newsock = accept(socklisten,(struct sockaddr FAR *) &acc_sin,
			(int FAR *) &acc_sin_len );

// FM: enleve pour pouvoir configurer Asynchrone / MultiThreading
//		AsyncReceive(hWnd,newsock);

		if (AcceptSocketFonc != NULL)
			AcceptSocketFonc(hWnd,newsock,socklisten);
		else
			{
			// Ferme la porte a toute connection entrante
			if (CloseSocketFonc != NULL)
				{
				CloseSocketFonc(hWnd,newsock);
				}
			else
				{
// FM: idem, voir 14 lignes au dessus
//				WSAAsyncSelect(newsock,hWnd, 0, 0);
				closesocket(newsock);
				newsock=INVALID_SOCKET;
				}
			}

		}
	return TRUE;
	}

else if (message == WSA_READ)
		{
		SOCKET socktmp;

		switch(WSAGETSELECTEVENT(lParam))
			{
			case FD_WRITE:
				socktmp=(SOCKET)wParam;
				if (SendSocketFonc != NULL) SendSocketFonc(hWnd,socktmp);
				return TRUE;

	      	case FD_READ:
	      		{
				int err;

				socktmp=(SOCKET)wParam;

				if ((err=(int)recv(socktmp,buf_interne,sizeof(buf_interne),0)) != SOCKET_ERROR)
					{
					if (err > 0)
						if (RecvSocketFonc != NULL) RecvSocketFonc(hWnd,socktmp,err,buf_interne);
					return TRUE;
					}
				else
					{
#ifdef LIBNET_DEBUG
					MessageBox(hWnd,"Erreur Recv","WSA_READ",MB_OK);
#endif
					// Il a ete chiant a trouver celui la ...
					if (WSAGetLastError() == WSAEWOULDBLOCK) return TRUE ; 
					if (CloseSocketFonc != NULL)
						{
						CloseSocketFonc(hWnd,socktmp);
						}
					else
						{
						closesocket(socktmp);
						socktmp=INVALID_SOCKET;
						}
					}
				}
				return TRUE;

			case FD_CLOSE:
				socktmp=(SOCKET)wParam;
#ifdef LIBNET_DEBUG
				MessageBox( hWnd, "Connection perdue (FD_CLOSE)", "WSA_READ", MB_OK);
#endif

				if (CloseSocketFonc != NULL)
					{
					CloseSocketFonc(hWnd,socktmp);
					}
				else
					{
					closesocket(socktmp);
					socktmp=INVALID_SOCKET;
					}
				return TRUE;
			}

		}

return FALSE;
}

/* ----------------------------------------------------------------
   ---------------------------------------------------------------- */
void DebugBox(char * chaine,...)
{
va_list	va ;
char	text[512] ;

va_start (va, chaine) ;
vsprintf (text, chaine, va) ;

MessageBox (0, text, "", MB_OK) ;

va_end (va) ;

return;
}


#endif


/* ----------------------------------------------------------------



	Extension pour le debuggage



   ---------------------------------------------------------------- */



/* ----------------------------------------------------------------
   ---------------------------------------------------------------- */
char OpenComDebug(char * host)
{
/* Sur le port Telnet */
sockdebug=ConnectHost(host,23);
if (sockdebug == INVALID_SOCKET)
	{
	/*DebugBox("Erreur ConnectHost %s !",host);*/
	return 0;
	}

return 1;
}


/* ----------------------------------------------------------------
   ---------------------------------------------------------------- */

void CloseComDebug()
{
if (sockdebug != INVALID_SOCKET)
	{
	closesocket(sockdebug);
	sockdebug=INVALID_SOCKET;
	}
return ;
}


/* ----------------------------------------------------------------
   ---------------------------------------------------------------- */
char SendComDebug(char * chaine,...)
{
va_list	va ;
char	text[1024] ;
int err;

if (sockdebug == INVALID_SOCKET) return 0;
err=IsSocketWritable(sockdebug);
if (err==0) /* pas disponible */
	{
	return 0;
	}
else if (err==2) /* probleme avec cette socket */
	{
	sockdebug=INVALID_SOCKET;
	return 0;
	}

va_start (va, chaine) ;
vsprintf (text, chaine, va) ;

if (Send(sockdebug,text,strlen(text)+1) != 0)
	{
	closesocket(sockdebug);
	sockdebug=INVALID_SOCKET;
	return 0;
	}

if (Send(sockdebug,"\r",1) != 0)
	{
	closesocket(sockdebug);
	sockdebug=INVALID_SOCKET;
	return 0;
	}

va_end (va) ;

return 1;
}


