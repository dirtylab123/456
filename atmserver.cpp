
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










	int num,flag,balance;

	map<string,string> m;
	m["1500001083"] = "1234";
	m["1500001133"] = "9876";
	m["1500001142"] = "6666";
	m["1500001143"] = "5555";
	m["1500001145"] = "4444";

	map<string,int> amount;
	amount["1500001083"] = 1234;
	amount["1500001133"] = 9876;
	amount["1500001142"] = 6666;
	amount["1500001143"] = 5555;
	amount["1500001145"] = 4444;
	string query,ans,pin,accountNumber;
 
	

	while(1){
		valread = read( new_socket , &num , sizeof(int));
		valread = read(new_socket , buffer , 1024);
		query = "";
		for(int i=0;i<num;i++) query+=buffer[i];
		cout<<query<<endl;
		accountNumber = query;

		valread = read( new_socket , &num , sizeof(int));
		valread = read(new_socket , buffer , 1024);
		pin = "";
		for(int i=0;i<num;i++) pin+=buffer[i];
		cout<<pin<<endl;


		if(m[query]==""){
			ans = "Account Number Invalid";
			query = ans;
			num = query.length();
			flag = 0;
			for(int i=0;i<num;i++) buffer[i]=query[i];
			send(new_socket , &flag , sizeof(int) , 0 );
			send(new_socket , &num , sizeof(int) , 0 );
			send(new_socket , buffer , 1024 , 0 );
		}
		else if(m[query]==pin){
			ans = "Successfully Verified";
			query = ans;
			num = query.length();
			flag = 1;
			for(int i=0;i<num;i++) buffer[i]=query[i];
			send(new_socket , &flag , sizeof(int) , 0 );
			send(new_socket , &num , sizeof(int) , 0 );
			send(new_socket , buffer , 1024 , 0 );

			valread = read( new_socket , &balance , sizeof(int));
			if(amount[accountNumber] >= balance){
				ans = "Successfully Withdrawn";
				query = ans;
				num = query.length();
				flag = 11;
				for(int i=0;i<num;i++) buffer[i]=query[i];
				send(new_socket , &flag , sizeof(int) , 0 );
				send(new_socket , &num , sizeof(int) , 0 );
				send(new_socket , buffer , 1024 , 0 );
			}
			else{
				ans = "Insufficient Balance";
				query = ans;
				num = query.length();
				flag = 10;
				for(int i=0;i<num;i++) buffer[i]=query[i];
				send(new_socket , &flag , sizeof(int) , 0 );
				send(new_socket , &num , sizeof(int) , 0 );
				send(new_socket , buffer , 1024 , 0 );
			}
		}
		else if(m[query]!=pin){
			ans = "Incorrect Pin";
			query = ans;
			num = query.length();
			flag = 2;
			for(int i=0;i<num;i++) buffer[i]=query[i];
			send(new_socket , &flag , sizeof(int) , 0 );
			send(new_socket , &num , sizeof(int) , 0 );
			send(new_socket , buffer , 1024 , 0 );
		}
		else if(buffer[0]=='e') break;
		else{
			ans = m[query];
			cout<<ans<<endl;
			query = ans;
			num = query.length();
			for(int i=0;i<num;i++) buffer[i]=query[i];
			send(new_socket , &num , sizeof(int) , 0 );
			send(new_socket , buffer , 1024 , 0 );
    		//send(new_socket , &ans , sizeof(ans) , 0 );
		}
		
		
		

	}


    return 0;
}

