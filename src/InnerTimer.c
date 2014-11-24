#include "SMPTS.h"


InnerTimer* newInnerTimer() {
    InnerTimer *innerTimer = (InnerTimer *)malloc(sizeof(InnerTimer));


    innerTimer->getTime = &getTime;


    return innerTimer;
}

void getTime(struct InnerTimer *self, char *buffer) {

    time_t ltime;
    struct tm *today;
    char cur_time[14];

    time(&ltime);
    today = localtime(&ltime);

    sprintf(cur_time,"%04d%02d%02d%02d%02d%02d\n",
            today->tm_year + 1900,
            today->tm_mon + 1,
            today->tm_mday,
            today->tm_hour,
            today->tm_min,
            today->tm_sec);

    printf("currentTime : %s\n",cur_time);
    
	strncpy(buffer, cur_time, 14);
}