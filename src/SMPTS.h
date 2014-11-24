﻿#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h> // non-blocking과 관련된 기능 제공
#include <arpa/inet.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>


#include "CardInformation.h"
#include "DailyAccountInformation.h"
#include "CommunicationDefinition.h"
#include "NetworkInterface.h"
#include "FileIoInterface.h"
#include "InnerTimer.h"
#include "AccountSystem.h"
#include "MetroControl.h"
#include "BusControl.h"

#define printf(...) fprintf(stdout, __VA_ARGS__); fflush(stdout)