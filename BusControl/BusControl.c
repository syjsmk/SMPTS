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
    CardInformation cardInformation;
    cardInformation = self->fileIoInterface->readCard(self->fileIoInterface, path);
    printf("\n---------------------------------------------------------------------\nbuff : %stransportType : %sINOUT : %scount : %sterminal : %s\n---------------------------------------------------------------------\n", cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal);
    //self->fileIoInterface->readFile(self->fileIoInterface, path);
    //strncpy(buff, (self->fileIoInterface->readFile(self->fileIoInterface, path)), sizeof(self->fileIoInterface->readFile(self->fileIoInterface, path)));

    //printf("Read from FileIoInterface : %s\n", buff);

    //self->fileIoInterface->writeCard(self->fileIoInterface, cardInformation, "writeCard.txt");

    //while(true) {
        self->busControlNetworkInterface->sendData(self->busControlNetworkInterface, 3);
        self->busControlNetworkInterface->listenTerminal(self->busControlNetworkInterface);
    //}
}

char* show_time() {
	time_t ltime;
	struct tm *today;
	char cur_time[12];

	time(&ltime);
	today = localtime(&ltime);
	
	sprintf(cur_time,"%04d%02d%02d%02d%02d\n",
	today->tm_year + 1900, 
	today->tm_mon + 1,
	today->tm_mday,
	today->tm_hour,
	today->tm_min);
	
	printf("����ð����:%s\n",cur_time);
	return *cur_time;
}