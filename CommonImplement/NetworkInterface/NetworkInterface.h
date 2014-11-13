

/*
listen을 하다가 먼저 들어오는쪽의 데이터를 저장함.
한 번 저장하고 나면 해당 소켓을 close하고 다시 대기.

BusTerminal인지 MetroTerminal인지 구분은 그쪽에서 데이터를 보내주지 않는 한은
구분할 수 없다는 것 같음. 따라서 자기가 어느쪽 터미널인지는 그쪽에서
먼저 값을 주게 함.
 */
struct sockaddr_in;
typedef struct NetworkInterface {

    // serverSocketFd = 서버의 소켓, connectedClientSocketFd = 서버에 연결된 클라이언트와 통신하기 위한 소켓
    int serverSocketFd, connectedClientSocketFd, terminalType, terminalAddrLength;

    // client측에서 접속하기 위해 사용할 소켓
    int clientSocketFd;

    // 서버측에서 사용하기 위한 sockaddr_in
    struct sockaddr_in serverAddr, connectedClientAddr;

    // 클라이언트측에서 사용하기 위한 sockaddr_in
    struct sockaddr_in clientToServerAddr;

    DailyAccountInformation busDailyAccountInformation, metroDailyAccountInformation;

    // ready를 호출하면 소켓을 열고 외부의 접속을 기다리는 상태가 됨.
    // Terminal측에서 socket을 통해서 dailyAccountInformation을 받는 순간 구조체에 쓰고 소켓이 종료되게.
    void (*listenTerminal)(struct NetworkInterface* self);
    DailyAccountInformation (*writeDailyAccountInformation)(struct NetworkInterface* self);
    void (*sendData)(struct NetworkInterface* self, int data); // TODO : void* data 이런 식으로 뭐든지 받을 수 있게.
    bool (*isServer)(struct NetworkInterface* self);
    void (*deleteNetworkInterface)(struct NetworkInterface* self);


} NetworkInterface;

NetworkInterface *newNetworkInterfaceForServer();
NetworkInterface *newNetworkInterfaceForClient();
void waitData(NetworkInterface *self);
DailyAccountInformation writeDailyAccountInformation(NetworkInterface* self);
void sendData(NetworkInterface* self, int data);
bool isServer(NetworkInterface* self);
void deleteNetworkInterface(struct NetworkInterface* self);