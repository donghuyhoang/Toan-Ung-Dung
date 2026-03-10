#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Matrix {
    int n, m;
    vector<vector<double>> x;
    Matrix(int n, int m) : n(n), m(m) {
        x.assign(n, vector<double>(m, 0));
    }
    void input() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> x[i][j];
            }
        }
    }
    void output() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << x[i][j] << " ";
            }
            cout << endl;
        }
    }
    void outputTranspose() {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cout << x[j][i] << " ";
            }
            cout << endl;
        }
    }
    friend Matrix operator*(const Matrix&, const Matrix&);
};

Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix c(a.n, b.m);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < b.m; j++) {
            double res = 0;
            for (int l = 0; l < a.m; l++) {
                res += a.x[i][l] * b.x[l][j];
            }
            c.x[i][j] = res;
        }
    }
    return c;
}

Matrix Transpose(Matrix a) {
    Matrix b(a.m, a.n);
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            b.x[j][i] = a.x[i][j];
        }
    }
    return b;
}

bool isSymmetry(Matrix a) {
    int n = a.n;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a.x[i][j] != a.x[j][i]) return false;
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
                for (int k = 0; k < j; k++) {
                    sum += pow(lower.x[j][k], 2);
                }
                double val = a.x[j][j] - sum;
                if (val <= 0) {
                    isPositiveDefinite = false;
                    return lower;
                }
                lower.x[j][j] = sqrt(val);
            }
            else {
                for (int k = 0; k < j; k++) {
                    sum += lower.x[i][k] * lower.x[j][k];
                }
                lower.x[i][j] = (a.x[i][j] - sum) / lower.x[j][j];
            }
        }
    }
    return lower;
}

pair<Matrix, Matrix> choleskyDecompositionModified(Matrix a) {
    int n = a.n;
    Matrix L(n, n), D(n, n);
    for (int i = 0; i < n; i++) L.x[i][i] = 1;
    for (int j = 0; j < n; j++) {
        double sum = 0;
        for (int k = 0; k < j; k++) {
            sum += L.x[j][k] * L.x[j][k] * D.x[k][k];
        }
        D.x[j][j] = a.x[j][j] - sum;
        for (int i = j + 1; i < n; i++) {
            sum = 0;
            for (int k = 0; k < j; k++) {
                sum += L.x[i][k] * L.x[j][k] * D.x[k][k];
            }
            L.x[i][j] = (a.x[i][j] - sum) / D.x[j][j];
        }
    }
    return {L, D};
}

int main() {
    cout << "Nhap so hang so cot: ";
    int n; cin >> n;
    Matrix A(n, n);
    A.input();
    if (!isSymmetry(A)) {
        cout << "Ma tran khong doi xung" << endl;
        return 0;
    }
    bool isPD = false;
    Matrix L = choleskyDecomposition(A, isPD);
    if (!isPD) {
        cout << "Ma tran khong xac dinh duong, khong the dung Cholesky co dien" << endl;
    }
    else {
        cout << "L:" << endl; L.output();
        cout << "L^T:" << endl; L.outputTranspose();
    }

    cout << "Cholesky bien the:" << endl;
    pair<Matrix, Matrix> p = choleskyDecompositionModified(A);
    cout << "K:" << endl; p.first.output();
    cout << "D:" << endl; p.second.output();
    cout << "K^T" << endl; p.first.outputTranspose();
    return 0;
}
