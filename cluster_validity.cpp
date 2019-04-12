#include<bits/stdc++.h>
using namespace std;
int main()
{
	int N;
	cin>>N;
	for(int i=1;i<100;i++){
		for(int j=1;j<100;j++){
			if(N==(i*i+i*j+j*j)){
				cout<<"Valid cluster size !!\n";
				return 0;			
			}
		}
	}
	cout<<"Inalid cluster size !!\n";	
 
}
