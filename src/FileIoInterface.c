#include "SMPTS.h"

FileIoInterface* newFileIoInterface() {
    FileIoInterface *fileIoInterface = (FileIoInterface *)malloc(sizeof(FileIoInterface));




    //////// add function to function pointer
    fileIoInterface->readCard = &readCard;
    fileIoInterface->writeCard = &writeCard;
    fileIoInterface->getDailyInfoSize = &getDailyInfoSize;



    return fileIoInterface;
}


void readCard(FileIoInterface *self, char* path, CardInformation *outCardInformation) {
//char* readFile(FileIoInterface *self, char* path) {

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


    //printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
     //       cardInformation.cardId, cardInformation.latestTaggedTime, cardInformation.transportType, cardInformation.inOut,
      //      cardInformation.count, cardInformation.boardingTerminal, cardInformation.transfer);

    fclose(file);

    memcpy(outCardInformation, &cardInformation, sizeof(cardInformation));

    //return data;
}

void writeCard(struct FileIoInterface *self, const CardInformation *cardInformation, char* path) {
   // printf("FileIoInterface::writeCard\n");

    assert(cardInformation != NULL);
    assert(path != NULL);

    FILE* file;
    file = fopen(path, "a");

    if(file == NULL) {
        perror("file open error\n");
    }

   // printf("-------------------------FileIO Terminal-------------------------------\ncardId : %s lastestTime : %s transportType : %s INOUT : %s count : %s terminal : %s transfer : %s\n",
   //         cardInformation->cardId, cardInformation->latestTaggedTime, cardInformation->transportType, cardInformation->inOut, cardInformation->count, cardInformation->boardingTerminal, cardInformation->transfer);

    fputs(cardInformation->cardId, file);
    fputs(cardInformation->latestTaggedTime, file);
    fputs(cardInformation->transportType, file);
    fputs(cardInformation->inOut, file);
    fputs(cardInformation->count, file);
    fputs(cardInformation->boardingTerminal, file);
    fputs(cardInformation->transfer, file);
    fputs("\n", file);

    fclose(file);


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


    fclose(file);
    //printf("The file has %d lines\n ", count);
    dailyInfoSize = (count + 1) / CARDINFORMATIONVALUECOUNT;

    return dailyInfoSize;
}