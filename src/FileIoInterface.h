

//struct CardInformation;
typedef struct FileIoInterface {

    FILE *file;
    CardInformation cardInformation;

    //char* (*readFile)(struct FileIoInterface *self, char* path);
    void (*readCard)(struct FileIoInterface *self, char* path, CardInformation *cardInformation);
    //void (*readCard)(struct FileIoInterface *self, char* path, CardInformation **outCardInformations);
    void (*readDailyInfo)(struct FileIoInterface *self, char* path, CardInformation cardInformations[]);
    void (*writeCard)(struct FileIoInterface *self, char* path, const CardInformation *cardInformation, int option);
    int (*getDailyInfoSize)(struct FileIoInterface *self, char* path);


} FileIoInterface;

FileIoInterface* newFileIoInterface();
//char* readFile(FileIoInterface *self, char* path);
void readCard(FileIoInterface *self, char* path, CardInformation *cardInformation);
//void readCard(FileIoInterface *self, char* path, CardInformation **outCardInformations);
void readDailyInfo(struct FileIoInterface *self, char* path, CardInformation cardInformations[]);
//void writeCard(struct FileIoInterface *self, const CardInformation *cardInformation, char* path, int option);
void writeCard(struct FileIoInterface *self, char* path, const CardInformation *cardInformation, int option);
int getDailyInfoSize(FileIoInterface *self, char* path);