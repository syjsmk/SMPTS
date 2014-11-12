#include "PrecompiledHeader.h"

int main() {

    printf("dasdasd\n");
    AccountSystem *accountSystem = makeAccountSystem();

    printf("main\n");

    accountSystem->run(accountSystem);


    return 0;
}
