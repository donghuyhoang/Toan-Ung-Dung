#include <iostream>
#include <cmath>
#include <climits>

using namespace std;

bool is_prime(int n){
    if(n < 2) return false;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

int main(){
    int n,m;

    cout << "Nhap n m: ";
    cin >> n >> m;

    if(n >= m){
        cout << "Khoang khong hop le";
        return 0;
    }

    int mi = INT_MAX;
    int res = 0;
    int cnt = 0;

    for(int i = n + 1; i < m; i++){
        if(is_prime(i)){
            cnt++;

            if(abs(i - 636) < mi){
                res = i;
                mi = abs(i - 636);
            }
        }
    }

    cout << "So luong so nguyen to: " << cnt << endl;

    if(cnt > 0)
        cout << "So nguyen to gan 636 nhat: " << res;
    else
        cout << "Khong co so nguyen to trong khoang";
}
