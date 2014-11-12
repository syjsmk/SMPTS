#define BUSTERMINAL 1
#define METROTERMINAL 2
#define PORTNUMBER 9876

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


typedef struct AccountSystem {

  int socketFd, busTerminalAddrLength, metroTerminalAddrLength, newSocketFd;
  struct sockaddr_in accountSystemAddr, busTerminalAddr, metroTerminalAddr;
  void (*run)();
  void (*getDailyData)();


} AccountSystem;


AccountSystem* makeAccountSystem();
void run();
void getDailyData(int type);
