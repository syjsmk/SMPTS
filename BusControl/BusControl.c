#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

BusControl* newBusControl() {
    BusControl *busControl = (BusControl *)malloc(sizeof(BusControl));

    busControl->busControlNetworkInterface = newNetworkInterfaceForClient();
    busControl->fileIoInterface = newFileIoInterface();
    busControl->innerTimer = newInnerTimer();


    //
    busControl->run = &run;
    busControl->cashAccount = &cashAccount;
    return busControl;
}

//버스 타는것 계산해서 계산된 금액 저장하는 함수.
bool cashAccount(BusControl* self, CardInformation inputcardinfo) {
    int countcash, curintTime;
    countcash = atoi(inputcardinfo.count);
    char stringTime[14];

    printf("\n\n\n\n\n%s\n\n\n\n\n\n\n\n\n\n",inputcardinfo.latestTaggedTime);

    strncpy(stringTime, self->innerTimer->getTime(self->innerTimer), 14);

    printf("\n\n\n\n*********\n%s\n*********\n\n\n\n\n\n\n\n\n",stringTime);

    curintTime = ((atoi(stringTime))-atoi(inputcardinfo.latestTaggedTime));
    printf("\n*********\n%d\n*********\n",curintTime);

/*
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
    */
}

void boardingResults(bool results) {
    if(results == true) { printf("boarding success\n"); }
    else{ printf("boarding fail\n"); }
}

void run(BusControl* self) {


    char *path = "../SampleBusCard.txt";
    char buff[BUFFSIZE];
    char currentTime[128];
    //char* test;
    memset(currentTime, 0, 128);

    CardInformation cardInformation;

    cardInformation = self->fileIoInterface->readCard(self->fileIoInterface, path); //Read card results
    printf("\n------------------------------Bus Print----------------------------\nbuff : %stransportType : %sINOUT : %scount : %sterminal : %s\n---------------------------------------------------------------------\n", cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal);



    self->cashAccount(self, cardInformation);


    //self->fileIoInterface->readFile(self->fileIoInterface, path);
    //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));
    int userInput;

    pthread_t dataSendThread;
    pthread_t userInputThread;
    int threadId;


    //*************This area is writeCard information area.*****************
    //boardingResults(cashAccount(cardInformation));
    self->fileIoInterface->writeCard(self->fileIoInterface, cardInformation, "writeCard.txt"); //Write card results.


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

        //TODO : 계산을 한 후 카드에 해당내용 기록.

    }


}

void* sendDailyDataLoop(void* data) {

    BusControl* self = (BusControl*)data;

    char *path = "../SampleBusCard.txt";
    char buff[BUFFSIZE];
    char currentTime[128];
    int userInput;

    while(true) {

        //TODO: 하루치 데이터를 보내기 전에 파일을 읽어올 부분.
        printf("sendDailiDataLoop\n");
        memset(currentTime, 0, 128);
        strncpy(currentTime, self->innerTimer->getTime(self->innerTimer), 22);
        CardInformation cardInformation;
        cardInformation = self->fileIoInterface->readCard(self->fileIoInterface, path);

        printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n", cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);
        //self->fileIoInterface->readFile(self->fileIoInterface, path);
        //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));

        //printf("Read from FileIoInterface : %s\n", buff);


        printf("getTime : %s\n", currentTime);
        //test = self->innerTimer->getTime(self->innerTimer);
        //printf("getTime : %s\n", test);

        //self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, (void*) &cardInformation);
        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);

        sleep(1);
    }



}
