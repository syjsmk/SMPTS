
typedef struct MetroControl {

    NetworkInterface *metroControlNetworkInterface;
    FileIoInterface *fileIoInterface;
    void (*run)(struct MetroControl* self);


} MetroControl;


MetroControl* newMetroControl();

