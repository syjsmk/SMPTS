
typedef struct BusControl {

    NetworkInterface *busControlNetworkInterface;
    FileIoInterface *fileIoInterface;

    void (*run)(struct BusControl* self);


} BusControl;


BusControl* makeBusControl();

void run(BusControl* self);
