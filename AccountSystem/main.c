#include "PrecompiledHeader.h"

int main() {

    printf("dasdasd\n");
    AccountSystem *accountSystem = makeAccountSystem();

    printf("main\n");

    //accountSystem->run(accountSystem);
    accountSystem->getDailyData(accountSystem, 1);




    return 0;
}
