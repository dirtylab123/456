//#include <stdio.h>
#include <sys/socket.h>
//#include <stdlib.h>
#include <netinet/in.h>
//#include <string.h>
//#include<math.h>
#include <arpa/inet.h>
//#include<unistd.h>
//#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define PORT 8080

int main(int argc, char const *argv[]){
	//struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
  char buffer[1000] = {0};
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("\n Socket creation error \n");
		return -1;
	}
	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
		printf("\nInvalid address \n");
		return -1;
	}
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		printf("\nConnection Failed \n");
		return -1;
	}
  cout<<"Welcome to Chat Room :\n";
	while(true){
		string chat, chat_line, reply;
    cout<<"\nClient : ";
    while(std::getline(std::cin, chat_line) && !chat_line.empty() ) chat += chat_line + "+" ;
		send(sock, chat.data(), chat.size(), 0);
		int len = recv(sock, buffer, sizeof(buffer), 0);
    reply.append(buffer, buffer + len);
    cout<<"\nBot : ";
    for(int i=0; i<reply.length(); i++){
      if(reply[i] == '+') cout<<endl;
      else cout<<reply[i];
    }
    if(reply == "bye+") break;
  }
return 0;
}
