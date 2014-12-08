#include "SMPTS.h"

FileIoInterface* newFileIoInterface() {
    FileIoInterface *fileIoInterface = (FileIoInterface *)malloc(sizeof(FileIoInterface));




    //////// add function to function pointer
    fileIoInterface->readCard = &readCard;
    fileIoInterface->writeCard = &writeCard;
    fileIoInterface->getDailyInfoSize = &getDailyInfoSize;
    fileIoInterface->readDailyInfo = &readDailyInfo;


    return fileIoInterface;
}

// TODO: 한 번만 읽게 만든게 문제인듯. outCardInformation을 배열로. 일일 정산 정보는 하나가 아니라 여러개 정보가 써있을 수 있으므로.
//void readCard(FileIoInterface *self, char* path, CardInformation **outCardInformations) {
void readCard(FileIoInterface *self, char* path, CardInformation *outCardInformation) {
//char* readFile(FileIoInterface *self, char* path) {

    int outCardInformationSize = 0;
    int i = 0;

    char buff[BUFFSIZE] = "";
    int readedSize = 0;
    FILE* file;
    CardInformation cardInformation;

    assert(outCardInformation != NULL);

    memset(&cardInformation, 0, sizeof(CardInformation));

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



    fgets(cardInformation.cardId, CARDIDSIZE, file);
    fgets(cardInformation.latestTaggedTime, TIMESIZE, file);
    fgets(cardInformation.transportType, TRANSPORTTYPESIZE, file);
    fgets(cardInformation.inOut, INOUTTYPESIZE, file);
    fgets(cardInformation.count, MONEYSIZE, file);
    fgets(cardInformation.boardingTerminal, LINESIZE, file);
    fgets(cardInformation.transfer, TRANSFERSIZE, file);


//    printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
//            cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut,
//            cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);



    fflush(file);
    fclose(file);
    memcpy(outCardInformation, &cardInformation, sizeof(cardInformation));

    //return data;
}

void readDailyInfo(struct FileIoInterface *self, char* path, CardInformation cardInformations[]) {

    int outCardInformationSize = 0;
    int i = 0;

    char buff[BUFFSIZE] = "";
    int readedSize = 0;
    FILE* file;
    CardInformation cardInformation;

    outCardInformationSize = self->getDailyInfoSize(self, path);

    assert(cardInformations != NULL);

    memset(&cardInformation, 0, sizeof(CardInformation));

    file = fopen(path, "rw");

    if(file == NULL) {
        perror("file open error\n");
    }


    for(i = 0; i < outCardInformationSize; i ++) {
        fgets(cardInformation.cardId, CARDIDSIZE, file);
        fgets(cardInformation.latestTaggedTime, TIMESIZE, file);
        fgets(cardInformation.transportType, TRANSPORTTYPESIZE, file);
        fgets(cardInformation.inOut, INOUTTYPESIZE, file);
        fgets(cardInformation.count, MONEYSIZE, file);
        fgets(cardInformation.boardingTerminal, LINESIZE, file);
        fgets(cardInformation.transfer, TRANSFERSIZE, file);

//        printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
//                cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut,
//                cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);

        memcpy(&(cardInformations[i]), &cardInformation, sizeof(cardInformation));
    }

//    for(i = 0; i < outCardInformationSize; i ++) {
//        printf("////////////////////////////////////////////////////\n");
//        printf("FileIO Terminal\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
//        cardInformations[i].cardId, cardInformations[i].latestTaggedTime, cardInformations[i].transportType, cardInformations[i].inOut,
//                cardInformations[i].count, cardInformations[i].boardingTerminal, cardInformations[i].transfer);
//        printf("////////////////////////////////////////////////////\n");
//    }

    fflush(file);
    fclose(file);

}

//void writeCard(struct FileIoInterface *self, const CardInformation *cardInformation, char* path, int option) {
void writeCard(struct FileIoInterface *self, char* path, const CardInformation *cardInformation, int option) {
   // printf("FileIoInterface::writeCard\n");

    assert(cardInformation != NULL);
    assert(path != NULL);

    FILE* file;
//    int fd;
//
//    if(option == APPEND) {
//        fd = open(path, O_APPEND);
//    } else if(option == OVERRIDE) {
//        fd = open(path, O_EXCL);
//    }
//
//    if(file == NULL) {
//        perror("file open error\n");
//    }
//
//   printf("-------------------------write card-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
//            cardInformation->cardId, cardInformation->latestTaggedTime, cardInformation->transportType, cardInformation->inOut, cardInformation->count, cardInformation->boardingTerminal, cardInformation->transfer);
//
//    write(fd, cardInformation->cardId, CARDIDSIZE);
//    write(fd, cardInformation->latestTaggedTime, LINESIZE);
//    write(fd, cardInformation->transportType, LINESIZE);
//    write(fd, cardInformation->inOut, LINESIZE);
//    write(fd, cardInformation->count, LINESIZE);
//    write(fd, cardInformation->boardingTerminal, LINESIZE);
//    write(fd, cardInformation->transfer, LINESIZE);
//
//    close(fd);

    if(option == APPEND) {
        file = fopen(path, "a");
    } else if(option == OVERRIDE) {
        file = fopen(path, "w");
    }

    if(file == NULL) {
        perror("file open error\n");
    }

   printf("-------------------------write card-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
            cardInformation->cardId, cardInformation->latestTaggedTime, cardInformation->transportType, cardInformation->inOut, cardInformation->count, cardInformation->boardingTerminal, cardInformation->transfer);

    fputs(cardInformation->cardId, file);
    fputs(cardInformation->latestTaggedTime, file);
    fputs(cardInformation->transportType, file);
    fputs(cardInformation->inOut, file);
    fputs(cardInformation->count, file);
    fputs(cardInformation->boardingTerminal, file);
    fputs(cardInformation->transfer, file);

//    fwrite(cardInformation->cardId, 1, LINESIZE, file);
//    fwrite(cardInformation->latestTaggedTime, 1, LINESIZE, file);
//    fwrite(cardInformation->transportType, 1, LINESIZE, file);
//    fwrite(cardInformation->inOut, 1, LINESIZE, file);
//    fwrite(cardInformation->count, 1, LINESIZE, file);
//    fwrite(cardInformation->boardingTerminal, 1, LINESIZE, file);
//    fwrite(cardInformation->transfer, 1, LINESIZE, file);
    //fputs("\n", file);

    fflush(file);
    fclose(file);
    printf("close : %d\n", close);


}

int getDailyInfoSize(FileIoInterface *self, char* path) {

    CardInformation readedCardInformation;
    int readedSize = 0;
    FILE* file;
    int count = 0;
    int dailyInfoSize;
    char c;

    file = fopen(path, "rw");

    /* if(fileDescriptor < 0) {
         perror("file not exist");
     }
 */
    if(file == NULL) {
        perror("file open error\n");
    }

    for (c = getc(file); c != EOF; c = getc(file)) {
        if (c == '\n') { // Increment count if this character is newline
            count = count + 1;
        }

    }

    fflush(file);
    fclose(file);
    //printf("The file has %d lines\n ", count);
    dailyInfoSize = (count + 1) / CARDINFORMATIONVALUECOUNT;

    return dailyInfoSize;
}