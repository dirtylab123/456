#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<math.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define PORT 8080

int main(int argc, char const *argv[]){
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
  char buffer[1000] = {0};

	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&opt, sizeof(opt))){
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0){
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0){
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
		perror("accept");
		exit(EXIT_FAILURE);
	}
  cout<<"Welcome to Chat Room :\n";

	while(true){
    string chat, reply, reply_line;
    int len = recv(new_socket, buffer, sizeof(buffer), 0);
    chat.append(buffer, buffer + len);
    cout<<"\nClient : ";
    for(int i=0; i<chat.size(); i++){
      if(chat[i] == '+') cout<<"\n";
      else cout<<chat[i];
    }
    cout<<"\nBot : ";
    while(getline(cin, reply_line) && !reply_line.empty()) reply += reply_line + "+";
    send(new_socket, reply.data(), reply.size(), 0);
    if(chat == "bye+") break;
  }
return 0;
}
