// Bai 2 : So luong uoc so dung cong thuc
#include <iostream>
#include <math.h>
using namespace std;

void uoc(int n){
    for (int i = 1; i <= sqrt(n); i++){
        if(n % i == 0){
            cout << i << ' ';
            int j = n / i;
            if(j != i) {
                cout << j << ' ';
            }
        }
    }
    cout << endl;
}

int main(){
    cout << "Nhap n: ";
    int n; cin >> n;
    if(n <= 0){
        cout << "Chi chap nhan so duong";
        return 0;
    }
    int m = n;
    int i = 2,cnt = 0,res = 1;
    if(n <= 1) {
        cout << n;
    }
    else {
        while(n > 1){
            cnt = 0;
            while(!(n % i)){
                n /= i;
                ++cnt;
            }
            if(cnt){
                res *= (cnt + 1);
                cout << i << "^" << cnt;
                if(n > 1) cout << " * ";
            }
            ++i;
        }
    }
    cout << endl << "So luong uoc: " << res << endl;
    cout << "Liet ke cac uoc: "; uoc(m); cout << endl;
}