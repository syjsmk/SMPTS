

//struct CardInformation;
typedef struct FileIoInterface {

    FILE *file;
    struct CardInformation cardInformation;

    char* (*readFile)(struct FileIoInterface *self, char* path);


} FileIoInterface;

FileIoInterface* newFileIoInterface();
char* readFile(FileIoInterface *self, char* path);