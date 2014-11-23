#include "../CommonImplement/PrecompiledHeader.h"
#include "MetroControl.h"

MetroControl* newMetroControl() {
    MetroControl *metroControl = (MetroControl *)malloc(sizeof(MetroControl));

    metroControl->metroControlNetworkInterface = newNetworkInterfaceForClient();



    //
    metroControl->run = &run;

    return metroControl;
}

void run(MetroControl* self) {
    printf("BusControl::run\n");

//    CardInformation cardInformation;
//    cardInformation.latestTaggedTime = "200706171430";
//    cardInformation.transportType = "10";
//    cardInformation.inOut = "100";
//    cardInformation.count = "3000";
//    cardInformation.boardingTerminal = "800_4";
    CardInformation cardInformation;
    strncpy(cardInformation.latestTaggedTime, "20070617143054", 1024);
    strncpy(cardInformation.transportType, "10", 1024);
    strncpy(cardInformation.inOut, "100", 1024);
    strncpy(cardInformation.count, "3000", 1024);
    strncpy(cardInformation.boardingTerminal, "600_4", 1024);


    while(true) {
        //self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, 9);
        self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, (void*)&cardInformation);
        self->metroControlNetworkInterface->listenTerminal(self->metroControlNetworkInterface);
        sleep(1);
    }

}