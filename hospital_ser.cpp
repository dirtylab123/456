#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include<math.h>
#include <arpa/inet.h>
#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define PORT 8080
#define loop(i, a, b) for(i=a; i<b; i++)

typedef struct Doctor{
  string name;
  bool avialable;
}doc;

typedef struct Department{
  string name;
  doc doctor[2];
}dept;

typedef struct Patient{
  string name;
  string age;
  string sex;
  string department_to_visit;
}pat;
dept departments[2];

void init_db(){
  departments[0].name = "ENT";
  departments[0].doctor[0].name = "Dr. Khana";
  departments[0].doctor[0].avialable = true;
  departments[0].doctor[1].name = "Dr. Sharma";
  departments[0].doctor[1].avialable = true;

  departments[1].name = "A&E";
  departments[1].doctor[0].name = "Dr. Kumar";
  departments[1].doctor[0].avialable = true;
  departments[1].doctor[1].name = "Dr. Singh";
  departments[1].doctor[1].avialable = true;
}

int main(int argc, char const *argv[]){
  queue<pat> waiting_queue;
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
  char buffer[512] = {0};

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
  init_db();
  int i, j;
 	while(true){
    vector<string> p_data;
    int tag = 1;
    string status;
    int len = recv(new_socket, buffer, sizeof(buffer), 0);
    char delim[] = "@";
    char *token = strtok(buffer, delim);
    while(token) {
    	p_data.push_back(token);
    	token = strtok(NULL, delim);
    }
    len = p_data.size();
    bool flag = false;
    for(int k=0; k<len; k++){
      if(p_data[k] == "0"){
        flag = true;
        break;
      }
    }
    if(flag) break;
    for(i=0; i<512; i++) buffer[i] = '\0';
    pat patient;
    patient.name = p_data[0];  patient.age = p_data[1];
    patient.sex = p_data[2];  patient.department_to_visit = p_data[3];
    p_data.clear();
    waiting_queue.push(patient);
      if(waiting_queue.size() > 3){
        init_db();
      }
      pat patient_new = waiting_queue.front();
      waiting_queue.pop();
      for(i=0; i<2; i++){
        if(departments[i].name == patient_new.department_to_visit) break;
      }
      if(i==2){
        status = "This Department doesn't exits";
      }
      else{
        for(j=0; j<2; j++){
          if(departments[i].doctor[j].avialable){
            departments[i].doctor[j].avialable = false;
            break;
          }
        }
        if(j==2){
          status = "Doctors are busy please wait for some time";
          tag = 0;
        }
        else{
          status = departments[i].doctor[j].name + " is assinged to " + patient_new.name;
        }
      }
      if(tag==0){
        waiting_queue.push(patient_new);
      }
      send(new_socket, status.data(), status.size(), 0);
  }
  return 0;
}
