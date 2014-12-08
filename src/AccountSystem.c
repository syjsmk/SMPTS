
#include "SMPTS.h"

static void sendAccountAlarmToTerminal(struct AccountSystem *self) {
    printf("AccountSystem::sendAccountAlarmToTerminal\n");
}

static void sendDataToEnterpriseServer(struct AccountSystem *self) {
    printf("AccountSystem::sendDataToEnterpriseServer\n");
}

static void display(struct AccountSystem *self) {
    printf("AccountSystem::display\n");
}

static void divideEachCardInformation(DailyAccountInformation *dailyInformation){
    int i, j, k, l;
    int hwanSeoung, zungSang;

    CardInformation userCardInformationSort[MAXIMUMUSER][256];

    char* constCardId;

    for(i = 0; i < MAXCLIENT; i++) {
        printf("dailyAccountSize : %d\n", dailyInformation[i].size);
        for(j = 0; j < dailyInformation[i].size; j ++) {
            printf("cardId %d : %s\n", j, dailyInformation[i].cardInformations[j].cardId);
            printf("inOut %d : %s\n", j, dailyInformation[i].cardInformations[j].inOut);
        }

    }

    for(k=0 ; k < MAXIMUMUSER ; k++){
        l = 0;
        for(i = 0; i < MAXCLIENT; i++) {
            for(j = 0; j < dailyInformation[i].size; j ++) {
                if(k == atoi(dailyInformation[i].cardInformations[j].cardId)){
                    userCardInformationSort[k][l] = dailyInformation[i].cardInformations[j];
                    l++;
                }
                else {
                    printf("Card Data Error\n");
                }
            }
        }
    }

    for(i = 0; i < MAXIMUMUSER; i++) {
        for (j = 0; j < 255; j++) {
            if (strncmp(userCardInformationSort[i][j].transfer, "N", 1) == 0) { // 환승 N인 경우
                if (strncmp(userCardInformationSort[i][j].count, userCardInformationSort[i][j + 1].count, sizeof(userCardInformationSort[i][j].count) != 0)) { // 바로 뒤의 돈이랑 금액이 다르면
                    if (strncmp(userCardInformationSort[i][j].transportType, "10", 2) == 0) {  // 버스면 버스에 차익 추가.
                        accountBusAndMetro[0] = accountBusAndMetro[0] + atoi(userCardInformationSort[i][j].count) - atoi(userCardInformationSort[i][j + 1].count);
                    }
                    if (strncmp(userCardInformationSort[i][j].transportType, "11", 2) == 0) {  //지하철이면 지하철 차익 추가.
                        accountBusAndMetro[1] = accountBusAndMetro[1] + atoi(userCardInformationSort[i][j].count) - atoi(userCardInformationSort[i][j + 1].count);
                    }
                }
                else { // 바로뒤의 돈과 금액이 같은경우
                    printf("Enough data Error\n");//그냥 내린것임
                }
            }
            else {  // 환승 Y인 경우.
                if (strncmp(userCardInformationSort[i][j].count, userCardInformationSort[i][j + 1].count, sizeof(userCardInformationSort[i][j].count) != 0)) { // 바로 뒤의 돈이랑 금액이 다르면
                    if (strncmp(userCardInformationSort[i][j].transportType, "10", 2) == 0) {  //버스
                        hwanSeoung = atoi(userCardInformationSort[i][j].count) - atoi(userCardInformationSort[i][j+1].count);
                        zungSang = atoi(userCardInformationSort[i][j-2].count) - atoi(userCardInformationSort[i][j-1].count);
                        accountBusAndMetro[0] = accountBusAndMetro[0] + (hwanSeoung+zungSang) * (hwanSeoung+zungSang) / 1050 + (hwanSeoung+zungSang);
                        accountBusAndMetro[1] = accountBusAndMetro[1] + (hwanSeoung+zungSang) * zungSang / 1050 + (hwanSeoung+zungSang);
                    }
                    if (strncmp(userCardInformationSort[i][j].transportType, "11", 2) == 0) {  //지하철
                        hwanSeoung = atoi(userCardInformationSort[i][j].count) - atoi(userCardInformationSort[i][j+1].count);
                        zungSang = atoi(userCardInformationSort[i][j-2].count) - atoi(userCardInformationSort[i][j-1].count);
                        accountBusAndMetro[0] = accountBusAndMetro[0] + (hwanSeoung+zungSang) * zungSang / 1050 + (hwanSeoung+zungSang);
                        accountBusAndMetro[1] = accountBusAndMetro[1] + (hwanSeoung+zungSang) * (hwanSeoung+zungSang) / 1050 + (hwanSeoung+zungSang);
                    }
                }
                else {
                    printf("Enough data Error\n");
                }
            }
        }
    }
    printf("Bus data : %d\n", accountBusAndMetro[0]);
    printf("Metro data : %d\n", accountBusAndMetro[1]);

}

