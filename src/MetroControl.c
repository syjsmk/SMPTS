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

    {
        // TODO: len is only two values
        const unsigned int len = 2;
        CardInformation cardInformations[len];

        memset(cardInformations, 0, sizeof(CardInformation) * len);

        for (i = 0; i < 2; i++) {
            CardInformation cardInformation;
            memset(&cardInformation, 0, sizeof(cardInformation));

            CardInformation cis[len];
            memset(&cis, 0, sizeof(CardInformation) * len);


            self->fileIoInterface->readCard(self->fileIoInterface, path, &cardInformation);
            //TODO: self->fileIoInterface->writeCard(self->fileIoInterface, path, &cardInformation);
            //TODO: self->fileIoInterface->writeCard(self->fileIoInterface, "dailyInfo.txt", &cardInformation);

            self->fileIoInterface->readDailyInfo(self->fileIoInterface, path, cis);

            //memcpy(&cardInformations[i], &cardInformation, sizeof(CardInformation));
            memcpy(&cardInformations[i], &cis[i], sizeof(CardInformation));

            printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
                    cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);
        }


        while (true) {
            //self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, 9);
            //self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, (void*)&cardInformation);
            self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, cardInformations, len);
            self->metroControlNetworkInterface->listenTerminal(self->metroControlNetworkInterface);
            sleep(3);
        }
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