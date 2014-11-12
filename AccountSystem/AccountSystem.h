#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "CommunicationDefinition.h"


struct TerminalInterface;
typedef struct AccountSystem {

  struct TerminalInterface* terminalInterface;

  int socketFd, busTerminalAddrLength, metroTerminalAddrLength, newSocketFd;
  struct sockaddr_in accountSystemAddr, busTerminalAddr, metroTerminalAddr;
  void (*run)(struct AccountSystem* self);
  void (*getDailyData)(struct AccountSystem* self, int type);


} AccountSystem;


AccountSystem* makeAccountSystem();
void run(AccountSystem* self);
void getDailyData(AccountSystem* self, int type);
