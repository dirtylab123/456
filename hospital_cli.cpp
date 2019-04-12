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
#define loop(i, a, b) for(i=a; i<b; i++)

int main(int argc, char const *argv[]){
	struct sockaddr_in address;
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
  char buffer[256] = {0};
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

  cout<<"~ Welcome to ISM Health Center ~\n";

	while(true){
    string patient_name, department_to_visit, patient_sex, patient_age, patient_status;
    cout<<"\nPlease enter the following patient details (or) to exit:\n";
    cout<<"\nName: "; getline(cin, patient_name);
    cout<<"\nAge: "; getline(cin, patient_age);
    cout<<"\nSex:"; getline(cin, patient_sex);
    cout<<"\nDepartment to visit: "; getline(cin, department_to_visit);

    string send_data = patient_name + "@" + patient_age +"@" + patient_sex + "@" + department_to_visit;
    send(sock, send_data.data(), send_data.size(), 0);
    int len = recv(sock, buffer, sizeof(buffer), 0);
    patient_status.append(buffer, buffer + len);
    cout<<"Patient Status:"<<patient_status<<endl;
  }
return 0;
}
