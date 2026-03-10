#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

bool is_prime(int n){
    for (int i = 2; i <= sqrt(n); i++){
        if(n % i == 0) return false;
    }
    return n > 1;
}
int main(){
    int n,m;
    cout << "So luong cac so nguyen to nam trong n m (khong tinh n m)" << endl;
    cout << "Nhap n m: " << endl; cin >> n >> m;
    int mi = 1000,res = 0,cnt = 0;
    for (int i = n + 1; i < m; i++){
        if(is_prime(i)) {
            ++cnt;
            if(abs(i - 636) <= mi) {
                res = i;
                mi = abs(i-636);
            }
        }
    }
    cout << "So luong so nguyen to trong khoang n m: " << cnt << endl;
    cout << "So nguyen to gan 636 nhat: " << res;
}