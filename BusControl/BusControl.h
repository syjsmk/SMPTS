typedef struct BusControl {

    NetworkInterface *busControlNetworkInterface;
    FileIoInterface *fileIoInterface;
    InnerTimer *innerTimer;

    DailyAccountInformation dailyAccountInformation;

    void (*run)(struct BusControl* self);


} BusControl;


BusControl* makeBusControl();

void run(BusControl* self);
