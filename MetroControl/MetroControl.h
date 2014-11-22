
typedef struct MetroControl {

    NetworkInterface *metroControlNetworkInterface;
    void (*run)(struct MetroControl* self);


} MetroControl;


MetroControl* newMetroControl();

void run(MetroControl* self);
