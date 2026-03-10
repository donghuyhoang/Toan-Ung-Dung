// Bai 6 : Mat do snt va sang nguyen to
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
const int N = 50000; // sang gioi han 50000
vector<int> snt(N + 1,0);

void sang_nt(){
    for (int i = 2; i * i <= N; i++){
        if(!snt[i]){
            for (int j = i * i; j <= N; j += i) snt[j] = 1;
        }
    }
}

int main() {
    cout << "Nhap n:";
    int n; cin >> n;
    cout << "Mat do so nguyen to xap xi: " << n / log(n) << endl;
    sang_nt();
    cout << "Cac so nguyen to: ";
    for (int i = 2; i <= n; i++){
        if(!snt[i]) cout << i << ' ';
    }
}