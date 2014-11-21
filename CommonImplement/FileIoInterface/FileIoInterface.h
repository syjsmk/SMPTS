

//struct CardInformation;
typedef struct FileIoInterface {

    FILE *file;
    CardInformation cardInformation;

    //char* (*readFile)(struct FileIoInterface *self, char* path);
    CardInformation (*readCard)(struct FileIoInterface *self, char* path);
    void (*writeCard)(struct FileIoInterface *self, CardInformation cardInformation, char* path);


} FileIoInterface;

FileIoInterface* newFileIoInterface();
//char* readFile(FileIoInterface *self, char* path);
CardInformation readCard(FileIoInterface *self, char* path);
void writeCard(struct FileIoInterface *self, CardInformation cardInformation, char* path);