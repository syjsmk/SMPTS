#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

BusControl* makeBusControl() {
    BusControl* busControl = (BusControl *)malloc(sizeof(BusControl));



    //
    busControl->run = &run;

    return busControl;
}

void run(BusControl* self) {
    printf("BusControl::run\n");
}