//1.
#include<bits/stdc++.h>
using namespace std;
int main()
{
	double si,io,n,freqreuse,N;
	cout<<"Enter Signal to Interderence Ratio: ";
	cin>>si;
	cout<<"Enter Io: ";
	cin>>io;
	cout<<"Enter Path Loss factor : ";
	cin>>n;
	N = pow(si*io,2/n)/3;
	cout<<N<<" "<<1/N<<endl;

}


