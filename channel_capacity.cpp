#include<bits/stdc++.h>
using namespace std;
int main()
{
int i,j,N,M,c;
cout<<"Enter i and j: ";
cin>>i>>j;
cout<<"Enter number of clusters: ";
cin>>M;
cout<<"Enter channels per cell: ";
cin>>c;
N=i*i +i*j +j*j;
cout<<N*M*c<<endl;
return 0;
}
 
