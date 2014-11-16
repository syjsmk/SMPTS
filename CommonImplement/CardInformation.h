#define TIMESIZE 12
#define BUS 10
#define METRO 11

#define IN 100
#define OUT 101


typedef struct CardInformation {

    char latestTaggedTime[TIMESIZE];
    int transportType;
    int inOut;
    int count;
    char* boardingTerminal;

} CardInformation;