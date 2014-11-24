#include "SMPTS.h"

static void run(MetroControl* self) {
    char buff[BUFFSIZE] = "a";
    CardInformation cardInformation;
    int i;
    char *path = "SampleMetroCard.txt";
    
    printf("BusControl::run\n");

//    CardInformation cardInformation;
//    cardInformation.latestTaggedTime = "200706171430";
//    cardInformation.transportType = "10";
//    cardInformation.inOut = "100";
//    cardInformation.count = "3000";
//    cardInformation.boardingTerminal = "800_4";

    strncpy(cardInformation.latestTaggedTime, "20070617143054", 1024);
    strncpy(cardInformation.transportType, "10", 1024);
    strncpy(cardInformation.inOut, "100", 1024);
    strncpy(cardInformation.count, "3000", 1024);
    strncpy(cardInformation.boardingTerminal, "600_4", 1024);


    for(i = 0; i < 2; i ++) {

        // TODO return 값이 call by value로 인하여 equation을 할경우 안에 들어있는 char[]은 복사가 안된다.
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


    printf("buff : %s\n", buff);

    while(true) {
        //self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, 9);
        //self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, (void*)&cardInformation);
        self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, buff);
        self->metroControlNetworkInterface->listenTerminal(self->metroControlNetworkInterface);
        sleep(1);
    }

}


MetroControl* newMetroControl() {
    MetroControl *metroControl = (MetroControl *)malloc(sizeof(MetroControl));

    metroControl->metroControlNetworkInterface = newNetworkInterfaceForClient();
    metroControl->fileIoInterface = newFileIoInterface();



    //
    metroControl->run = &run;

    return metroControl;
}