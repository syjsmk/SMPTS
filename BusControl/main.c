#include "PrecompiledHeader.h"

int main() {

    BusControl* busControl = makeBusControl();
    busControl->run(busControl);

    return 0;
}