#include "pch.h"

PollEvent::PollEvent(int fd){
    this->events = (pollfd*)malloc (NUM_FDS * sizeof (struct pollfd));
    this->events->fd = fd;
    //?
    this->listener = fd;
    //
    this->events->events = POLLIN;
    this->events->revents = 0;
    this->numfds = 1;
    this->maxfds = NUM_FDS;
}
PollEvent::~PollEvent(){
    free(this->events);
}

void PollEvent::_close(int fd){
    jump(fd)->fd*=-1;
}

pollfd* PollEvent::jump(int fd){
    if(fd==0)
        return this->events;
    return (this->events+fd);
}

void PollEvent::add(int fd_new){
    if(++this->numfds==maxfds){
        makeSpace();
    }
    
    this->jump(numfds-1)->fd = fd_new;
    this->jump(numfds-1)->events = POLLIN;
    this->jump(numfds-1)->revents = 0;

}

void PollEvent::makeSpace(){
    this->events = (pollfd*)realloc(this->events, (maxfds + NUM_FDS) * sizeof (struct pollfd));
    maxfds+=NUM_FDS;
}

int PollEvent::getNumfds(){
    return numfds;
}

void PollEvent::_poll(){

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);

    char buf[4096];

    nfds_t nfds = this->numfds;

    while(true){//check if close app?
    nfds = this->numfds;
    if(poll(this->jump(0), nfds, -1)==-1)
        cerr<<"err poll";
    for(int fd = 0; fd<(nfds+1); fd++){
        
        if(this->jump(fd)->fd <=0)
            continue;
        if((this->jump(fd)->revents)&POLLIN ==POLLIN){
            if(this->jump(fd)->fd == this->listener){
                int fd_new;
                if((fd_new = accept(this->listener, (sockaddr*)&client, &clientSize))==-1)
                    cerr<<"error accept";
                this->add(fd_new);
            }       
            else{
                memset(buf, 0, 4096);
                ssize_t read = recv(this->jump(fd)->fd, &buf, sizeof(buf),0);
                if(read == -1)
                    cerr<<"error recv";
                else if(read==0){
                    //closed con
                    if(close(this->jump(fd)->fd)==-1)
                        cerr<<"err close";
                    this->_close(fd);                    
                }
                else{
                    cout<<buf<<endl;
                }
            }

        }
    }
    }
    //for accept
    



}