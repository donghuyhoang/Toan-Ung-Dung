#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

const double PI = 3.14159265358979323846;
const double EPS = 1e-9;

struct Matrix {
    int n;
    vector<vector<double>> x;

    Matrix(int n) : n(n) {
        x.assign(n, vector<double>(n, 0));
    }

    void input() {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) cin >> x[i][j];
    }

    void output() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (abs(x[i][j]) < EPS) cout << 0 << " ";
                else cout << x[i][j] << " ";
            }
            cout << endl;
        }
    }

    static Matrix Identity(int n) {
        Matrix I(n);
        for (int i = 0; i < n; i++) I.x[i][i] = 1;
        return I;
    }

    double trace() {
        double s = 0;
        for (int i = 0; i < n; i++) s += x[i][i];
        return s;
    }

    double det() {
        if (n == 2) return x[0][0] * x[1][1] - x[0][1] * x[1][0];
        return x[0][0] * (x[1][1] * x[2][2] - x[1][2] * x[2][1]) -
               x[0][1] * (x[1][0] * x[2][2] - x[1][2] * x[2][0]) +
               x[0][2] * (x[1][0] * x[2][1] - x[1][1] * x[2][0]);
    }

    double sumMinors() {
        return (x[1][1] * x[2][2] - x[1][2] * x[2][1]) +
               (x[0][0] * x[2][2] - x[0][2] * x[2][0]) +
               (x[0][0] * x[1][1] - x[0][1] * x[1][0]);
    }

    friend Matrix operator*(const Matrix&, const Matrix&);
    friend Matrix operator-(const Matrix&, const Matrix&);
    friend Matrix operator*(double, const Matrix&);
};

Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix c(a.n);
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < a.n; j++)
            for (int l = 0; l < a.n; l++)
                c.x[i][j] += a.x[i][l] * b.x[l][j];
    return c;
}

Matrix operator-(const Matrix& a, const Matrix& b) {
    Matrix c(a.n);
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < a.n; j++) c.x[i][j] = a.x[i][j] - b.x[i][j];
    return c;
}

Matrix operator*(double k, const Matrix& a) {
    Matrix c(a.n);
    for (int i = 0; i < a.n; i++)
        for (int j = 0; j < a.n; j++) c.x[i][j] = a.x[i][j] * k;
    return c;
}

vector<double> solveEquation(Matrix A) {
    vector<double> roots;
    if (A.n == 2) {
        double b = -A.trace();
        double c = A.det();
        double delta = b * b - 4 * c;
        if (delta >= 0) {
            roots.push_back((-b - sqrt(delta)) / 2.0);
            roots.push_back((-b + sqrt(delta)) / 2.0);
        }
    } else {
        double a = 1, b = -A.trace(), c = A.sumMinors(), d = -A.det();
        double A_3 = b / 3.0;
        double p = c - b * A_3;
        double q = 2.0 * pow(A_3, 3) - A_3 * c + d;
        double delta = (q * q) / 4.0 + (p * p * p) / 27.0;

        if (delta <= EPS) {
            double r = sqrt(-(p * p * p) / 27.0);
            double phi = acos(-q / (2.0 * r));
            double k = 2.0 * sqrt(-p / 3.0);
            roots.push_back(k * cos(phi / 3.0) - A_3);
            roots.push_back(k * cos((phi + 2.0 * PI) / 3.0) - A_3);
            roots.push_back(k * cos((phi + 4.0 * PI) / 3.0) - A_3);
        } else {
            double sqD = sqrt(delta);
            roots.push_back(cbrt(-q / 2.0 + sqD) + cbrt(-q / 2.0 - sqD) - A_3);
        }
    }
    sort(roots.begin(), roots.end());
    return roots;
}

vector<double> eigenVec(Matrix A, double lambda) {
    Matrix B = A - (lambda * Matrix::Identity(A.n));
    vector<double> v(A.n, 0);

    if (A.n == 2) {
        v[0] = -B.x[0][1]; v[1] = B.x[0][0];
        if (abs(v[0]) < EPS && abs(v[1]) < EPS) {
            v[0] = -B.x[1][1]; v[1] = B.x[1][0];
        }
    } else {
        double x = B.x[0][1] * B.x[1][2] - B.x[0][2] * B.x[1][1];
        double y = B.x[0][2] * B.x[1][0] - B.x[0][0] * B.x[1][2];
        double z = B.x[0][0] * B.x[1][1] - B.x[0][1] * B.x[1][0];

        if (abs(x) < EPS && abs(y) < EPS && abs(z) < EPS) {
            x = B.x[0][1] * B.x[2][2] - B.x[0][2] * B.x[2][1];
            y = B.x[0][2] * B.x[2][0] - B.x[0][0] * B.x[2][2];
            z = B.x[0][0] * B.x[2][1] - B.x[0][1] * B.x[2][0];
        }
        if (abs(x) < EPS && abs(y) < EPS && abs(z) < EPS) {
            x = B.x[1][1] * B.x[2][2] - B.x[1][2] * B.x[2][1];
            y = B.x[1][2] * B.x[2][0] - B.x[1][0] * B.x[2][2];
            z = B.x[1][0] * B.x[2][1] - B.x[1][1] * B.x[2][0];
        }

        double len = sqrt(x*x + y*y + z*z);
        if (len < EPS) {
            for(int i=0; i<3; i++) {
                if (abs(B.x[i][0]) > EPS || abs(B.x[i][1]) > EPS || abs(B.x[i][2]) > EPS) {
                    x = -B.x[i][1]; y = B.x[i][0]; z = 0;
                    len = sqrt(x*x + y*y + z*z);
                    if (len < EPS) { x = -B.x[i][2]; y = 0; z = B.x[i][0]; }
                    len = sqrt(x*x + y*y + z*z);
                    if (len < EPS) { x = 0; y = -B.x[i][2]; z = B.x[i][1]; }
                    break; 
                }
            }
        }
        v = {x, y, z};
    }
    
    double len = 0; for(double val : v) len += val*val;
    len = sqrt(len);
    if (len < EPS) { v[0] = 1; return v; }
    for(double &val : v) val /= len;
    return v;
}

int main() {
    int n = 3; 
    // cout << "Nhap n (2 hoac 3): "; cin >> n; 
    Matrix A(n);
    cout << "Nhap ma tran " << n << "x" << n << ":" << endl;
    A.input();

    vector<double> ev = solveEquation(A);
    if (ev.size() < n) return 0;

    Matrix P(n), D(n);
    for (int i = 0; i < n; i++) {
        D.x[i][i] = ev[i];
        vector<double> v = eigenVec(A, ev[i]);
        for(int r = 0; r < n; r++) P.x[r][i] = v[r];
    }

    cout << "P:" << endl; P.output();
    cout << "D:" << endl; D.output();
    cout << "Check AP:" << endl; (A * P).output();
    cout << "Check PD:" << endl; (P * D).output();
}
