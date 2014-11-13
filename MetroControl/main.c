#include "../CommonImplement/PrecompiledHeader.h"
#include "MetroControl.h"

int main() {

    MetroControl *metroControl = makeMetroControl();
    metroControl->run(metroControl);

    return 0;
}