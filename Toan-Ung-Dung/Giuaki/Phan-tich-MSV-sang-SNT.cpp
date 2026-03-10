#include <iostream>
using namespace std;

int main(){
	long long n; cin >> n;
	int i = 2,cnt = 0;
	while(n > 1){
		if(n % i == 0){
			while(n % i == 0){
				n /= i;
				++cnt;
			}
			cout << i << "^" << cnt << " + ";
		}
		++i;
		cnt = 0;
	}
}