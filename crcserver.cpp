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
string Xor(string a, string b){
string res;
for(int i=0; i<b.length(); i++){
if(a[i] == b[i]) res += "0";
else res += "1";
}
return res;
}
string DecToBin(long long dec){string res ;
while(dec > 0){
res = to_string(dec%2) + res;
dec = dec/2;
}
return res;
}
long long BinToDec(string bin){
long long dec = 0;
for(int i=0;i<bin.length(); i++){
dec += pow(2, bin.length() - 1 - i)*(bin[i] - '0');
}
return dec;
}
long long crc(string divident, string divisor){
int len = divisor.length();
string tmp_res = divident.substr(0, len);
while(len < divident.length()){
if(tmp_res[0] == '1'){
tmp_res = Xor(divisor, tmp_res).substr(1,3) + divident[len];
}
else{
string tmp;
for(int i=0; i< len; i++) tmp += '0';
tmp_res = Xor(tmp, tmp_res).substr(1, 3) + divident[len];
}
len++;
}
if(tmp_res[0] == '1'){
tmp_res = Xor(divisor, tmp_res);
}
else{
string tmp;
for(int i=0; i< len; i++) tmp += '0';
tmp_res = Xor(tmp, tmp_res).substr(1, 3) + divident[len];
}
return BinToDec(tmp_res);
}
int main(int argc, char const *argv[]){
int server_fd, new_socket, valread;
struct sockaddr_in address;int opt = 1;
int addrlen = sizeof(address);
char bufer[2256] = {0};
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
perror("socket failed");
exit(EXIT_FAILURE);
}
if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR |
SO_REUSEPORT,&opt, sizeof(opt))){
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
if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
(socklen_t*)&addrlen))<0){
perror("accept");
exit(EXIT_FAILURE);
}
while(true){
long long cwd, ky;
valread = read(new_socket, &cwd, sizeof(long long));
valread = read(new_socket, &ky, sizeof(long long));
if(cwd == 0 || ky == 0) break;
string codeword = DecToBin(cwd);
string key = DecToBin(ky);
string res;
crc(codeword, key) == 0 ? res = "good data" : res = "bad data";send(new_socket, res.data(), res.size(), 0);
}
return 0;
}
