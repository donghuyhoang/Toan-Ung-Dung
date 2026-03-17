#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}
void inSoHoanHao(long long N) {
    cout << "Cac so hoan hao khong vuot qua " << N << " la: ";
    bool found = false;
    
    // Sử dụng định lý Euclid-Euler để sinh số hoàn hảo
    for (long long p = 2; ; ++p) {
        if (isPrime(p)) {
            long long mersenne = (1LL << p) - 1; // Tính 2^p - 1
          
            // Nếu (2^p - 1) là số nguyên tố, ta có một số hoàn hảo
            if (isPrime(mersenne)) {
                long long perfect = (1LL << (p - 1)) * mersenne; // 2^(p-1) * (2^p - 1)
          
                if (perfect > N) break; // Nếu vượt quá N thì dừng vòng lặp ngay
                
                cout << perfect << " ";
                found = true;
            }
        }
    }
    
    if (!found) cout << "Khong co so nao.";
    cout << endl;
}

int main() {
    long long N;
    cout << "Nhap MSSV cua ban (N): ";
    cin >> N;
    
    inSoHoanHao(N);
    
    return 0;
}
