#include "../PrecompiledHeader.h"

TerminalInterface* newTerminalInterfaceForServer() {

    printf("TerminalInterface::newTerminalInterfaceForServer\n");

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
    terminalInterface->sendData = &sendData;

    return terminalInterface;
}


TerminalInterface* newTerminalInterfaceForClient() {

    printf("TerminalInterface::newTerminalInterfaceForServer\n");

    TerminalInterface* terminalInterface = (TerminalInterface *)malloc(sizeof(TerminalInterface));

    printf("before socketFd = %d\n", terminalInterface->clientSocketFd);

    terminalInterface->clientSocketFd = socket(PF_INET, SOCK_STREAM, 0);

    printf("after socketFd = %d\n", terminalInterface->clientSocketFd);


    terminalInterface->serverAddr.sin_family = AF_INET;
    terminalInterface->serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    terminalInterface->serverAddr.sin_port = htons(PORTNUMBER);


    // 함수포인터 세팅
    terminalInterface->listenTerminal = &listenTerminal;
    terminalInterface->writeDailyAccountInformation = &writeDailyAccountInformation;
    terminalInterface->sendData = &sendData;

    return terminalInterface;
}

void listenTerminal(TerminalInterface* self) {
    printf("TerminalInterface::listenTerminal\n");

    listen(self->socketFd, 5);
    self->terminalAddrLength = sizeof(self->terminalAddr);

    self->newSocketFd = accept(self->socketFd, (struct sockaddr *)&(self->terminalAddr), &(self->terminalAddrLength));

    //이 아래에서 write

    if(self->newSocketFd < 0) {
        perror("accept error");
    }

    recv(self->newSocketFd, &(self->terminalType), sizeof(int), 0);
    printf("recv data : %d\n", self->terminalType);


}

DailyAccountInformation writeDailyAccountInformation(TerminalInterface* self) {
    printf("TerminalInterface::writeDailyAccountInformation\n");
}

void sendData(struct TerminalInterface* self, int data) {

    if(connect(self->clientSocketFd, (struct sockaddr*)&(self->serverAddr), sizeof(self->serverAddr))) {
        perror("connect error\n");
    }

    send(self->clientSocketFd, &data, sizeof(int), 0);
}