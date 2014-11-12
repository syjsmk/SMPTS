#include "PrecompiledHeader.h"

AccountSystem* makeAccountSystem() {
  printf("initAccountSystem\n");

  AccountSystem* accountSystem = (AccountSystem *)malloc(sizeof(AccountSystem));
  accountSystem->terminalInterface = makeTerminamInterface();

  printf("before socketFd = %d\n", accountSystem->socketFd);

  accountSystem->socketFd = socket(AF_INET, SOCK_STREAM, 0);

  printf("after socketFd = %d\n", accountSystem->socketFd);

  accountSystem->accountSystemAddr.sin_family = AF_INET;
  accountSystem->accountSystemAddr.sin_addr.s_addr = INADDR_ANY;
  accountSystem->accountSystemAddr.sin_port = htons(PORTNUMBER);



  // set function to function pointer of AccountSystem
  accountSystem->run = &run;
  accountSystem->getDailyData = &getDailyData;

  
  return accountSystem;

}

void run(AccountSystem* self) {

  self->terminalInterface->listenTerminal(self->terminalInterface);

  printf("run\n");
}

// 이 함수 호출 시 실제로 소켓 열어서 통신해서 값을 가져오게 할 것
void getDailyData(AccountSystem* self, int type) {

  printf("getDailyData\n");

  switch(type) {
  case BUSTERMINAL:
    printf("get daily information from bus terminal\n");
    break;
  case METROTERMINAL:
    printf("get daily information from metro terminal\n");
    break;

  default:
    break;
  }

}
