typedef struct BusControl {

    NetworkInterface *busControlNetworkInterface;
    FileIoInterface *fileIoInterface;
    InnerTimer *innerTimer;
    char* users[30];

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
void printUsers(BusControl* self);