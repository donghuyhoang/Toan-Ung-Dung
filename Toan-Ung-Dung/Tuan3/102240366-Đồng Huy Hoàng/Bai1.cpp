#include <iostream>
#include <cmath>
#include <vector>
#include <climits>

using namespace std;

bool is_prime(int n){
    if(n < 2) return false;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0) return false;
    }
    return true;
}

int gcd(int a, int b){
    while(b != 0){
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int tonguoc(int n){
    if(n == 1) return 0;

    int res = 1;
    for(int i = 2; i * i <= n; i++){
        if(n % i == 0){
            res += i;
            int j = n / i;
            if(j != i) res += j;
        }
    }
    return res;
}

int main(){

    int n;
    cin >> n;

    // tìm số nguyên tố gần n nhất
    int res = -1;
    int mi = INT_MAX;

    for(int i = 2; i <= 2*n; i++){
        if(i == n) continue;

        if(is_prime(i)){
            int d = abs(n - i);
            if(d < mi){
                mi = d;
                res = i;
            }
        }
    }

    cout << "So nguyen to gan nhat voi n la: " << res << endl;

    // tìm 9000 số nguyên dương nguyên tố cùng nhau với n
    vector<int> v;
    int i = 1;

    while(v.size() < 9000){
        if(i != n && gcd(i, n) == 1){
            v.push_back(i);
        }
        i++;
    }

    cout << "Cac so hoan hao trong danh sach: ";

    for(int i = 0; i < 9000; i++){
        if(tonguoc(v[i]) == v[i]){
            cout << v[i] << " ";
        }
    }

}