static void run(AccountSystem* self) {

    int i = 0;
    int j = 0;

    printf("%s\n", __FUNCTION__);

    //여기서 반복적으로 돌게? 두 번 돌고 나서 DailyAccountInformation이 생성되었을것이라고 가정.

    assert(self != NULL);
    assert(self->networkInterface != NULL);

    self->running = true;

    CardInformation cardInformation;
    memset(&cardInformation, 0, sizeof(CardInformation));
    strcpy(cardInformation.cardId, "asd_123");
    strcpy(cardInformation.latestTaggedTime, "20070617143054");
    strcpy(cardInformation.transportType, "10");
    strcpy(cardInformation.inOut, "100");
    strcpy(cardInformation.count, "3000");
    strcpy(cardInformation.boardingTerminal, "300_4");
    strcpy(cardInformation.transfer, "Y");

    char buff[BUFFSIZE] = "0";
    printf("[%s]buff : %s\n", __FILE__, buff);

    DailyAccountInformation *dailyAccountInformations;


    for(i = 0; i < MAXCLIENT ; i++){
        accountBusAndMetro[i] = 0;
    }

    while(self->running) {

        sleep(5);
        dailyAccountInformations = self->networkInterface->listenTerminal(self->networkInterface);

        for(i = 0; i < MAXCLIENT; i++) {
            printf("dailyAccountSize : %d\n", dailyAccountInformations[i].size);
            for(j = 0; j < dailyAccountInformations[i].size; j ++) {
                printf("cardId %d : %s\n", j, dailyAccountInformations[i].cardInformations[j].cardId);
                printf("inOut %d : %s\n", j, dailyAccountInformations[i].cardInformations[j].count);
            }
        }

        //TODO: listenTerminal에서 CardInformation배열을 return하게 / output parameter를 사용하는 식으로 수정해서 이 부분에서 그걸 파일로 쓰게 할 것.
        //divideEachCardInformation(dailyAccountInformations);
        //writeDailyInfo();


        //printf("[%s:%d]SUCCESS listenTerminal", __FILE__, __LINE__);
        //self->accountSystemNetworkInterface->sendData(self->accountSystemNetworkInterface, 5);
        //self->accountSystemNetworkInterface->sendData(self->accountSystemNetworkInterface, (void*) &cardInformation);
        self->networkInterface->sendData(self->networkInterface, &cardInformation, 1);


    }



}

// 이 함수 호출 시 실제로 소켓 열어서 통신해서 값을 가져오게 할 것
static void getDailyData(AccountSystem* self, int type) {

    printf("AccountSystem::getDailyData\n");

    switch(type) {
        case BUSTERMINAL:
            printf("get daily information from bus terminal\n");
            break;
        case METROTERMINAL:
            printf("get daily information from metro terminal\n");
            break;

        default:
            break;
    }

}

void deleteAccountSystem(AccountSystem *self) {
    self->running = false;
    deleteNetworkInterface(self->networkInterface);

    free(self);
}

AccountSystem* newAccountSystem() {
    printf("initAccountSystem\n");

    AccountSystem* accountSystem = (AccountSystem *)malloc(sizeof(AccountSystem));
    memset(accountSystem, 0, sizeof(AccountSystem));

    accountSystem->networkInterface = newNetworkInterfaceForServer();


    // set function to function pointer of AccountSystem
    accountSystem->run = &run;
    accountSystem->getDailyData = &getDailyData;
    accountSystem->display = &display;
    accountSystem->sendDataToEnterpriseServer = &sendDataToEnterpriseServer;
    accountSystem->sendAccountAlarmToTerminal = &sendAccountAlarmToTerminal;


    return accountSystem;
}
