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

    printf("%s\n", __FUNCTION__);

    //여기서 반복적으로 돌게? 두 번 돌고 나서 DailyAccountInformation이 생성되었을것이라고 가정.

    assert(self != NULL);
    assert(self->networkInterface != NULL);

    self->running = true;

    CardInformation cardInformation;
    memset(&cardInformation, 0, sizeof(CardInformation));
    strncpy(cardInformation.cardId, "asd_123", sizeof(cardInformation.cardId));
    strncpy(cardInformation.latestTaggedTime, "20070617143054", sizeof(cardInformation.latestTaggedTime));
    strncpy(cardInformation.transportType, "10", sizeof(cardInformation.transportType));
    strncpy(cardInformation.inOut, "100", sizeof(cardInformation.inOut));
    strncpy(cardInformation.count, "3000", sizeof(cardInformation.count));
    strncpy(cardInformation.boardingTerminal, "300_4", sizeof(cardInformation.boardingTerminal));
    strncpy(cardInformation.transfer, "Y", sizeof(cardInformation.transfer));

    char buff[BUFFSIZE] = "0";
    printf("[%s]buff : %s\n", __FILE__, buff);

    while(self->running) {
        printf("running is true");

        self->networkInterface->listenTerminal(self->networkInterface);
        printf("[%s:%d]SUCCESS listenTerminal", __FILE__, __LINE__);
        //self->accountSystemNetworkInterface->sendData(self->accountSystemNetworkInterface, 5);
        //self->accountSystemNetworkInterface->sendData(self->accountSystemNetworkInterface, (void*) &cardInformation);
        self->networkInterface->sendData(self->networkInterface, &cardInformation, 1);
        printf("start sleeping");
        sleep(1);
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