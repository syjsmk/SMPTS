


struct NetworkInterface;
typedef struct AccountSystem {

    struct NetworkInterface* terminalInterface;

    void (*run)(struct AccountSystem* self);
    void (*getDailyData)(struct AccountSystem* self, int type);
    void (*display)(struct AccountSystem* self);
    void (*sendDataToEnterpriseServer)(struct AccountSystem* self);
    void (*sendAccountAlarmToTerminal)(struct AccountSystem* self);

} AccountSystem;


AccountSystem* newAccountSystem();
void run(AccountSystem* self);

void getDailyData(AccountSystem* self, int type);

void display(AccountSystem *self);

void sendDataToEnterpriseServer(AccountSystem *self);

void sendAccountAlarmToTerminal(AccountSystem *self);