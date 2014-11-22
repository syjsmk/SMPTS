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

//버스 타는것 계산해서 계산된 금액 저장하는 함수.
bool cashAccount(CardInformation inputcardinfo) {
    int countcash;
    countcash = atoi(inputcardinfo.count);

    if(strcmp(inputcardinfo.transportType,"BUS")) {
        if(strcmp(inputcardinfo.inOut,"OUT")) {
            //환승시간 체크 후 판별

        }
        else { //Lastest inOUT data is "IN"
            //환승시간 체크 후 판별

        }
    }
    else if(strcmp(inputcardinfo.transportType,"METRO")) {
        if(strcmp(inputcardinfo.inOut,"OUT")) {
            //환승시간 체크 후 판별

        }
        else { //Lastest inOUT data is "IN"
            //환승시간 체크 후 판별

        }
    }
    else {
        printf("Transport Type Error");
        return false;
    }
}

void boardingResults(bool results) {
    if(results == true) { printf("boarding success\n"); }
    else{ printf("boarding fail\n"); }
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

    cardInformation = self->fileIoInterface->readCard(self->fileIoInterface, path); //Read card results
    printf("\n------------------------------Bus Print----------------------------\nbuff : %stransportType : %sINOUT : %scount : %sterminal : %s\n---------------------------------------------------------------------\n", cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal);
    //self->fileIoInterface->readFile(self->fileIoInterface, path);
    //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));

    //printf("Read from FileIoInterface : %s\n", buff);



    //*************This area is writeCard information area.*****************
    //boardingResults(cashAccount(cardInformation));
    self->fileIoInterface->writeCard(self->fileIoInterface, cardInformation, "writeCard.txt"); //Write card results.






    strncpy(currentTime, self->innerTimer->getTime(self->innerTimer), 20);
    printf("getTime : %s\n", currentTime);
    //test = self->innerTimer->getTime(self->innerTimer);
    //printf("getTime : %s\n", test);

    //while(true) {
        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);
    //}
}
