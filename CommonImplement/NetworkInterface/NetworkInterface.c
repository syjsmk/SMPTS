#include "../PrecompiledHeader.h"

NetworkInterface* newNetworkInterfaceForServer() {

    printf("NetworkInterface::newNetworkInterfaceForServer\n");

    NetworkInterface *networkInterfaceForServer = (NetworkInterface *)malloc(sizeof(NetworkInterface));
    networkInterfaceForServer->clientSocketFd = 0;
    networkInterfaceForServer->serverSocketFd = 0;
    networkInterfaceForServer->connectedClientSocketFd = 0;

    //printf("before serverSocketFd = %d\n", networkInterfaceForServer->serverSocketFd);

    // 왜 AccountSystem의 NetworkInputInteface와 BusControl의 NetworkInputInterface의 serverSocketFd에 똑같은 값이 할당되는가?
    networkInterfaceForServer->serverSocketFd = socket(PF_INET, SOCK_STREAM, 0);

    //printf("after serverSocketFd = %d\n", networkInterfaceForServer->serverSocketFd);

    memset(&(networkInterfaceForServer->serverAddr), 0, sizeof(networkInterfaceForServer->serverAddr));
    memset(&(networkInterfaceForServer->connectedClientAddr), 0, sizeof(networkInterfaceForServer->connectedClientAddr));
    networkInterfaceForServer->serverAddr.sin_family = AF_INET;
    networkInterfaceForServer->serverAddr.sin_addr.s_addr = INADDR_ANY;
    networkInterfaceForServer->serverAddr.sin_port = htons(PORTNUMBER);

    if (bind(networkInterfaceForServer->serverSocketFd, (struct sockaddr *) &(networkInterfaceForServer->serverAddr), sizeof(networkInterfaceForServer->serverAddr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    listen(networkInterfaceForServer->serverSocketFd, 5);
    networkInterfaceForServer->terminalAddrLength = sizeof(networkInterfaceForServer->connectedClientAddr);

    networkInterfaceForServer->connectedClientSocketFd = accept(networkInterfaceForServer->serverSocketFd, (struct sockaddr *)&(networkInterfaceForServer->connectedClientAddr), &(networkInterfaceForServer->terminalAddrLength));

    //이 아래에서 write

    if(networkInterfaceForServer->connectedClientSocketFd < 0) {
        perror("accept error");
    }


    // 함수포인터 세팅
    networkInterfaceForServer->listenTerminal = &waitData;
    networkInterfaceForServer->writeDailyAccountInformation = &writeDailyAccountInformation;
    networkInterfaceForServer->sendData = &sendData;
    networkInterfaceForServer->isServer = &isServer;
    networkInterfaceForServer->deleteNetworkInterface = &deleteNetworkInterface;

    return networkInterfaceForServer;
}


NetworkInterface* newNetworkInterfaceForClient() {

    printf("NetworkInterface::newNetworkInterfaceForClient\n");

    NetworkInterface *networkInterfaceForClient = (NetworkInterface *)malloc(sizeof(NetworkInterface));
    networkInterfaceForClient->clientSocketFd = 0;
    networkInterfaceForClient->serverSocketFd = 0;
    networkInterfaceForClient->connectedClientSocketFd = 0;

    //printf("before clientSocketFd = %d\n", networkInterfaceForClient->clientSocketFd);

    networkInterfaceForClient->clientSocketFd = socket(PF_INET, SOCK_STREAM, 0);


    //printf("after clientSocketFd = %d\n", networkInterfaceForClient->clientSocketFd);

    memset(&(networkInterfaceForClient->clientToServerAddr), 0, sizeof(networkInterfaceForClient->clientToServerAddr));
    networkInterfaceForClient->clientToServerAddr.sin_family = AF_INET;
    networkInterfaceForClient->clientToServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    networkInterfaceForClient->clientToServerAddr.sin_port = htons(PORTNUMBER);

    if(connect(networkInterfaceForClient->clientSocketFd, (struct sockaddr*)&(networkInterfaceForClient->clientToServerAddr), sizeof(networkInterfaceForClient->clientToServerAddr))) {
        perror("connect error\n");
    }

    // 함수포인터 세팅
    networkInterfaceForClient->listenTerminal = &waitData;
    networkInterfaceForClient->writeDailyAccountInformation = &writeDailyAccountInformation;
    networkInterfaceForClient->sendData = &sendData;
    networkInterfaceForClient->isServer = &isServer;
    networkInterfaceForClient->deleteNetworkInterface = &deleteNetworkInterface;

    return networkInterfaceForClient;
}

void waitData(NetworkInterface *self) {
    printf("NetworkInterface::waitData\n");

    if(self->isServer(self)) {

        recv(self->connectedClientSocketFd, &(self->terminalType), sizeof(int), 0);
        printf("received data(server) : %d\n", self->terminalType);

        //close(self->connectedClientSocketFd);
    } else {
        recv(self->clientSocketFd, &(self->terminalType), sizeof(int), 0);
        printf("received data(client) : %d\n", self->terminalType);

        //close(self->clientSocketFd);
    }

}

DailyAccountInformation writeDailyAccountInformation(NetworkInterface* self) {
    printf("NetworkInterface::writeDailyAccountInformation\n");
}

void sendData(NetworkInterface* self, int data) {

    printf("NetworkInterface::sendData\n");
    printf("sended data : [%d]\n", data);

    if(self->isServer(self)) {
        send(self->connectedClientSocketFd, &data, sizeof(int), 0);
        //close(self->connectedClientSocketFd);

    } else {

        send(self->clientSocketFd, &data, sizeof(int), 0);

    }

}

bool isServer(NetworkInterface* self) {

    printf("NetworkInterface::isServer\n");

    if(self->clientSocketFd == 0) {
        return true;
    } else {
        return false;
    }

}

void deleteNetworkInterface(NetworkInterface* self) {
    free(self);
}