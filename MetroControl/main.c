#include "../CommonImplement/PrecompiledHeader.h"
#include "MetroControl.h"

int main() {

    MetroControl *metroControl = newMetroControl();
    metroControl->run(metroControl);

    return 0;
}