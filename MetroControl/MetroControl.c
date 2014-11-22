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

    while(true) {
        self->metroControlNetworkInterface->sendData(self->metroControlNetworkInterface, 9);
        self->metroControlNetworkInterface->listenTerminal(self->metroControlNetworkInterface);
        sleep(1);
    }

}