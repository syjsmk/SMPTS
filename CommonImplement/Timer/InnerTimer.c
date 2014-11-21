#include "../PrecompiledHeader.h"


InnerTimer* newInnerTimer() {
    InnerTimer *innerTimer = (InnerTimer *)malloc(sizeof(InnerTimer));


    innerTimer->getTime = &getTime;


    return innerTimer;
}

char* getTime(struct InnerTimer *self) {

    time_t ltime;
    struct tm *today;
    char cur_time[12];

    time(&ltime);
    today = localtime(&ltime);

    sprintf(cur_time,"%04d%02d%02d%02d%02d\n",
            today->tm_year + 1900,
            today->tm_mon + 1,
            today->tm_mday,
            today->tm_hour,
            today->tm_min);

    printf("currentTime : %s\n",cur_time);
    return cur_time;
}