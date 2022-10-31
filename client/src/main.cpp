#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

//there should be like, a smart class hierarchy to this. good god.
int getInput(string& input){
    cout<<"> ";
    getline(cin, input);

    if(input=="0"){
        return 0;
    }

    return 1;
}

int main()
{
    //create a socket
    int sock = socket(AF_INET, SOCK_STREAM,0);
    if(sock==-1){
        cerr<<"cant create socket";
        return -1;
    }
    //create a hint structure
    int port = 54000;
    string ipaddress = "127.0.0.1"; //up to change

    //this structure signifies ipv4
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipaddress.c_str(), &hint.sin_addr);

    //connect with server
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if(connectRes == -1){
        return -2;
    }

    char buf[4096];
    string userInput;

    cout<<"type 0 to disconnect"<<endl;

    //while loop
    do{
    //  enter lines
        
        if(getInput(userInput)==0){
            cout<<"disconnecting"<<endl;
            break;
        }
    //  send to server
        int sendRec = send(sock, userInput.c_str(), userInput.size()+1, 0);

        //check if fail
        if(sendRec==-1){
            cout << "couldnt send";
            continue;
        }
    
    //  wait for response
        memset(buf, 0, 4096);
        //int bytesRec = recv(sock, buf, 4096, 0);

    //  display
        //cout<< "SERVER "<< string(buf, bytesRec)<<"\r\n";
    }while(true);
    //close
    close(sock);
    return 0;
}

