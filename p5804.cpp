#include <bits/stdc++.h>
using namespace std;
int n;
long long int a[1001],b[1001],am,bm,ava,avb;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		ava+=a[i];
	}
	ava=ava/n;
	for(int i=1;i<=n;i++){
		cin>>b[i];
		avb+=b[i];
	}
	
	avb=avb/n;
	am=a[1];
	bm=b[1];
	cout<<ava<<" "<<avb<<endl;
	for(int i=1;i<=n;i++){
		if((a[i]-ava)*(a[i]-ava)>(am-ava)*(am-ava)){
			am=a[i];
		}
		if((b[i]-avb)*(b[i]-avb)<(bm-avb)*(bm-avb)){
			bm=b[i];
		}
	}
	cout<<am<<" "<<bm<<endl;
	if(am>=bm){
		cout<<am-bm;
	}else{
		cout<<bm-am;
	}
	return 0;
} 
