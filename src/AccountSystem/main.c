#include "SMPTS.h"

int main() {

    printf("Account System Start\n");

    AccountSystem *accountSystem = newAccountSystem();

    printf("main\n");

    accountSystem->run(accountSystem);
    //accountSystem->getDailyData(accountSystem, 1);




    return 0;
}
