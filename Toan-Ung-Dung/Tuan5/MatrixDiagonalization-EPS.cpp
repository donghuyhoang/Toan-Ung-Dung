#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const double PI = 3.14159265358979323846;
const double EPS = 1e-5;

struct Matrix
{
	int n;
	vector<vector<double>> x;

	Matrix(int n)
	{
		this->n = n;
		x.assign(n, vector<double>(n, 0));
	}

	void input()
	{
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				cin >> x[i][j];
	}

	void output()
	{
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < n; j++)
			{
				if(abs(x[i][j]) < EPS) cout << 0 << " ";
				else cout << x[i][j] << " ";
			}
			cout << endl;
		}
	}

	static Matrix Identity(int n)
	{
		Matrix I(n);
		for(int i = 0; i < n; i++)
			I.x[i][i] = 1;
		return I;
	}

	double trace()
	{
		double s = 0;
		for(int i = 0; i < n; i++)
			s += x[i][i];
		return s;
	}

	double det()
	{
		if(n == 2)
			return x[0][0]*x[1][1] - x[0][1]*x[1][0];

		return
			x[0][0]*(x[1][1]*x[2][2] - x[1][2]*x[2][1]) -
			x[0][1]*(x[1][0]*x[2][2] - x[1][2]*x[2][0]) +
			x[0][2]*(x[1][0]*x[2][1] - x[1][1]*x[2][0]);
	}

	double sumMinors()
	{
		return
			(x[1][1]*x[2][2] - x[1][2]*x[2][1]) +
			(x[0][0]*x[2][2] - x[0][2]*x[2][0]) +
			(x[0][0]*x[1][1] - x[0][1]*x[1][0]);
	}
};

Matrix operator*(const Matrix& a, const Matrix& b)
{
	Matrix c(a.n);

	for(int i = 0; i < a.n; i++)
		for(int j = 0; j < a.n; j++)
			for(int k = 0; k < a.n; k++)
				c.x[i][j] += a.x[i][k] * b.x[k][j];

	return c;
}

Matrix operator-(const Matrix& a, const Matrix& b)
{
	Matrix c(a.n);

	for(int i = 0; i < a.n; i++)
		for(int j = 0; j < a.n; j++)
			c.x[i][j] = a.x[i][j] - b.x[i][j];

	return c;
}

Matrix operator*(double k, const Matrix& a)
{
	Matrix c(a.n);

	for(int i = 0; i < a.n; i++)
		for(int j = 0; j < a.n; j++)
			c.x[i][j] = k * a.x[i][j];

	return c;
}

vector<double> solveEquation(Matrix A)
{
	vector<double> roots;

	if(A.n == 2)
	{
		double b = -A.trace();
		double c = A.det();

		double delta = b*b - 4*c;

		if(delta >= 0)
		{
			roots.push_back((-b - sqrt(delta)) / 2);
			roots.push_back((-b + sqrt(delta)) / 2);
		}
	}
	else
	{
		double a = 1;
		double b = -A.trace();
		double c = A.sumMinors();
		double d = -A.det();

		double A3 = b / 3.0;

		double p = c - b*A3;
		double q = 2*pow(A3,3) - A3*c + d;

		double delta = q*q/4 + p*p*p/27;

		if(delta <= EPS)
		{
			double r = sqrt(-(p*p*p)/27);
			double phi = acos(-q/(2*r));
			double k = 2*sqrt(-p/3);

			roots.push_back(k*cos(phi/3) - A3);
			roots.push_back(k*cos((phi+2*PI)/3) - A3);
			roots.push_back(k*cos((phi+4*PI)/3) - A3);
		}
		else
		{
			double sqD = sqrt(delta);

			roots.push_back(
				cbrt(-q/2 + sqD) +
				cbrt(-q/2 - sqD) - A3
			);
		}
	}

	sort(roots.begin(), roots.end());
	return roots;
}

vector<double> eigenVec(Matrix A, double lambda)
{
	Matrix B = A - (lambda * Matrix::Identity(A.n));
	vector<double> v(A.n,0);

	if(A.n == 2)
	{
		v[0] = -B.x[0][1];
		v[1] =  B.x[0][0];

		if(abs(v[0]) < EPS && abs(v[1]) < EPS)
		{
			v[0] = -B.x[1][1];
			v[1] =  B.x[1][0];
		}
	}
	else
	{
		double x = B.x[0][1]*B.x[1][2] - B.x[0][2]*B.x[1][1];
		double y = B.x[0][2]*B.x[1][0] - B.x[0][0]*B.x[1][2];
		double z = B.x[0][0]*B.x[1][1] - B.x[0][1]*B.x[1][0];

		v = {x,y,z};
	}

	double len = 0;

	for(double val : v)
		len += val*val;

	len = sqrt(len);

	if(len < EPS)
	{
		v[0] = 1;
		return v;
	}

	for(double &val : v)
		val /= len;

	return v;
}

int main()
{
	int n;

	cout << "Nhap n (2 hoac 3): ";
	cin >> n;

	Matrix A(n);

	cout << "Nhap ma tran:" << endl;
	A.input();

	vector<double> ev = solveEquation(A);

	if(ev.size() < n)
	{
		cout << "Khong du eigenvalue de cheo hoa\n";
		return 0;
	}

	Matrix P(n), D(n);

	for(int i = 0; i < n; i++)
	{
		D.x[i][i] = ev[i];

		vector<double> v = eigenVec(A, ev[i]);

		for(int r = 0; r < n; r++)
			P.x[r][i] = v[r];
	}

	cout << "\nMa tran P:\n";
	P.output();

	cout << "\nMa tran D:\n";
	D.output();

	cout << "\nCheck A*P:\n";
	(A * P).output();

	cout << "\nCheck P*D:\n";
	(P * D).output();
}
