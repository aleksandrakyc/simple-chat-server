#include <iostream>
#include <string>
#include "pch.h"

using namespace std;

int main()
{   
    //create socket
    SmartSocket listener(54000);
    listener.init();

    cout << "listening" << endl;

    PollEvent pollev(listener.getFd());
    pollev._poll();
    
    return 0;
}