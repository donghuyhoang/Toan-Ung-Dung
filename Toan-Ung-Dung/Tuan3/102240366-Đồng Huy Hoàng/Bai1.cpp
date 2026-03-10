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

bool gcd(int a, int b){
    if(b <= 0) return a;
    return gcd(b,a%b);
}
int tonguoc(int n){
    int res = 1;
    for (int i = 2; i <= sqrt(n); i++){
        if(n % i == 0){
            res += i;
            int j = n / i;
            if(j != i) res += j;
        }
    }
    return res;
}
int main(){
    vector<int> v;
    int n; cin >> n;
    int i = 2,mi = 10000,res = 0;
    while(1){
        if(i == n) {
            ++i;
            continue;
        }
        if(is_prime(i)){
            if(abs(n - i) <= mi){
                res = i;
                mi = abs(n-i);
            }
            if(i > n) break;
        }
        ++i;
    }
    cout << "So nguyen to gan nhat voi n la " << res << endl;
    i = 1;
    while(v.size() <= 9000){
        if(i != n && gcd(i,n) == 1) v.push_back(i);
        ++i;
    }
    cout << "Cac so nguyen to cung nhau theo dieu kien de bai: ";
    for (int i = 0; i < 9000; i++) {
        if(tonguoc(v[i]) == v[i]) cout << v[i] << ' ';
    }
}