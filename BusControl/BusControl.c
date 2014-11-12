#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

BusControl* makeBusControl() {
    BusControl *busControl = (BusControl *)malloc(sizeof(BusControl));

    busControl->terminalInterface = newTerminalInterfaceForClient();



    //
    busControl->run = &run;

    return busControl;
}

void run(BusControl* self) {
    printf("BusControl::run\n");

    self->terminalInterface->sendData(self->terminalInterface, 3);
}