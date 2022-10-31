#pragma once

using namespace std;

//creates itself, binds then listens
class SmartSocket{
    int fd = -1;
    sockaddr_in hint;
public:
    SmartSocket(int portnum);
    void init();
    int getFd();
};