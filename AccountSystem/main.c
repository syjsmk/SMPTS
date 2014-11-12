#include "PrecompiledHeader.h"

int main() {

  AccountSystem* accountSystem = makeAccountSystem();
  accountSystem->run(accountSystem);

  printf("main\n");


  return 0;
}
