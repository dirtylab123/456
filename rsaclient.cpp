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
int solve_ext_gcd(int a,int b, int &x,int &y){
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
if(y&1) res = (res*x)%n;
y >>= 1;
x = (x*x)%n;}
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
struct sockaddr_in address;
int sock = 0, valread;
struct sockaddr_in serv_addr;
char buffer[256] = {0};
if((sock = socket(AF_INET , SOCK_STREAM, 0)) < 0){
printf("\n Socket creation error \n");
return -1;
}
memset(&serv_addr, '0', sizeof(serv_addr));
serv_addr.sin_family = AF_INET ;
serv_addr.sin_port = htons(PORT );
if(inet_pton(AF_INET , "127.0.0.1", &serv_addr.sin_addr)<=0){
printf("\nInvalid address \n");
return -1;
}
if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
printf("\nConnection Failed \n");
return -1;
}
cout<<"Welcome to Authentication Services : \n";
int public_key, private_key, n, i;
init_rsa(&public_key, &private_key, &n);
while(true){
string username, password, encrypted_password, status;
cout<<"\n username : "; getline(cin, username);
cout<<" password : "; getline(cin, password);
loop(i, 0, password.length()-1){
encrypted_password +=
to_string(solve_fast_modulo_exponent(password[i],
public_key, n)) + "*";
}
encrypted_password +=
to_string(solve_fast_modulo_exponent(password[password.length()-1],
public_key, n));
send(sock, username.data(), username.size(), 0);
send(sock, encrypted_password.data(), encrypted_password.size(), 0);int len = recv(sock, buffer, sizeof(buffer), 0);
status.append(buffer, buffer + len);
cout<<" status : "<<status<<endl;
}
return 0;
}
