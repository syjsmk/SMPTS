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
#define CARDIDSIZE 1024
#define TRANSFERSIZE 1024



typedef struct CardInformation {

    char cardId[CARDIDSIZE];
    char latestTaggedTime[TIMESIZE];
    char transportType[TRANSPORTTYPESIZE];
    char inOut[INOUTTYPESIZE];
    char count[MONEYSIZE];
    char boardingTerminal[LINESIZE]; // 1: 동대문 , 2: 건대입구, 3: 강남, 4: 신림, 5: 합정
    char transfer[TRANSFERSIZE]; // Y/N으로만 구분


} CardInformation;