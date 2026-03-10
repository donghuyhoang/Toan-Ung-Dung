// Bai 5 Kiem tra tinh dung dan x^(m-1) % m = 1 voi m la nguyen to va x va m la nguyen to cung nhau
#include <iostream>
#include <math.h>
using namespace std;

long long gcd(long long a, long long b){
    if(b <= 0) return a;
    return gcd(b, a % b);
}

long long modpow(long long x,long long n, long long m){
    if(!n) return 1 % m;
    long long u = modpow(x,n/2,m);
    u = (u * u) % m;
    if(n & 1) u = (u * x) % m;
    return u;
}

bool is_prime(long long n){
    for (int i = 2; i <= sqrt(n); i++){
        if(n % i == 0) return false;
    }
    return n > 1;
}

int main(){
    long long x,m;
    cout << "Kiem tra tinh dung dan cua x^(m-1) % m = 1" << endl;
    cout << "Nhap x m: "; cin >> x >> m;
    if(gcd(x,m) != 1 || !is_prime(m)){
        cout << "Sai dau vao";
    }
    else{
        cout << "Dap an x^(m-1) % m = " << modpow(x,m-1,m);
    }
}   