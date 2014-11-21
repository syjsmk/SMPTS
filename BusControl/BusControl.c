#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

BusControl* makeBusControl() {
    BusControl *busControl = (BusControl *)malloc(sizeof(BusControl));

    busControl->busControlNetworkInterface = newNetworkInterfaceForClient();
    busControl->fileIoInterface = newFileIoInterface();
    busControl->innerTimer = newInnerTimer();


    //
    busControl->run = &run;
    return busControl;
}

void run(BusControl* self) {
    printf("BusControl::run\n");

    char* path = "test.txt";
    char buff[BUFFSIZE];
    //char* currentTime;
    char currentTime[128];
    //char* test;
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

    //while(true) {
        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);
    //}
}
