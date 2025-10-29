#include <bits/stdc++.h>
using namespace std;

int n,co=0;
bool x[1001];
char db[10],num[1001][9];
int main(){
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    for(int i=1;i<=9;i++){
        cin>>db[i];
    }
    cin>>n;
    for(int i=1;i<=n;i++){
        x[i]=true;
        for(int j=1;j<=9;j++){
            cin>>num[i][j];
            if(num[i][j]==db[j]||db[j]=='*'){
                continue;
            }else{
                x[i]=false;
            }
        }
        if(x[i]==true){
            co++;
        }
    }
    cout<<co<<endl;
    for(int i=1;i<=n;i++){
        if(x[i]==true){
            for(int j=1;j<=9;j++){
                cout<<num[i][j];
            }
            cout<<endl;
        }
    }
    return 0;
}