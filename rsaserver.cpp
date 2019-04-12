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
#define PORT  8080
#define loop(i, a, b) for(i=a; i<b; i++)
int solve_ext_gcd(int a,int b, int &x,int &y){ // Extended GCD
if(a==0){
x=0; y=1;
return b;
}
int x1,y1;
int g = solve_ext_gcd(b%a,a,x1,y1);
x=y1-(b/a)*x1;
y=x1;
return g;
}
int solve_modulo_multi_inverse(int a, int m){
int x, y;
int g = solve_ext_gcd(a, m, x, y);
if (g != 1) {
cout <<"Inverse doesn't exist"; return -1;
}
else{
int res=(x%m+m)%m;
return res;
}
}
int solve_fast_modulo_exponent(int x, int y, int n){
int res = 1; x = x%n;
while(y>0){
if(y&1) res = (res*x)%n;y >>= 1;
x = (x*x)%n;
}
return res;
}
void init_rsa(int *public_key, int *private_key, int *n){
int p = 73, q = 227;
int phi_n = (p - 1) * (q - 1);
*public_key = 25;
*n = p*q;
*private_key = solve_modulo_multi_inverse(*public_key, phi_n);
}
int main(int argc, char const *argv[]){
int server_fd, new_socket, valread;
struct sockaddr_in address;
int opt = 1;
int addrlen = sizeof(address);
char buffer[256] = {0};
map<string, string> mp;
mp["alokpatra199s@gmail.com"] = "patra_style";
if ((server_fd = socket(AF_INET , SOCK_STREAM, 0)) == 0){
perror("socket failed");
exit(EXIT_FAILURE);
}
if (setsockopt(server_fd, SOL_SOCKET , SO_REUSEADDR |
SO_REUSEPORT ,&opt, sizeof(opt))){
perror("setsockopt");
exit(EXIT_FAILURE);
}
address.sin_family = AF_INET ;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons( PORT  );
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
int public_key, private_key, n, i;
init_rsa(&public_key, &private_key, &n);while(true){
string username, decrypted_password, status;
vector<int> password;
int len = recv(new_socket, buffer, sizeof(buffer), 0);
username.append(buffer, buffer + len);
len = recv(new_socket, buffer, sizeof(buffer), 0);
char delim[] = "*";
char *token = strtok(buffer, delim);
while(token) {
password.push_back(stoi(token));
token = strtok(NULL, delim);
}
if(mp.find(username) == mp.end()){
status = "Incorrect Username";
}
else{
loop(i, 0, password.size()){
decrypted_password +=
(char)solve_fast_modulo_exponent(password[i],
private_key, n);
}
if(decrypted_password == mp[username]){
status = "Success";
}
else{
status = "Incorrect Password";
}
}
send(new_socket, status.data(), status.size(), 0);
}
return 0;
}
