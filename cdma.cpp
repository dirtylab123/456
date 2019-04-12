#include<bits/stdc++.h>
#include<math.h>
using namespace std;
#define ll long long
#define loop(i, a, b) for(i=a; i<b; i++)
#define rloop(i, a, b) for(i=a; i>b; i++)
void cdma(){
ll d[4], i, j, c;
cout<<"\n Enter 4 data points: ";
cin>>d[0]>>d[1]>>d[2]>>d[3];
ll n = 4, w[][4]={ {1,1,1,1},
{1,-1,1,-1},
{1,1,-1,-1},
{1,-1,-1,1} },f[n];
cout<<"\n Chips for each cahnnel are: "<<endl;
loop(j, 1, n + 1){
cout<<" C"<<j<<": [";
loop(i, 0, n - 1)
cout<<w[j-1][i]<<", ";
cout<<w[j-1][n-1]<<"]"<<endl;
}
loop(i, 0, n){
c = 0;
loop(j, 0, n){
c += (w[j][i] * d[j]);
}
f[i] = c;
}
cout<<"\n Data Sent: [";
loop(i, 0, n - 1) cout<<f[i]<<", ";
cout<<f[n-1]<<"]"<<endl;loop(i, 0, n){
c = 0;
loop(j, 0, n)
c += (w[i][j] * f[j]) ;
cout<<"\n Bit Sent By "<<i<<" = "<<c / n;
}
cout<<endl;
}
int main(int argc, char const *argv[]) {
cdma();
return 0;
}
