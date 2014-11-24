#include "SMPTS.h"

int main() {

    BusControl* busControl = newBusControl();
    pthread_t thread;
    int threadId;
    char* filePath = "test.txt";




    busControl->run(busControl);

    //threadId = pthread_create(&thread, NULL, run, (void*)filePath);
    //threadId = pthread_create(&thread, NULL, (busControl->sendDailyDataLoop), (void*)filePath);

//    printf("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq\n");
//
//    if(threadId < 0) {
//        perror("thread create error\n");
//    }
//    pthread_join(thread, NULL);





    return 0;
}