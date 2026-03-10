// Bai 5 : Kiem tra so hoan hao
#include <iostream>
#include <math.h>
using namespace std;

long long tong_uoc(long long n){
    int res = 1;
    for (int i = 2; i <= sqrt(n); i++){
        if(n % i == 0){
            res += i;
            int j = n / i;
            if(j != i) {
                res += j;
            }
        }
    }
    return res;
}

void dem_shh(long long n){
    int cnt = 0;
    cout << "So hoan hao be hon n: ";
    for (long long i = 6; i < n; i++){
        if(tong_uoc(i) == i) cout << i << ' ';
    }
}

int main(){
    cout << "Nhap n: ";
    long long n; cin >> n;
    if(n <= 0){
        cout << "Chi chap nhan so duong";
        return 0;
    }
    int m = n,so_luong = 1;
    long long i = 2,cnt = 0,res = 1;
    if(n <= 1) {
        cout << n;
    }
    else {
        while(n > 1){
            cnt = 0;
            while(!(n % i)){
                n /= i;
                ++cnt;
            }
            if(cnt){
                long long tmp = 1;
                for (int j = 1; j <= cnt + 1; j++) tmp *= i;
                res *= (tmp - 1) / (i - 1);
            }
            ++i;
        }
    }
    res -= m;
    long long tong_uoc1 = tong_uoc(m);
    cout << "Cach 1 ";
    cout <<(tong_uoc1 == m ? "n la so hoan hao" : "n khong phai la so hoan hao") << endl;
    cout << "Cach 2 ";
    cout << (res == m ? "n la so hoan hao" : "n khong phai la so hoan hao") << endl;
    dem_shh(m);
}