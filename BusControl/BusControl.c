#include "PrecompiledHeader.h"

BusControl* makeBusControl() {
    BusControl* busControl = (BusControl *)malloc(sizeof(BusControl));



    //
    busControl->run = &run;

    return busControl;
}

void run(BusControl* self) {
    printf("BusControl::run\n");
}