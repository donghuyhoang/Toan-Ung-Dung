// Bai 4 x ^ n % M voi O(logn)
#include <iostream>
#include <math.h>
using namespace std;

long long modpow(long long x,long long n, long long m){
    if(!n) return 1 % m;
    long long u = modpow(x,n/2,m);
    u = (u * u) % m;
    if(n & 1) u = (u * x) % m;
    return u;
}

int main(){
    long long x,n,m;
    cout << "Nhap x n m: "; cin >> x >> n >> m;
    cout << modpow(x,n,m);
    
}   