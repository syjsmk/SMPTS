#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

BusControl* makeBusControl() {
    BusControl *busControl = (BusControl *)malloc(sizeof(BusControl));

    busControl->busControlNetworkInterface = newNetworkInterfaceForClient();



    //
    busControl->run = &run;

    return busControl;
}

void run(BusControl* self) {
    printf("BusControl::run\n");

    self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
    self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);
}