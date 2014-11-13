#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

BusControl* makeBusControl() {
    BusControl *busControl = (BusControl *)malloc(sizeof(BusControl));

    busControl->networkInterface = newNetworkInterfaceForClient();



    //
    busControl->run = &run;

    return busControl;
}

void run(BusControl* self) {
    printf("BusControl::run\n");

    self->networkInterface->sendData(self->networkInterface, 3);
}