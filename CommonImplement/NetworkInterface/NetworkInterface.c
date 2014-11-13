#include "../PrecompiledHeader.h"

NetworkInterface* newNetworkInterfaceForServer() {

    printf("NetworkInterface::newNetworkInterfaceForServer\n");

    NetworkInterface*networkInterface = (NetworkInterface *)malloc(sizeof(NetworkInterface));

    printf("before socketFd = %d\n", networkInterface->socketFd);

    networkInterface->socketFd = socket(AF_INET, SOCK_STREAM, 0);

    printf("after socketFd = %d\n", networkInterface->socketFd);


    networkInterface->interfaceAddr.sin_family = AF_INET;
    networkInterface->interfaceAddr.sin_addr.s_addr = INADDR_ANY;
    networkInterface->interfaceAddr.sin_port = htons(PORTNUMBER);

    if (bind(networkInterface->socketFd, (struct sockaddr *) &(networkInterface->interfaceAddr), sizeof(networkInterface->interfaceAddr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }


    // 함수포인터 세팅
    networkInterface->listenTerminal = &listenTerminal;
    networkInterface->writeDailyAccountInformation = &writeDailyAccountInformation;
    networkInterface->sendData = &sendData;

    return networkInterface;
}


NetworkInterface* newNetworkInterfaceForClient() {

    printf("NetworkInterface::newNetworkInterfaceForServer\n");

    NetworkInterface* terminalInterface = (NetworkInterface *)malloc(sizeof(NetworkInterface));

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

void listenTerminal(NetworkInterface* self) {
    printf("NetworkInterface::listenTerminal\n");

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

DailyAccountInformation writeDailyAccountInformation(NetworkInterface* self) {
    printf("NetworkInterface::writeDailyAccountInformation\n");
}

void sendData(NetworkInterface* self, int data) {

    if(connect(self->clientSocketFd, (struct sockaddr*)&(self->serverAddr), sizeof(self->serverAddr))) {
        perror("connect error\n");
    }

    send(self->clientSocketFd, &data, sizeof(int), 0);
}