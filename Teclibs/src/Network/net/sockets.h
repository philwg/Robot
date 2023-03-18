#ifdef WIN32
  // Les sockets windows
  #include <winsock.h>
  #include <stdio.h>
  #include <string.h>
  #include <memory.h>
  #include <process.h>
  #include <time.h>

  // La lib Winsock (uncomaptible avec les standtars Unix...)
  #pragma comment (lib,"ws2_32.lib.")

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

  void DebugBox(char * chaine) {printf("%s\n",chaine);};


#endif


