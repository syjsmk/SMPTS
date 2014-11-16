#define TIMESIZE 12
#define TRANSPORTTYPESIZE 2
#define INOUTTYPESIZE 3

#define BUS 10
#define METRO 11

#define IN 100
#define OUT 101

#define LINEFEEDBUFF 255

#define LINESIZE 255


typedef struct CardInformation {

    char latestTaggedTime[TIMESIZE];
    char transportType[TRANSPORTTYPESIZE];
    char inOut[INOUTTYPESIZE];
    char count[LINESIZE];
    char boardingTerminal[LINESIZE];

} CardInformation;