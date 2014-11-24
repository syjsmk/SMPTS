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


//TODO: countcash 변수 금액변환한걸 다시 inputcardinfo에 문자열로 저장해야함.
//TODO: userID에 따라 탑승시 탑승되도록 배열 사용하여 리스트로 관리.

bool cashAccount(BusControl* self, CardInformation inputcardinfo, int inout, int userID) { // inout 1이면 IN 2면 OUT
    int countcash, curintTime;
    countcash = atoi(inputcardinfo.count);
    char stringTime[14];

    // 현재 시간을 string Time 변수에 복사.
    strncpy(stringTime, self->innerTimer->getTime(self->innerTimer), 14);

    // 마지막 태그 시간과 현재 stringTime의 차이 = curintTime
    curintTime = ((atoi(stringTime))-atoi(inputcardinfo.latestTaggedTime));

    //Last transport Tagged BUS
    if(strcmp(inputcardinfo.transportType,"BUS")) {
        if(strcmp(inputcardinfo.inOut,"OUT")) { //Lastest inOut data is "OUT"
            if(inout==1) { //BUS OUT -> BUS IN
                if (countcash >= 1050) {
                    countcash = countcash - 1050;
                    strncpy(inputcardinfo.inOut, "IN\n", 3);
                    strncpy(inputcardinfo.transfer, "N\n", 2);
                    return true;
                }
                else {
                    printf("Not Enough Money\n");
                    strncpy(inputcardinfo.transfer, "N\n", 2);
                    return false;
                }
            }
            else { //BUS OUT -> BUS OUT
                printf("Wrong command\n");
                strncpy(inputcardinfo.transfer, "N\n", 2);
                return false;
            }
        }
        else if(strcmp(inputcardinfo.inOut,"IN")) { //Lastest inOut data is "IN"
            if(inout==1) { //BUS IN -> BUS IN 특이케이스
                if (curintTime <= 80) { //80초 이하 아직 버스에 탑승중 내리세요
                    printf("Not ready bus door.\n");
                    strncpy(inputcardinfo.transfer, "N\n", 2);
                    return false;
                }
                else { //80초 이상 버스를 이미 내렸어야함 추가요금 부과
                    if (countcash <= 1750) {
                        countcash = countcash - 1750;
                        strncpy(inputcardinfo.inOut, "IN\n", 3);
                        strncpy(inputcardinfo.transfer, "N\n", 2);
                        return true;
                    }
                    else if (countcash <= 700) {
                        countcash = countcash - 700;
                        strncpy(inputcardinfo.transportType, "BUS\n", 4);
                        strncpy(inputcardinfo.inOut, "OUT\n", 4);
                        printf("Please re-tagging cards\n");
                        strncpy(inputcardinfo.transfer, "N\n", 2);
                        return false;
                    }
                    else {
                        printf("Not Enough Moneyy\n");
                    }
                }
            }
            else { //BUS IN -> BUS OUT 정상 하차
                strncpy(inputcardinfo.inOut, "OUT\n", 4);
                printf("get off a Bus\n");
                strncpy(inputcardinfo.transfer, "N\n", 2);
                return true;
            }
        }
        else { //Lastest inOut data error
            printf("\nInOut Type Error\n");
            return false;
        }
    }


    //Last transport Tagged METRO
    else if(strcmp(inputcardinfo.transportType,"METRO")) {
        if(strcmp(inputcardinfo.inOut,"OUT")) {
            if(inout==1) { // METRO OUT -> BUS IN
                if (curintTime <= 15) { //지하철에서 내렸고, 환승시간 내에 환승한다.
                    if (countcash >= 700) {
                        countcash = countcash - 0;
                        strncpy(inputcardinfo.inOut, "IN\n", 3);
                        strncpy(inputcardinfo.transfer, "Y\n", 2);
                        return true;
                    }
                    else { //잔액부족 승차거부
                        printf("Not Enough Money\n");
                        strncpy(inputcardinfo.transfer, "N\n", 2);
                        return false;
                    }
                }
                else { //환승시간 초과이므로 기본요금 부여
                    if (countcash >= 1050) { //기본요금 체크
                        //FIN: 기본요금 부가 후 버스 IN으로 수정
                        countcash = countcash - 1050;
                        strncpy(inputcardinfo.inOut, "IN\n", 3);
                        strncpy(inputcardinfo.transfer, "N\n", 2);
                        return true;
                    }
                    else {//어차피 시간 지났으므로 환승이 아니며 승차거부도 당함
                        printf("Not Enough Money\n");
                        strncpy(inputcardinfo.transfer, "N\n", 2);
                        return false;
                    }
                }
            }
            else { //METRO OUT -> BUS OUT 존재하지 않는 케이스
                printf("OUT -> OUT ERROR\n");
                strncpy(inputcardinfo.transfer, "N\n", 2);
                return false;
            }
        }
        else { //Lastest inOut data is "IN" "METRO"
            if(inout==1) { //METRO IN -> BUS IN
                if (curintTime <= 15) { //환승이지만 지하철 미정산
                    if (countcash >= 600) { // 환승이지만 지하철것이 미정산 되었으므로 600원 부과.
                        countcash = countcash - 600;
                        strncpy(inputcardinfo.transfer, "Y\n", 2);
                        return true;
                    }
                    else { //돈이없으니. 환승도 못함
                        printf("Not enough cash\n");
                        return false;
                    }
                }
                else { //환승시간 초과 + 지하철 미정산
                    if (countcash >= 1650) { // 지하철것이 미정산 되었으므로 1050+600원
                        countcash = countcash - 1650;
                        strncpy(inputcardinfo.transfer, "N\n", 2);
                        return true;
                    }
                    else { //돈이없으니 탑승불가.
                        if(countcash >= 600){ //600원만 빠져나가고 탑승불가.
                            countcash = countcash - 600;
                            strncpy(inputcardinfo.inOut, "OUT\n", 4);
                            strncpy(inputcardinfo.transfer, "N\n", 2);
                            return false;
                        }
                        else { //돈이없으니 탑승불가.
                            printf("Not enough cash\n");
                            return false;
                        }
                    }
                }
            }
            else { //METRO IN -> BUS OUT
                printf("METRO IN -> BUS OUT ERROR\n");
                return false;
            }
        }
    }
    else {
        printf("\nTransport Type Error\n");
        return false;
    }

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



    //self->cashAccount(self, cardInformation);


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

    int i;
    BusControl* self = (BusControl*)data;

    char *path = "../SampleBusCard.txt";
    char buff[BUFFSIZE] = "a";
    char currentTime[128];
    int userInput;
    int dailyInfoSize;

    //printf("buff : %s\n", buff);

    while(true) {

        //TODO: 하루치 데이터를 보내기 전에 파일을 읽어올 부분.
        printf("sendDailiDataLoop\n");
        memset(currentTime, 0, 128);
        strncpy(currentTime, self->innerTimer->getTime(self->innerTimer), 22);
        CardInformation cardInformation;

        dailyInfoSize = self->fileIoInterface->getDailyInfoSize(self->fileIoInterface, path);
        printf("dailyInfoSize : %d\n", dailyInfoSize);

        for(i = 0; i < dailyInfoSize; i ++) {

            cardInformation = self->fileIoInterface->readCard(self->fileIoInterface, path);
//            if(strcmp(buff[0], "a") == 0) {
//                strncpy(buff, cardInformation.cardId, CARDIDSIZE);
//            } else {
//                strcat(buff, cardInformation.cardId);
//            }
            if(strcmp(buff,"a") == 0) {
                //printf("111111111111111111\n");
                strncpy(buff, cardInformation.cardId, CARDIDSIZE);
            } else {
                //printf("22222222222222222222\n");
                strcat(buff, cardInformation.cardId);
            }

            //strncpy(buff, cardInformation.cardId, CARDIDSIZE);
            strcat(buff, cardInformation.latestTaggedTime);
            strcat(buff, cardInformation.transportType);
            strcat(buff, cardInformation.inOut);
            strcat(buff, cardInformation.count);
            strcat(buff, cardInformation.boardingTerminal);
            strcat(buff, cardInformation.transfer);
        }

        printf("copied buffer : %s\n", buff);

        printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n", cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);
        //self->fileIoInterface->readFile(self->fileIoInterface, path);
        //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));

        //printf("Read from FileIoInterface : %s\n", buff);


        printf("getTime : %s\n", currentTime);
        //test = self->innerTimer->getTime(self->innerTimer);
        //printf("getTime : %s\n", test);

        //self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
        //self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, (void*) &cardInformation);
        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, buff);
        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);

        strncpy(buff, "a", BUFFSIZE);

        sleep(1);
    }



}
