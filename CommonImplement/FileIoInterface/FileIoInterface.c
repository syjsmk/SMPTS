#include "../PrecompiledHeader.h"

FileIoInterface* newFileIoInterface() {
    FileIoInterface *fileIoInterface = (FileIoInterface *)malloc(sizeof(FileIoInterface));




    //////// add function to function pointer
    fileIoInterface->readCard = &readCard;
    fileIoInterface->writeCard = &writeCard;



    return fileIoInterface;
}


CardInformation readCard(FileIoInterface *self, char* path) {
//char* readFile(FileIoInterface *self, char* path) {

    CardInformation readedCardInformation;
    char buff[BUFFSIZE] = "";
    int readedSize = 0;
    FILE* file;

    memset(buff, 0, BUFFSIZE);

    // O_RDWR | O_CREAT | O_TRUNC
    // "./test.txt"
   // fileDescriptor = open(path, O_RDWR);
    file = fopen(path, "rw");

   /* if(fileDescriptor < 0) {
        perror("file not exist");
    }
*/
    if(file == NULL) {
        perror("file open error\n");
    }

    fgets(readedCardInformation.cardId, CARDIDSIZE, file);
    fgets(readedCardInformation.latestTaggedTime, TIMESIZE, file);
    fgets(readedCardInformation.transportType, TRANSPORTTYPESIZE, file);
    fgets(readedCardInformation.inOut, INOUTTYPESIZE, file);
    fgets(readedCardInformation.count, MONEYSIZE, file);
    fgets(readedCardInformation.boardingTerminal, LINESIZE, file);
    fgets(readedCardInformation.transfer, TRANSFERSIZE, file);


    printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n", readedCardInformation.cardId, readedCardInformation.latestTaggedTime, readedCardInformation.transportType, readedCardInformation.inOut, readedCardInformation.count, readedCardInformation.boardingTerminal, readedCardInformation.transfer);

    fclose(file);



    //return data;
    return readedCardInformation;
}

void writeCard(struct FileIoInterface *self, CardInformation cardInformation, char* path) {
    printf("FileIoInterface::writeCard\n");

    FILE* file;
    file = fopen(path, "a");

    if(file == NULL) {
        perror("file open error\n");
    }

    printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n", cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut, cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);

    fputs(cardInformation.cardId, file);
    fputs(cardInformation.latestTaggedTime, file);
    fputs(cardInformation.transportType, file);
    fputs(cardInformation.inOut, file);
    fputs(cardInformation.count, file);
    fputs(cardInformation.boardingTerminal, file);
    fputs(cardInformation.transfer, file);
    fputs("\n", file);

    fclose(file);


}