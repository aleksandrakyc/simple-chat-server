#pragma once

using namespace std;

class PollEvent
{    
    pollfd* events;
    int numfds;
    int maxfds;
    //store listener?
    int listener;

public:
    PollEvent(int fd);
    ~PollEvent();
    void _close(int fd);
    pollfd* jump(int fd);
    void add(int fd_new);
    void makeSpace();
    int getNumfds();
    void _poll();
};
