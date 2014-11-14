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

    memset(buff, 0, BUFFSIZE);

    // O_RDWR | O_CREAT | O_TRUNC
    // "./test.txt"
    fileDescriptor = open(path, O_RDWR);

    if(fileDescriptor < 0) {
        perror("file not exist");
    }

    readedSize = read(fileDescriptor, buff, BUFFSIZE);
    //readedSize = read(fileDescriptor, readedCardInformation, sizeof(CardInformation));
    //printf("buff : %d || readedSize : %d\n", buff, readedSize);
    printf("buff : %s || readedSize : %d\n", buff, readedSize);
    close(fileDescriptor);



    //return data;
    return readedCardInformation;
}