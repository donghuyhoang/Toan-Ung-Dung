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

bool is_pf(int n){
    int res = 1;
    for (int i = 2; i <= sqrt(n); i++){
        if(n % i == 0){
            res += i;
            int j = n / i;
            if(i != j) res += j;
        }
    }
    return res == n;
}

void uoc(int n){
    int cnt_uoc = 0,cnt_prime = 0,tong = 0;
    vector<int> v;
    for (int i = 1; i <= sqrt(n); i++){
        if(n % i == 0){
            cnt_uoc++;
            int j = n / i;
            if(is_prime(i)) v.push_back(i);
            if(i != j) {
                ++cnt_uoc;
                if(is_prime(j)) v.push_back(j);
            }
        }
    }
    cout << "So luong uoc cua n: " << cnt_uoc << " trong do co " << v.size() << " so nguyen to: ";
    for (int i = 0; i < v.size(); i++){
        tong += v[i];
        cout << v[i] << ' ';
    }
    cout << "Tong cac so la: " << tong << endl;
}

int main(){
    int n; cin >> n;
    uoc(n);
    cout << "Cac so nguyen to cung nhau voi n la: ";
    long long tong = 0;
    for (int i = 1; i < n; i++){
        if(gcd(i,n) == 1) {
            cout << i << ' ',tong += i;
        }
    }
    cout << endl << "Tong cac so la " << tong << endl;
    cout << "Cac so hoan hao tu 1 den n: ";
    for (int i = 2; i <= n; i++){
        if(is_pf(i)) cout << i << ' ';
    }
    cout << endl;
    cout << "So nguyen to gan nhat voi n + 1 la: ";
    int i = 2,res = 0,mi = 10000;
    ++n;
    while(1){
        if(i == n){
            ++i;
            continue;
        }
        if(is_prime(i)){
            if(abs(n - i) <= mi){
                mi = abs(n - i);
                res = i;
            }
            if(i > n) break;
        }
        ++i;
    }
    cout << res;
}