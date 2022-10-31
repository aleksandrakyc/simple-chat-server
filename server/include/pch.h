#ifndef PCH_H
#define PCH_H

#define NUM_FDS 5
#define BACKLOG 10
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <poll.h>
#include <memory>
#include <cstring>
#include <iostream>
#include "PollEvent.h"
#include "SmartSocket.h"

#endif // !PCH_H