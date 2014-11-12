#include "../CommonImplement/PrecompiledHeader.h"
#include "BusControl.h"

int main() {

    BusControl* busControl = makeBusControl();
    busControl->run(busControl);




    return 0;
}