#include <bits/stdc++.h>
using namespace std;
int st[26],shul,save[26],ans[26];
int v,g,vt[26],c[16][26];
int p=26;
bool check(int x){
    for(int i=1;i<=v;i++){
        int sum=0;
        for(int j=1;j<=x;j++){
            sum+=c[save[j]][i];
        }
        if(sum<vt[i]){
            return false;
        }
    }
    return true;
}

void match(int t,int s){
    if(t>g){
        if(check(s)){
            if(s<=p){
                p=s;
                for(int i=1;i<=p;i++){
                    ans[i]=save[i];
                }
            }
        }
        return;
    }
    save[s+1]=t;
    match(t+1,s+1);//xuan
    save[s+1]=0;
    match(t+1,s);//buxuan
}

int main(){
    cin>>v;
    for(int i=1;i<=v;i++){
        cin>>vt[i];
    }
    cin>>g;
    for(int j=1;j<=g;j++){
        for(int i=1;i<=v;i++){
            cin>>c[j][i];
        }
    }
    match(1,0);
    cout<<p;
    for(int i=1;i<=p;i++){
        cout<<" "<<ans[i];
    }
    return 0;
}