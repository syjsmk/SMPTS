#include "../CommonImplement/PrecompiledHeader.h"
#include "AccountSystem.h"

int main() {

    AccountSystem *accountSystem = newAccountSystem();

    printf("main\n");

    accountSystem->run(accountSystem);
    //accountSystem->getDailyData(accountSystem, 1);




    return 0;
}