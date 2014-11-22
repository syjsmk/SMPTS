#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

BusControl* newBusControl() {
    BusControl *busControl = (BusControl *)malloc(sizeof(BusControl));

    busControl->busControlNetworkInterface = newNetworkInterfaceForClient();
    busControl->fileIoInterface = newFileIoInterface();
    busControl->innerTimer = newInnerTimer();


    //
    busControl->run = &run;
    return busControl;
}

void run(BusControl* self) {


    char *path = "test.txt";
    char buff[BUFFSIZE];
    char currentTime[128];
    int userInput;

    pthread_t dataSendThread;
    pthread_t userInputThread;
    int threadId;

    threadId = pthread_create(&dataSendThread, NULL, sendDailyDataLoop, (void*)self);
    threadId = pthread_create(&userInputThread, NULL, getUserInputLoop, (void*)self);


    //while(true) {

//        printf("BusControl::run\n");
//        printf("1. In, 2. Out\n");
//        printf("input : ");
//        scanf("%d\n", &userInput);


        //char* test;
//        memset(currentTime, 0, 128);
//
//        CardInformation cardInformation;
//        cardInformation = self->fileIoInterface->readCard(self->fileIoInterface, path);
//        printf("\n---------------------------------------------------------------------\nbuff : %stransportType : %sINOUT : %scount : %sterminal : %s\n---------------------------------------------------------------------\n", cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal);
//        //self->fileIoInterface->readFile(self->fileIoInterface, path);
//        //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));
//
//        //printf("Read from FileIoInterface : %s\n", buff);
//
//        self->fileIoInterface->writeCard(self->fileIoInterface, cardInformation, "writeCard.txt");
//        self->fileIoInterface->writeCard(self->fileIoInterface, cardInformation, "writeCard.txt");
//
//        strncpy(currentTime, self->innerTimer->getTime(self->innerTimer), 20);
//        printf("getTime : %s\n", currentTime);
//        //test = self->innerTimer->getTime(self->innerTimer);
//        //printf("getTime : %s\n", test);
//
//        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
//        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);

    //}
}

void* getUserInputLoop(void* data) {

    //BusControl* self = (BusControl*)data;
    int userInput;

    while(true) {

        printf("BusControl::run\n");
        printf("1. In, 2. Out\n");
        printf("input : ");
        scanf("%d\n", &userInput);
        printf("usetInput : %d\n", userInput);

    }


}

void* sendDailyDataLoop(void* data) {

    BusControl* self = (BusControl*)data;

    char *path = "test.txt";
    char buff[BUFFSIZE];
    char currentTime[128];
    int userInput;

    while(true) {
        printf("sendDailiDataLoop\n");

        memset(currentTime, 0, 128);
        CardInformation cardInformation;
        cardInformation = self->fileIoInterface->readCard(self->fileIoInterface, path);
        printf("\n---------------------------------------------------------------------\nbuff : %stransportType : %sINOUT : %scount : %sterminal : %s\n---------------------------------------------------------------------\n", cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal);
        //self->fileIoInterface->readFile(self->fileIoInterface, path);
        //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));

        //printf("Read from FileIoInterface : %s\n", buff);

        self->fileIoInterface->writeCard(self->fileIoInterface, cardInformation, "writeCard.txt");
        self->fileIoInterface->writeCard(self->fileIoInterface, cardInformation, "writeCard.txt");

        strncpy(currentTime, self->innerTimer->getTime(self->innerTimer), 20);
        printf("getTime : %s\n", currentTime);
        //test = self->innerTimer->getTime(self->innerTimer);
        //printf("getTime : %s\n", test);

        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);

        sleep(1);
    }



}