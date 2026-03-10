#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a % b);
}

int TrungHoa(int k, int m[], int a[], int X[], int X_1[], int &M)
{
	M = 1;
	int ans = 0;

	for (int i = 0; i < k; i++)
		M = M * m[i];

	for (int i = 0; i < k; i++)
		X[i] = M / m[i];

	for (int i = 0; i < k; i++)
	{
		int j = 1;

		while ((j * m[i] + 1) % X[i] != 0)
		{
			j++;
		}

		X_1[i] = (j * m[i] + 1) / X[i];
	}

	for (int i = 0; i < k; i++)
		ans = ans + a[i] * X[i] * X_1[i];

	return ans;
}

int main()
{
	int k;
	int M;

	cout << "Nhap so luong phuong trinh can tinh: ";
	cin >> k;

	int m[k + 1], a[k + 1], X[k + 1], X_1[k + 1];
	bool kt;

	for (int i = 0; i < k; i++)
	{
		cout << "a[" << i + 1 << "] = ";
		cin >> a[i];

		cout << "m[" << i + 1 << "] = ";
		cin >> m[i];

		do
		{
			kt = true;

			for (int j = 0; j < i; j++)
			{
				if (gcd(m[i], m[j]) != 1)
				{
					cout << "Nhap lai m[" << i + 1 << "] = ";
					cin >> m[i];
					kt = false;
					break;
				}
			}

		} while (!kt);
	}

	int ans = TrungHoa(k, m, a, X, X_1, M);
	int x = ans % M;

	cout << "Phuong trinh can tim la: x = " << x << " + k * " << M << endl;

	return 0;
}
