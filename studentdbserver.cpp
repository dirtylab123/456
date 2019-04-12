
// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <bits/stdc++.h>
#define PORT 8080
using namespace std;
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    string hello = "Hello from server";
       
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
	int num;

	map<string,string> m;
	m["15je001083"] = "Anushka";
	m["15je001133"] = "Mohak";
	m["15je001142"] = "Barasha";
	m["15je001143"] = "Anupam";
	m["15je001145"] = "Aayush";
	string query,ans;
 
	

	while(1){
		valread = read( new_socket , &num , sizeof(int));
		printf("Received : %d\n",num);
		valread = read(new_socket , buffer , 1024);
		query = "";
		for(int i=0;i<num;i++) query+=buffer[i];
		cout<<query<<endl;		
		if(buffer[0]=='e') break;
		else{
			ans = m[query];
			cout<<ans<<endl;
    		//send(new_socket , &ans , sizeof(ans) , 0 );
		}
		
		query = ans;
		num = query.length();
		for(int i=0;i<num;i++) buffer[i]=query[i];
		send(new_socket , &num , sizeof(int) , 0 );
		send(new_socket , buffer , 1024 , 0 );
		

	}


    return 0;
}

