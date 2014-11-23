typedef struct BusControl {

    NetworkInterface *busControlNetworkInterface;
    FileIoInterface *fileIoInterface;
    InnerTimer *innerTimer;

    DailyAccountInformation dailyAccountInformation;

    void (*run)(struct BusControl* self);
    void* (*sendDailyDataLoop)(void* data);
    //bool (*cashAccount)(struct BusControl* self, CardInformation inputcardinfo);
    bool (*cashAccount)(struct BusControl* self, CardInformation inputcardinfo, int inout, int userID);


} BusControl;


BusControl* newBusControl();

void run(BusControl* self);
void* getUserInputLoop(void* data);
void* sendDailyDataLoop(void* data);
//bool cashAccount(BusControl* self, CardInformation inputcardinfo);
bool cashAccount(BusControl* self, CardInformation inputcardinfo, int inout, int userID);