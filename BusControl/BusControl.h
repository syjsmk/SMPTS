

typedef struct BusControl {

    void (*run)(struct BusControl* self);

} BusControl;


BusControl* makeBusControl();

void run(BusControl* self);