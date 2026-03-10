// Bai 1 : Phan tich thua so nguyen to
#include <iostream>
using namespace std;

int main(){
    cout << "Nhap n: ";
    int n; cin >> n;
    int i = 2,cnt = 0;
    if(n <= 1) return cout << "Chi chap nhan so duong",0;
    while(n > 1){
        cnt = 0;
        while(!(n % i)){
            n /= i;
            ++cnt;
        }
        if(cnt){
            cout << i << "^" << cnt;
            if(n > 1) cout << " * ";
        }
        ++i;
    }
}
