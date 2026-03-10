// Bai 3 Kiem tra cac phep toan mod
#include <iostream>
#include <math.h>
using namespace std;

long long bipow(long long x,long long n, long long m){
    long long res = 1;
    while(n){
        if(n & 1){
            res = ((res % m) * (x % m)) % m;
        }
        x = ((x % m) * (x % m)) % m;
        n >>= 1;
    }
    return res;
}

int main(){
    long long x,y,n,m;
    cout << "Nhap x y m: "; cin >> x >> y >> m;
    cout << "Dap an (x + y) mod m = " << (x + y) % m << endl;
    cout << "Dap an (x mod m + y mod m) mod m = " << ((x % m + y % m) % m) << endl;
    cout << "Dap an (x - y) mod m = " << (x - y + m) % m << endl;
    cout << "Dap an (x mod m - y mod m) mod m = " << (((x % m) - (y % m) + m) % m) << endl;
    cout << "Dap an (x * y) mod m = " << (x * y) % m << endl;
    cout << "Dap an (x mod m * y mod m) mod m = " << ((x % m * y % m) % m) << endl;
    cout << "Nhap x n m: "; cin >> x >> n >> m;
    cout << "Dap an x^n mod m = " << bipow(x,n,m) << endl;
    long long res = 1;
    for (int i = 1; i <= n; i++){
        res = ((res % m) * (x % m)) % m;
    }
    cout << "Dap an (x mod m)^n mod m = " << res;
}   