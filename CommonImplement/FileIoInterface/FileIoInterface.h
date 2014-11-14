
typedef struct FileIoInterface {

    FILE *file;

    char* (*readFile)(struct FileIoInterface *self, char* path);


} FileIoInterface;

FileIoInterface* newFileIoInterface();
char* readFile(FileIoInterface *self, char* path);