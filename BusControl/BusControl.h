typedef struct BusControl {

    NetworkInterface *busControlNetworkInterface;
    FileIoInterface *fileIoInterface;
    InnerTimer *innerTimer;

    DailyAccountInformation dailyAccountInformation;

    void (*run)(struct BusControl* self);
    void* (*sendDailyDataLoop)(void* data);


} BusControl;


BusControl* newBusControl();

void run(BusControl* self);
void* getUserInputLoop(void* data);
void* sendDailyDataLoop(void* data);