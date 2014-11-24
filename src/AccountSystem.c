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

static void run(AccountSystem* self) {

    printf("AccountSystem::run\n");

    //여기서 반복적으로 돌게? 두 번 돌고 나서 DailyAccountInformation이 생성되었을것이라고 가정.

    CardInformation cardInformation;
    strncpy(cardInformation.latestTaggedTime, "20070617143054", 1024);
    strncpy(cardInformation.transportType, "10", 1024);
    strncpy(cardInformation.inOut, "100", 1024);
    strncpy(cardInformation.count, "3000", 1024);
    strncpy(cardInformation.boardingTerminal, "300_4", 1024);



    while(true) {
        self->accountSystemNetworkInterface->listenTerminal(self->accountSystemNetworkInterface);
        //self->accountSystemNetworkInterface->sendData(self->accountSystemNetworkInterface, 5);
        self->accountSystemNetworkInterface->sendData(self->accountSystemNetworkInterface, (void*) &cardInformation);
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

AccountSystem* newAccountSystem() {
    printf("initAccountSystem\n");

    AccountSystem* accountSystem = (AccountSystem *)malloc(sizeof(AccountSystem));
    accountSystem->accountSystemNetworkInterface = newNetworkInterfaceForServer();


    // set function to function pointer of AccountSystem
    accountSystem->run = &run;
    accountSystem->getDailyData = &getDailyData;
    accountSystem->display = &display;
    accountSystem->sendDataToEnterpriseServer = &sendDataToEnterpriseServer;
    accountSystem->sendAccountAlarmToTerminal = &sendAccountAlarmToTerminal;


    return accountSystem;
}