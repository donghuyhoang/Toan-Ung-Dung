#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int extEuclid(int a, int b, int& x, int& y){
    if (b == 0){
        x = 1;
        y = 0;
        return a;
    }
    int q = a / b;
    int r = a - b * q;
    int x1 = 0, y1 = 0;
    int d = extEuclid(b, r, x1, y1);
    x = y1;
    y = x1 - q * y1;
    return d;
}

int modInv(int a, int m){
    int x, y;
    int d = extEuclid(a, m, x, y); 
    if (d != 1) return -1; 
    x = (x % m + m) % m;
    return x; 
}

int main(){
    int n; 
    long long M = 1;
    cout << "Nhap so luong n: "; cin >> n;
    cout << endl;
    cout << "Nhap a b theo cau truc x = a mod m" << endl;
    vector<long long> a(n + 1),m(n + 1);
    for (int i = 1; i <= n; i++){
        cin >> a[i] >> m[i];
        M *= m[i];
    }
    long long x = 0;
    for (int i = 1; i <= n; i++){
        x += a[i] * (M / m[i]) * modInv(M / m[i],m[i]);
    }
    cout << "x = " << (x % M) << " + k*" << M;
} 