
typedef struct BusControl {

    NetworkInterface *busControlNetworkInterface;
    void (*run)(struct BusControl* self);


} BusControl;


BusControl* makeBusControl();

void run(BusControl* self);
