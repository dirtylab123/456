#include<bits/stdc++.h>
using namespace std;

int main(){

	float n, SIR_db, i0;
	float N;
	
	cin>>n>>SIR_db>>i0;
	float sir = SIR_db/10.0;
	cout<<sir<<endl;
	float SIR = pow(10, sir);
	float N_ = SIR*i0/(pow(3, n/2));
	N = pow(N_, 2/n);
	cout<<N<<endl;
	//cout<<"the cluser size must be greater than: "<<ceil(N)<<endl;
	for(int k=ceil(N); k<9999; k++){
		int i, j;
		int count = 0;
		for(i=1; i*i<=k; i++){
			for(j=1; j*j<=k; j++){
				if(i*i + i*j + j*j == k){
					count++;
					cout<<i<<" "<<j<<endl;
					break;
				}
			}
			if(count>0) break;
		}
		if(count == 1) {
			cout<<"cluster size for max capacity: "<<k<<endl;
			break;
		}
	}
	
	return 0; 

}







