#include "pch.h"

using namespace std;

SmartSocket::SmartSocket(int portnum){
    this->hint.sin_family = AF_INET;
    this->hint.sin_port = htons(portnum);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr); //not 100% sure what this does
}

void SmartSocket::init(){
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if(this->fd<0){
        cerr<<"cant create socket";
        return;
    }
    if(bind(this->fd, (const sockaddr*)&this->hint, sizeof(this->hint))==-1){
        cerr<<"cant bind";
        return;
    }
    if(listen(this->fd, BACKLOG)==-1){
        cerr<<"cant listen";
        return;
    }

}

int SmartSocket::getFd(){
    return this->fd;
}