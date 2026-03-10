#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double EPS = 1e-5;

struct Matrix {
    int n, m;
    vector<vector<double>> x;
    Matrix(int n, int m) : n(n), m(m) {
        x.assign(n, vector<double>(m, 0));
    }

    void input() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cin >> x[i][j];
        }
    }

    void output() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << setw(10) << (abs(x[i][j]) < EPS ? 0 : x[i][j]) << " ";
            }
            cout << endl;
        }
    }

    void outputTranspose() {
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                cout << setw(10) << (abs(x[i][j]) < EPS ? 0 : x[i][j]) << " ";
            }
            cout << endl;
        }
    }
};

bool isSymmetry(const Matrix& a) {
    for (int i = 0; i < a.n; i++) {
        for (int j = i + 1; j < a.n; j++) {
            if (abs(a.x[i][j] - a.x[j][i]) > EPS) return false;
        }
    }
    return true;
}

Matrix choleskyDecomposition(Matrix a, bool &isPositiveDefinite) {
    int n = a.n;
    Matrix lower(n, n);
    isPositiveDefinite = true;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0;
            if (i == j) {
                for (int k = 0; k < j; k++) sum += pow(lower.x[j][k], 2);
                double val = a.x[j][j] - sum;
                if (val < EPS) { // Kiểm tra xác định dương với sai số EPS
                    isPositiveDefinite = false;
                    return lower;
                }
                lower.x[j][j] = sqrt(val);
            } else {
                for (int k = 0; k < j; k++) sum += lower.x[i][k] * lower.x[j][k];
                lower.x[i][j] = (a.x[i][j] - sum) / lower.x[j][j];
            }
        }
    }
    return lower;
}

int main() {
    int n;
    cout << "Nhap bac ma tran vuong: "; cin >> n;
    Matrix A(n, n);
    A.input();

    if (!isSymmetry(A)) {
        cout << "Ma tran khong doi xung!" << endl;
        return 0;
    }

    bool isPD = false;
    Matrix L = choleskyDecomposition(A, isPD);

    if (!isPD) {
        cout << "Ma tran khong xac dinh duong (co the co tri rieng <= 0)." << endl;
    } else {
        cout << "Ma tran L:" << endl; L.output();
        cout << "Ma tran L^T:" << endl; L.outputTranspose();
    }
    return 0;
}
