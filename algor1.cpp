#include <iostream>
#include <vector>
using namespace std;
// int a;
// int sum;
// int main(){
//     cin>>a;
//     for(int i=1;i<=a;i++){
//         if(a%i==0){
//             sum += i;
//         }
//     }
//     if(sum>a){
//         cout<<"is abuntant";
//     }else{
//         cout<<"not abundant";
//     }
//     return 0;
// }



int index(int x, const vector<int>& L, int position = 0) {
    if (position >= L.size()) {
        return -1; // 
    }
    if (L[position] == x) {
        return position; 
    }
    return index(x, L, position + 1);
}
int main() {
    vector<int> L = {10, 20, 30, 40, 50};
    int x = 30;
    
    int pos = index(x, L);
    if (pos != -1) {
        cout << "Element " << x << " found at position: " << pos <<endl;
    } else {
        cout << "Element " << x << " not found in the list." << endl;
    }

    return 0;
}
