#include "SMPTS.h"

//FIN: countcash 변수 금액변환한걸 다시 inputcardinfo에 문자열로 저장해야함.

void printUserList(BusControl *self) {
    int i;
    printf("Current riding bus user total : %d\n", self->userCount);

    for( i = 0 ; i < MAXIMUMUSER; i ++) { // print user status.
        if(self->userList[i] != 0) {
            printf("%d : %d user riding a BUS\n", i, self->userList[i]);
        }
    }
}

void rideBus(BusControl *self, int userID){
    if(self->userCount >= 0){ //승차 로직
        self->userList[self->userCount] = userID;
        self->userCount++;
        printf("%d : user get in the bus\n",userID);
        printUserList(self);
    }
    else {
        printf("Add user fail\n");
    }
}

void rideOffBus(BusControl *self, int userID){
    int i;
    int j;
    for(i = 0 ; i < self->userCount; i++){ //하차 로직

        if(self->userList[i] == userID){
            self->userList[i] = 0;
            self->userCount--;
            printf("%d : user get off the bus\n", userID);
            for(i = 0 ; i < MAXIMUMUSER ; i ++) {
                if(self->userList[i] == 0){ // 첫칸이 0인경우 전체 한칸씩 당김.
                    for(j = i; j < MAXIMUMUSER; j++){
                        if(j!=MAXIMUMUSER) {
                            self->userList[j] = self->userList[j+1];
                        }
                        else {
                            self->userList[j] = 0;
                        }
                    }
                }
            }
            printUserList(self);
        } else {
            printf("%d : User dismount fail\n", userID);
        }
    }
}


