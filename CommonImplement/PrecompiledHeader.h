#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h> // non-blocking과 관련된 기능 제공
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>


#include "DailyAccountInformation.h"
#include "CommunicationDefinition.h"
#include "NetworkInterface/NetworkInterface.h"