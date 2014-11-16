#include "../PrecompiledHeader.h"

FileIoInterface* newFileIoInterface() {
    FileIoInterface *fileIoInterface = (FileIoInterface *)malloc(sizeof(FileIoInterface));




    fileIoInterface->readCard = &readCard;


    return fileIoInterface;
}


CardInformation readCard(FileIoInterface *self, char* path) {
//char* readFile(FileIoInterface *self, char* path) {

    CardInformation readedCardInformation;
    char* data = "test";
    char buff[BUFFSIZE] = "";
    int fileDescriptor = 0;
    int readedSize = 0;
    char temp[LINEFEEDBUFF];
    FILE* file;

    memset(buff, 0, BUFFSIZE);

    // O_RDWR | O_CREAT | O_TRUNC
    // "./test.txt"
    fileDescriptor = open(path, O_RDWR);
    file = fopen(path, "rw");

    if(fileDescriptor < 0) {
        perror("file not exist");
    }

    if(file == NULL) {
        perror("file open error\n");
    }

    fgets(readedCardInformation.latestTaggedTime, TIMESIZE, file);
    fgets(temp, LINEFEEDBUFF, file);
    fgets(readedCardInformation.transportType, TRANSPORTTYPESIZE, file);
    fgets(temp, LINEFEEDBUFF, file);
    fgets(readedCardInformation.inOut, INOUTTYPESIZE, file);
    fgets(temp, LINEFEEDBUFF, file);
    fgets(readedCardInformation.count, LINESIZE, file);
    fgets(temp, LINEFEEDBUFF, file);
    // FIXME: 얘 왜 boardingTerminal만 값 안들어가는지 모르겠음.
    fgets(readedCardInformation.boardingTerminal, LINESIZE, file);


//    readedSize = read(fileDescriptor, buff, sizeof(int));
//    printf("buff : %d || readedSize : %d\n", buff, readedSize);
//    printf("buff : %s || readedSize : %d\n", buff, readedSize);
    printf("buff : %s, transportType : %s, INOUT : %s, count : %s, terminal : %s\n", readedCardInformation.latestTaggedTime, readedCardInformation.transportType, readedCardInformation.inOut, readedCardInformation.count, readedCardInformation.boardingTerminal);
//    printf("latestTaggedTime : %s, transportType : %d, inOut : %d, count : %d, boardingTerminal : %s\n", readedCardInformation.latestTaggedTime, readedCardInformation.transportType, readedCardInformation.inOut, readedCardInformation.count, readedCardInformation.boardingTerminal);



    close(fileDescriptor);
    fclose(file);



    //return data;
    return readedCardInformation;
}