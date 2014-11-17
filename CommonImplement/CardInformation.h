#define TIMESIZE 1024
#define TRANSPORTTYPESIZE 1024
#define INOUTTYPESIZE 1024

#define BUS 10
#define METRO 11

#define IN 100
#define OUT 101

#define LINEFEEDBUFF 255

#define MONEYSIZE 1024
#define LINESIZE 1024


typedef struct CardInformation {

    char latestTaggedTime[TIMESIZE];
    char transportType[TRANSPORTTYPESIZE];
    char inOut[INOUTTYPESIZE];
    char count[MONEYSIZE];
    char boardingTerminal[LINESIZE];

} CardInformation;