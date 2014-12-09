#include "SMPTS.h"

static void run(MetroControl* self) {
    char buff[BUFFSIZE] = "a";
    int i;
    char *path = "SampleMetroCard.txt";
    
    printf("MetroControl::run\n");

    {
        // TODO: len is only two values

        unsigned int dailyInfoSize = 0;
        dailyInfoSize = self->fileIoInterface->getDailyInfoSize(self->fileIoInterface, path);
        CardInformation cardInformations[dailyInfoSize];

        memset(cardInformations, 0, sizeof(CardInformation) * dailyInfoSize);

        for (i = 0; i < dailyInfoSize; i++) {
            CardInformation cardInformation;
            memset(&cardInformation, 0, sizeof(cardInformation));

            CardInformation cis[dailyInfoSize];
            memset(&cis, 0, sizeof(CardInformation) * dailyInfoSize);


            self->fileIoInterface->readCard(self->fileIoInterface, path, &cardInformation);
            //TODO: self->fileIoInterface->writeCard(self->fileIoInterface, path, &cardInformation);
            //TODO: self->fileIoInterface->writeCard(self->fileIoInterface, "dailyInfo.txt", &cardInformation);

            self->fileIoInterface->readDailyInfo(self->fileIoInterface, path, cis);

            //memcpy(&cardInformations[i], &cardInformation, sizeof(CardInformation));
            memcpy(&cardInformations[i], &cis[i], sizeof(CardInformation));

//            printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
//                    cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);
        }


        while (true) {
            sleep(30);
            //self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, 9);
            //self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, (void*)&cardInformation);
            self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, cardInformations, dailyInfoSize);
            self->metroControlNetworkInterface->listenTerminal(self->metroControlNetworkInterface);

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