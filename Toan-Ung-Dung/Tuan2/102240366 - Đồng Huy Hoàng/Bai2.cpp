// Bai 2 Totient Function
#include <iostream>
#include <math.h>
using namespace std;

long long gcd(long long a, long long b){
    if(b <= 0) return a;
    return gcd(b, a % b);
}

long long lcm(long long a, long long b){
    return a / gcd(a,b) * b;
}

long long totient(long long n){
    int i = 2,cnt = 0;
    long long res = 1;
    while(n > 1){
        cnt = 0;
        while(n % i == 0){
            n /= i;
            ++cnt;
        }
        if(cnt) {
            long long tmp = 1;
            for (int j = 1; j < cnt; j++){
                tmp *= i;
            }
            tmp *= (i - 1);
            res *= tmp;
        }
        ++i;
    }
    return res;
}

bool is_prime(long long n){
    for (int i = 2; i <= sqrt(n); i++) {
        if(n % i == 0) return false;
    }
    return n > 1;
}

int main(){
    long long n;
    cout << "Nhap n: "; cin >> n;
    cout << "So luong so nguyen to cung nhau voi n la: " << totient(n) << endl;
    cout << "Danh sach la: ";
    for (int i = 1; i < n; i++){
        if(gcd(i,n) == 1) cout << i << ' ';
    }
    cout << endl;
    cout << "Kiem tra so nguyen to bang 2 cach: " << endl;
    cout << "Cach 1: n " << (is_prime(n) ? "la so nguyen to" : "khong la so nguyen to") << endl;
    cout << "Cach 2: n " << (totient(n) == n - 1 ? "la so nguyen to" : "khong la so nguyen to");
}