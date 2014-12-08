typedef struct BusControl {

    NetworkInterface *busControlNetworkInterface;
    FileIoInterface *fileIoInterface;
    InnerTimer *innerTimer;
    char* dailyInfoPath;

    int userCount;
    int userList[MAXIMUMUSER];

    DailyAccountInformation dailyAccountInformation;
    void (*run)(struct BusControl* self);
    //void* (*sendDailyDataLoop)(struct BusControl* data);
    //bool (*cashAccount)(struct BusControl* self, CardInformation inputcardinfo);
    bool (*cashAccount)(struct BusControl* self, CardInformation *inputcardinfo, int inout, int userID);
    void (*printUsers)(struct BusControl* self);


} BusControl;


BusControl* newBusControl();
void* getUserInputLoop(void* data);
void* sendDailyDataLoop(void* data);
//bool cashAccount(BusControl* self, CardInformation inputcardinfo);
void printUserList(BusControl* self);
void printUsers(BusControl* self);
void rideBus(BusControl *self, int userID);
void rideOffBus(BusControl *self, int userID);
void initFile(BusControl* self, char* path, int *dailyInfoSize);