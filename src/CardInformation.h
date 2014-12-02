#define TIMESIZE 256
#define TRANSPORTTYPESIZE 256
#define INOUTTYPESIZE 256

#define BUS 10
#define METRO 11

#define IN 100
#define OUT 101

#define LINEFEEDBUFF 255

#define MONEYSIZE 256
#define LINESIZE 256
#define CARDIDSIZE 256
#define TRANSFERSIZE 256

#define CARDINFORMATIONVALUECOUNT 7

#define MAXIMUMUSER 10

typedef struct CardInformation {

    char cardId[CARDIDSIZE];
    char latestTaggedTime[TIMESIZE];
    char transportType[TRANSPORTTYPESIZE];
    char inOut[INOUTTYPESIZE];
    char count[MONEYSIZE];
    char boardingTerminal[LINESIZE]; // 1: 동대문 , 2: 건대입구, 3: 강남, 4: 신림, 5: 합정
    char transfer[TRANSFERSIZE]; // Y/N으로만 구분


} CardInformation;