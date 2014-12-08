typedef struct AccountSystem {

    NetworkInterface *networkInterface;
    bool running;



    void (*run)(struct AccountSystem* self);
    void (*getDailyData)(struct AccountSystem* self, int type);
    void (*display)(struct AccountSystem* self);
    void (*sendDataToEnterpriseServer)(struct AccountSystem* self);
    void (*sendAccountAlarmToTerminal)(struct AccountSystem* self);
} AccountSystem;


AccountSystem* newAccountSystem();
void deleteAccountSystem(AccountSystem *self);
int accountBusAndMetro[2];