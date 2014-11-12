
struct TerminalInterface;
typedef struct BusControl {

    struct TerminalInterface *terminalInterface;
    void (*run)(struct BusControl* self);


} BusControl;


BusControl* makeBusControl();

void run(BusControl* self);
