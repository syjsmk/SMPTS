
struct NetworkInterface;
typedef struct BusControl {

    struct NetworkInterface* networkInterface;
    void (*run)(struct BusControl* self);


} BusControl;


BusControl* makeBusControl();

void run(BusControl* self);
