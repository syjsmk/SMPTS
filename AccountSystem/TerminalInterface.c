#include "PrecompiledHeader.h"

TerminalInterface* makeTerminamInterface() {

    printf("makeTerminamInterface\n");

    TerminalInterface* terminalInterface = (TerminalInterface *)malloc(sizeof(TerminalInterface));

    printf("before socketFd = %d\n", terminalInterface->socketFd);

    terminalInterface->socketFd = socket(AF_INET, SOCK_STREAM, 0);

    printf("after socketFd = %d\n", terminalInterface->socketFd);


    terminalInterface->interfaceAddr.sin_family = AF_INET;
    terminalInterface->interfaceAddr.sin_addr.s_addr = INADDR_ANY;
    terminalInterface->interfaceAddr.sin_port = htons(PORTNUMBER);

    if (bind(terminalInterface->socketFd, (struct sockaddr *) &(terminalInterface->interfaceAddr), sizeof(terminalInterface->interfaceAddr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }



    // 함수포인터 세팅
    terminalInterface->listenTerminal = &listenTerminal;
    terminalInterface->writeDailyAccountInformation = &writeDailyAccountInformation;

    return terminalInterface;
}

void listenTerminal(TerminalInterface* self) {
    printf("listenTerminal\n");

    listen(self->socketFd, 5);
    self->terminalAddrLength = sizeof(self->terminalAddr);

    self->newSocketFd = accept(self->socketFd, (struct sockaddr *)&(self->terminalAddr), &(self->terminalAddrLength));

}

DailyAccountInformation writeDailyAccountInformation(TerminalInterface* self) {
    printf("writeDailyAccountInformation\n");
}