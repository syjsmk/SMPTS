#include "SMPTS.h"

NetworkInterface* newNetworkInterfaceForServer() {

    int i;

  //  printf("NetworkInterface::newNetworkInterfaceForServer\n");

    NetworkInterface *networkInterfaceForServer = (NetworkInterface *)malloc(sizeof(NetworkInterface));
    networkInterfaceForServer->clientSocketFd = 0;
    networkInterfaceForServer->serverSocketFd = 0;
    //networkInterfaceForServer->connectedClientSocketFd = 0;
    memset(networkInterfaceForServer->connectedClientSocketFd, 0, sizeof(networkInterfaceForServer->connectedClientSocketFd));

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


    //networkInterfaceForServer->connectedClientSocketFd = accept(networkInterfaceForServer->serverSocketFd, (struct sockaddr *)&(networkInterfaceForServer->connectedClientAddr), &(networkInterfaceForServer->terminalAddrLength));
    for(i = 0; i < MAXCLIENT; i ++) {
        //printf("1\n");
        networkInterfaceForServer->connectedClientSocketFd[i] = accept(networkInterfaceForServer->serverSocketFd, (struct sockaddr *)&(networkInterfaceForServer->connectedClientAddr), &(networkInterfaceForServer->terminalAddrLength));
        //printf("2\n");

        if(networkInterfaceForServer->connectedClientSocketFd[i] < 0) {
            perror("accept error");
        }
    }



    //이 아래에서 write




    // 함수포인터 세팅
    networkInterfaceForServer->listenTerminal = &listenTerminal;
    networkInterfaceForServer->writeDailyAccountInformation = &writeDailyAccountInformation;
    networkInterfaceForServer->sendData = &sendData;
    networkInterfaceForServer->isServer = &isServer;
    networkInterfaceForServer->deleteNetworkInterface = &deleteNetworkInterface;

    return networkInterfaceForServer;
}


NetworkInterface* newNetworkInterfaceForClient() {

  //  printf("NetworkInterface::newNetworkInterfaceForClient\n");

    NetworkInterface *networkInterfaceForClient = (NetworkInterface *)malloc(sizeof(NetworkInterface));
    networkInterfaceForClient->clientSocketFd = 0;
    networkInterfaceForClient->serverSocketFd = 0;
    memset(networkInterfaceForClient->connectedClientSocketFd, 0, sizeof(networkInterfaceForClient->connectedClientSocketFd));
    //networkInterfaceForClient->connectedClientSocketFd = 0;


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
    networkInterfaceForClient->listenTerminal = &listenTerminal;
    networkInterfaceForClient->writeDailyAccountInformation = &writeDailyAccountInformation;
    networkInterfaceForClient->sendData = &sendData;
    networkInterfaceForClient->isServer = &isServer;
    networkInterfaceForClient->deleteNetworkInterface = &deleteNetworkInterface;

    return networkInterfaceForClient;
}

void listenTerminal(NetworkInterface *self) {

    int i;
    CardInformation cardInformation;
   // printf("NetworkInterface::waitData\n");
    unsigned int len;
//    char buff[BUFFSIZE] = "lllllllllllllll";

    if(self->isServer(self)) {

        for(i = 0; i < MAXCLIENT; i ++) {
            //recv(self->connectedClientSocketFd[i], &(self->terminalType), sizeof(int), 0);
            //recv(self->connectedClientSocketFd[i], &(cardInformation), sizeof(CardInformation), 0);
            recv(self->connectedClientSocketFd[i], &len, sizeof(unsigned int), 0);
            {
                CardInformation cardInformations[len];

                recv(self->connectedClientSocketFd[i], cardInformations, sizeof(CardInformation) * len, 0);
               // printf("socketFD : %d\n", self->connectedClientSocketFd[i]);
                //printf("received data(server) : %d\n", self->terminalType);
                //printf("received data(server) : %s\n", cardInformation.boardingTerminal);
               // printf("received data(from client) : %s\n", cardInformations[i].cardId);
            }
            //close(self->connectedClientSocketFd);
        }

    } else {

        //recv(self->clientSocketFd, &(self->terminalType), sizeof(int), 0);
        //recv(self->clientSocketFd, &(cardInformation), sizeof(CardInformation), 0);
        recv(self->clientSocketFd, &len, sizeof(unsigned int), 0);
        {
            CardInformation cardInformations[len];

            recv(self->clientSocketFd, cardInformations, sizeof(CardInformation) * len, 0);
            //printf("received data(client) : %d\n", self->terminalType);
            //printf("received data(server) : %s\n", cardInformation.count);
           // printf("received data(from server) : %s\n", cardInformations[0].cardId);
        }

        //close(self->clientSocketFd);
    }

}

DailyAccountInformation writeDailyAccountInformation(NetworkInterface* self) {
   // printf("NetworkInterface::writeDailyAccountInformation\n");
}

//void sendData(NetworkInterface* self, int data) {
//void sendData(NetworkInterface* self, void* data) {
void sendData(NetworkInterface* self, CardInformation *cardInformations, unsigned int len) {

    int i;

 //   printf("NetworkInterface::sendData\n");
    //printf("sended data : [%d]\n", data);
//    CardInformation *temp = (CardInformation *)data;
//    CardInformation sendedData = *temp;
//    printf("sendedData Info : %s\n", sendedData.boardingTerminal);
 //   printf("sendedData Info : {id: %s}\n", cardInformations[0].cardId);

    if(self->isServer(self)) {

        for(i = 0; i < MAXCLIENT; i ++) {
            //send(self->connectedClientSocketFd[i], &data, sizeof(int), 0);
            //send(self->connectedClientSocketFd[i], &sendedData, sizeof(CardInformation), 0);
            send(self->connectedClientSocketFd[i], &len, sizeof(unsigned int), 0);
            send(self->connectedClientSocketFd[i], cardInformations, sizeof(CardInformation) * len, 0);
            //close(self->connectedClientSocketFd);
        }

    } else {

        //send(self->clientSocketFd, &data, sizeof(int), 0);
        //send(self->clientSocketFd, &sendedData, sizeof(CardInformation), 0);
        send(self->clientSocketFd, &len, sizeof(unsigned int), 0);
        send(self->clientSocketFd, cardInformations, sizeof(CardInformation) * len, 0);

    }

}

bool isServer(NetworkInterface* self) {

   // printf("NetworkInterface::isServer\n");

    if(self->clientSocketFd == 0) {
        return true;
    } else {
        return false;
    }

}

void deleteNetworkInterface(NetworkInterface* self) {
    free(self);
}