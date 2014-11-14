#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

BusControl* makeBusControl() {
    BusControl *busControl = (BusControl *)malloc(sizeof(BusControl));

    busControl->busControlNetworkInterface = newNetworkInterfaceForClient();
    busControl->fileIoInterface = newFileIoInterface();



    //
    busControl->run = &run;

    return busControl;
}

void run(BusControl* self) {
    printf("BusControl::run\n");

    char* path = "test.txt";
    char buff[BUFFSIZE];
    self->fileIoInterface->readFile(self->fileIoInterface, path);
    //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));

    //printf("Read from FileIoInterface : %s\n", buff);

    //while(true) {
        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);
    //}

}