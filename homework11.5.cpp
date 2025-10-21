#include <bits/stdc++.h>
using namespace std;

vector<int> cut(const vector<int>& L, int i, int j, int current = 1) {
    if (current > L.size()) {
        return {};
    }
    if (current >= i && current <= j) {
        return cut(L, i, j, current + 1); 
    }
    vector<int> rest = cut(L, i, j, current + 1);
    rest.insert(rest.begin(), L[current - 1]); 
    return rest;
}

int main() {
    int n, i, j;
    cin >> n;
    vector<int> L(n);
    cout << n <<endl;
    for (int& x : L) {
        cin >> x;
    }
    cin >> i >> j;
    vector<int> result = cut(L, i, j);
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}







int main(){
	int n,a[10001],x;
	cin>>n; 
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	cin>>x;
	int t=n
	for(int i=1;i<=n/2;i++){
		for(int j=start;j<=end;j++){
			
		}
		
		
	
	}
	return o;
} 