static bool cashAccount(BusControl* self, CardInformation *inputcardinfo, int inout, int userID) { // inout 1이면 IN 2면 OUT

    int countcash, curintTime;
    countcash = atoi(inputcardinfo->count);
    char stringTime[14];
    int i;
    self->userCount = 0;
    for( i = 0 ; i < MAXIMUMUSER; i ++) { // check userCount for loop.
        if(self->userList[i] == 0) {}
        else {
            self->userCount++;
        }
    }

    printUserList(self);    // 현재 인원 총 수 및 상태 출력

    // 현재 시간을 string Time 변수에 복사.
    self->innerTimer->getTime(self->innerTimer, stringTime);

    // 마지막 태그 시간과 현재 stringTime의 차이 = curintTime
    curintTime = ((atoi(stringTime))-atoi(inputcardinfo->latestTaggedTime));

    //Last transport Tagged BUS
    if(strncmp(inputcardinfo->transportType,"10",2)==0) { // Lastest transportation BUS
        printf("BUS  //");
        if(strncmp(inputcardinfo->inOut,"101",3)==0) { //Lastest inOut data is "OUT"
            printf("OUT  //");
            if(inout==1) { //BUS OUT -> BUS IN
                printf("IN  //");
                if (countcash >= 1050) {
                    countcash = countcash - 1050;
                    snprintf (inputcardinfo->count, sizeof(inputcardinfo->count), "%d\n",countcash);
                    strncpy(inputcardinfo->inOut, "100", 3);
                    strncpy(inputcardinfo->transfer, "N", 1);

                    rideBus(self, userID);

                    return true;
                }
                else {
                    printf("Not Enough Money\n");
                    strncpy(inputcardinfo->transfer, "N", 1);
                    return false;
                }
            }
            else { //BUS OUT -> BUS OUT
                printf("OUT  //");
                printf("Wrong command\n");
                strncpy(inputcardinfo->transfer, "N", 1);
                return false;
            }
        }
        else if(strncmp(inputcardinfo->inOut,"100",3)==0) { //Lastest inOut data is "IN"
            printf("IN  //");
            if(inout==1) { //BUS IN -> BUS IN 특이케이스
                printf("IN  //");
                if (curintTime <= 80) { //80초 이하 아직 버스에 탑승중 내리세요
                    printf("Not ready bus door.\n");
                    strncpy(inputcardinfo->transfer, "N", 1);
                    //내리게 함.

                    rideOffBus(self, userID);

                    return false;
                }
                else { //80초 이상 버스를 이미 내렸어야함 추가요금 부과
                    if (countcash >= 1750) {
                        countcash = countcash - 1750;
                        snprintf (inputcardinfo->count, sizeof(inputcardinfo->count), "%d\n",countcash);
                        strncpy(inputcardinfo->inOut, "100", 3);
                        strncpy(inputcardinfo->transfer, "N", 1);

                        rideBus(self, userID);

                        return true;
                    }
                    else if (countcash >= 700) {  //700원만 지불하고 못탐.
                        countcash = countcash - 700;
                        snprintf (inputcardinfo->count, sizeof(inputcardinfo->count), "%d\n",countcash);
                        strncpy(inputcardinfo->transportType, "10", 2);
                        strncpy(inputcardinfo->inOut, "101", 3);
                        printf("Please re-tagging cards\n");
                        strncpy(inputcardinfo->transfer, "N", 1);

                        rideOffBus(self, userID);

                        return false;
                    }
                    else { //돈이 아예 없으므로 하차.
                        printf("Not Enough Moneyy\n");

                        rideOffBus(self, userID);

                    }
                }
            }
            else { //BUS IN -> BUS OUT 정상 하차
                printf("OUT  //");
                strncpy(inputcardinfo->inOut, "101", 3);
                printf("get off a Bus\n");
                strncpy(inputcardinfo->transfer, "N", 1);

                rideOffBus(self, userID);

                return true;
            }
        }
        else { //Lastest inOut data error
            printf("\nInOut Type Error\n");
            return false;
        }
    }


    //Last transport Tagged METRO
    else if(strncmp(inputcardinfo->transportType,"11",2)==0) { //Lastest transportation METRO
        printf("LAST METRO //");
        if(strncmp(inputcardinfo->inOut,"101",3)==0) {
            printf("OUT //");
            if(inout==1) { // METRO OUT -> BUS IN
                printf("->BUS IN //");
                if (curintTime <= 15) { //지하철에서 내렸고, 환승시간 내에 환승한다.
                    printf("Transfer OK//");
                    if (countcash >= 700) {
                        countcash = countcash - 0;
                        snprintf (inputcardinfo->count, sizeof(inputcardinfo->count), "%d\n",countcash);
                        strncpy(inputcardinfo->inOut, "100", 3);
                        strncpy(inputcardinfo->transfer, "Y", 1);

                        rideBus(self, userID);

                        return true;
                    }
                    else { //잔액부족 승차거부
                        printf("Not Enough Money\n");
                        strncpy(inputcardinfo->transfer, "N", 1);

                        rideOffBus(self, userID);

                        return false;
                    }
                }
                else { //환승시간 초과이므로 기본요금 부여
                    printf("Transfer NO//");
                    if (countcash >= 1050) { //기본요금 체크
                        //FIN: 기본요금 부가 후 버스 IN으로 수정
                        countcash = countcash - 1050;
                        snprintf (inputcardinfo->count, sizeof(inputcardinfo->count), "%d\n",countcash);
                        strncpy(inputcardinfo->inOut, "100", 3);
                        strncpy(inputcardinfo->transfer, "N", 1);

                        rideBus(self, userID);

                        return true;
                    }
                    else {//어차피 시간 지났으므로 환승이 아니며 승차거부도 당함
                        printf("Not Enough Money\n");
                        strncpy(inputcardinfo->transfer, "N", 1);

                        rideOffBus(self, userID);

                        return false;
                    }
                }
            }
            else { //METRO OUT -> BUS OUT 존재하지 않는 케이스
                printf("OUT -> OUT ERROR\n");
                strncpy(inputcardinfo->transfer, "N", 1);

                rideOffBus(self, userID);

                return false;
            }
        }
        else { //Lastest inOut data is "IN" "METRO"
            printf("IN //");
            if(inout==1) { //METRO IN -> BUS IN
                printf("->BUS IN //");
                if (curintTime <= 15) { //환승이지만 지하철 미정산
                    printf("Transfer OK//");
                    if (countcash >= 600) { // 환승이지만 지하철것이 미정산 되었으므로 600원 부과.
                        countcash = countcash - 600;
                        snprintf (inputcardinfo->count, sizeof(inputcardinfo->count), "%d\n",countcash);
                        strncpy(inputcardinfo->transfer, "Y", 1);

                        rideBus(self, userID);

                        return true;
                    }
                    else { //돈이없으니. 환승도 못함
                        printf("Not enough cash\n");

                        rideOffBus(self, userID);

                        return false;
                    }
                }
                else { //환승시간 초과 + 지하철 미정산
                    printf("Transfer NO//");
                    if (countcash >= 1650) { // 지하철것이 미정산 되었으므로 1050+600원
                        countcash = countcash - 1650;
                        snprintf (inputcardinfo->count, sizeof(inputcardinfo->count), "%d\n",countcash);
                        strncpy(inputcardinfo->transfer, "N", 1);

                        rideBus(self, userID);

                        return true;
                    }
                    else { //돈이없으니 탑승불가.
                        if(countcash >= 600){ //600원만 빠져나가고 탑승불가.
                            countcash = countcash - 600;
                            snprintf (inputcardinfo->count, sizeof(inputcardinfo->count), "%d\n",countcash);
                            strncpy(inputcardinfo->inOut, "101", 3);
                            strncpy(inputcardinfo->transfer, "N", 1);

                            rideOffBus(self, userID);

                            return false;
                        }
                        else { //돈이없으니 탑승불가.
                            printf("Not enough cash\n");

                            rideOffBus(self, userID);

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

static void boardingResults(bool results) {
    if(results == true) { printf("boarding success\n"); }
    else{ printf("boarding fail\n"); }
}

static void run(BusControl* self) {
    int i = 0 ;
    self->userCount = 0;    //init


    for(i = 0 ; i < MAXIMUMUSER; i ++){


        self->userList[i] = 0;
    }   //user List 초기화.


    char buff[BUFFSIZE];
    char currentTime[128];

    memset(currentTime, 0, 128);

    CardInformation cardInformation;

    //self->fileIoInterface->readCard(self->fileIoInterface, path, &cardInformation); //Read card results

    //self->fileIoInterface->readFile(self->fileIoInterface, path);
    //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));
    int userInput;

    pthread_t dataSendThread;
    pthread_t userInputThread;
    int threadId1, threadId2;


    //*************This area is writeCard information area.*****************
    //boardingResults(cashAccount(cardInformation));
    //self->fileIoInterface->writeCard(self->fileIoInterface, &cardInformation, "writeCard.txt", ); //Write card results.


    threadId1 = pthread_create(&dataSendThread, NULL, sendDailyDataLoop, (void*)self);
    threadId2 = pthread_create(&userInputThread, NULL, getUserInputLoop, (void*)self);

    pthread_join(dataSendThread, NULL);
    pthread_join(userInputThread, NULL);


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
    int outUser;
    char currentTime[128];
    BusControl *self = (BusControl*)data;
    CardInformation cardInformation;
    char *cardPath = "SampleBusCard.txt";



    memset(&userInput,0, sizeof(int));
    while(true) {

        printf("BusControl::run\n");
        printf("1. In, 2. Out\n");
        printf("input : ");
        scanf("%d", &userInput);

        if(self->userCount == 0 && userInput == 2) {
            printf("No user here\n");
        } else {
            memset(&cardInformation, 0, sizeof(CardInformation));
            self->fileIoInterface->readCard(self->fileIoInterface, cardPath, &cardInformation);
            boardingResults(cashAccount(self, &cardInformation, userInput, atoi(cardInformation.cardId)));

            printf("User ID: %s LastestTaggedTime: %s TransportType: %s InOut: %s Count: %s BoardingTerminal: %s Transfer: %s",cardInformation.cardId,cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut,
                    cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);

            self->fileIoInterface->writeCard(self->fileIoInterface, cardPath, &cardInformation, OVERRIDE);
            self->fileIoInterface->writeCard(self->fileIoInterface, self->dailyInfoPath, &cardInformation, APPEND);

        }




        self->innerTimer->getTime(self->innerTimer, currentTime);
        printf("\ncurrentTime : %s\n", currentTime);
        memset(&userInput,0, sizeof(int));

        //TODO : 계산을 한 후 카드에 해당내용 기록.

    }
}

void* sendDailyDataLoop(void* data) {

    int i;
    BusControl *self = (BusControl*)data;

    char *cardPath = "SampleBusCard.txt";
    char *dailyInfoPath = "BusDailyInfo.txt";
    char buff[BUFFSIZE] = "a";
    char currentTime[128];
    int userInput;
    unsigned int dailyInfoSize = 0;

//    dailyInfoSize = (unsigned int)self->fileIoInterface->getDailyInfoSize(self->fileIoInterface, cardPath);
//
//    CardInformation cardInformations[dailyInfoSize];
//    memset(cardInformations, 0, sizeof(CardInformation) * dailyInfoSize);
//
//    for(i = 0; i < dailyInfoPath; i ++) {
//
//
//        CardInformation cis[dailyInfoSize];
//        self->fileIoInterface->readDailyInfo(self->fileIoInterface, dailyInfoPath, cis);
//        memcpy(&cardInformations[i], &cis[i], sizeof(CardInformation));
//    }

    dailyInfoSize = (unsigned int)self->fileIoInterface->getDailyInfoSize(self->fileIoInterface, dailyInfoPath);

    CardInformation cardInformations[dailyInfoSize];
    memset(cardInformations, 0, sizeof(CardInformation) * dailyInfoSize);

    {
        // TODO: len is only two values

        unsigned int dailyInfoSize = 0;
        dailyInfoSize = self->fileIoInterface->getDailyInfoSize(self->fileIoInterface, dailyInfoPath);
        CardInformation cardInformations[dailyInfoSize];

        memset(cardInformations, 0, sizeof(CardInformation) * dailyInfoSize);

        for (i = 0; i < dailyInfoSize; i++) {
            CardInformation cardInformation;
            memset(&cardInformation, 0, sizeof(cardInformation));

            CardInformation cis[dailyInfoSize];
            memset(&cis, 0, sizeof(CardInformation) * dailyInfoSize);

            self->fileIoInterface->readDailyInfo(self->fileIoInterface, self->dailyInfoPath, cis);

            //memcpy(&cardInformations[i], &cardInformation, sizeof(CardInformation));
            memcpy(&cardInformations[i], &cis[i], sizeof(CardInformation));

//            printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
//                    cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);
        }

    while(true) {

        memset(currentTime, 0, 128);
        self->innerTimer->getTime(self->innerTimer, currentTime);


        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, cardInformations, dailyInfoSize);
        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);

        sleep(3);
        }
    }



}

BusControl* newBusControl() {
    BusControl *busControl = (BusControl *)malloc(sizeof(BusControl));

    busControl->busControlNetworkInterface = newNetworkInterfaceForClient();
    busControl->fileIoInterface = newFileIoInterface();
    busControl->innerTimer = newInnerTimer();

    busControl->dailyInfoPath =  "BusDailyInfo.txt";

    //
    busControl->run = &run;
    busControl->cashAccount = &cashAccount;
    busControl->printUsers = &printUsers;
    return busControl;
}

void printUsers(BusControl* self) {

    int i;
    printf("BusControl::printUsers\n");

    for(i = 0; i < MAXIMUMUSER; i ++) {
        printf("user : %d\n", self->userList[i]);
    }
}