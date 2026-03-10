#include <iostream>
using namespace std;

long long gcd(long long a, long long b){
    if(b <= 0) return a;
    return gcd(b, a % b);
}

long long lcm(long long a, long long b){
    return a / gcd(a,b) * b;
}

int main(){
    long long a,b; cin >> a >> b;
    cout << "Tinh uoc chung lon nhat va boi chung nho nhat" << endl;
    cout << "Nhap a: "; cin >> a;
    cout << "Nhap b: "; cin >> b;
    cout << "Uoc chung lon nhat " << gcd(a,b) << endl;
    cout << "Boi chung nho nhat " << lcm(a,b) << endl;
}