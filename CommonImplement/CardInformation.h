#define TIMESIZE 13
#define TRANSPORTTYPESIZE 3
#define INOUTTYPESIZE 4

#define BUS 10
#define METRO 11

#define IN 100
#define OUT 101

#define LINEFEEDBUFF 255

#define LINESIZE 5


typedef struct CardInformation {

    char latestTaggedTime[TIMESIZE];
    char transportType[TRANSPORTTYPESIZE];
    char inOut[INOUTTYPESIZE];
    char count[LINESIZE];
    char boardingTerminal[LINESIZE];

} CardInformation;