#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

#include "CommunicationDefinition.h"


struct TerminalInterface;
typedef struct AccountSystem {

    struct TerminalInterface* terminalInterface;

    void (*run)(struct AccountSystem* self);
    void (*getDailyData)(struct AccountSystem* self, int type);
    void (*display)(struct AccountSystem* self);
    void (*sendDataToEnterpriseServer)(struct AccountSystem* self);
    void (*sendAccountAlarmToTerminal)(struct AccountSystem* self);

} AccountSystem;


AccountSystem* makeAccountSystem();
void run(AccountSystem* self);

void getDailyData(AccountSystem* self, int type);

void display(struct AccountSystem *self);

void sendDataToEnterpriseServer(struct AccountSystem *self);

void sendAccountAlarmToTerminal(struct AccountSystem *self);