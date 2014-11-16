typedef struct BusControl {

    NetworkInterface *busControlNetworkInterface;
    FileIoInterface *fileIoInterface;

    DailyAccountInformation dailyAccountInformation;

    void (*run)(struct BusControl* self);


} BusControl;


BusControl* makeBusControl();

void run(BusControl* self);
