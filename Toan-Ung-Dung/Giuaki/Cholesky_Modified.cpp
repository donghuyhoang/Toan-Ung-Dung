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

pair<Matrix, Matrix> choleskyDecompositionModified(Matrix a, bool &canDecompose) {
    int n = a.n;
    Matrix L(n, n), D(n, n);
    canDecompose = true;

    for (int i = 0; i < n; i++) L.x[i][i] = 1;

    for (int j = 0; j < n; j++) {
        double sumD = 0;
        for (int k = 0; k < j; k++) {
            sumD += L.x[j][k] * L.x[j][k] * D.x[k][k];
        }
        D.x[j][j] = a.x[j][j] - sumD;

        if (abs(D.x[j][j]) < EPS) {
            canDecompose = false;
            return {L, D};
        }

        for (int i = j + 1; i < n; i++) {
            double sumL = 0;
            for (int k = 0; k < j; k++) {
                sumL += L.x[i][k] * L.x[j][k] * D.x[k][k];
            }
            L.x[i][j] = (a.x[i][j] - sumL) / D.x[j][j];
        }
    }
    return {L, D};
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

    bool success = false;
    pair<Matrix, Matrix> res = choleskyDecompositionModified(A, success);

    if (!success) {
        cout << "Khong the phan ra LDL^T (ton tai D[j][j] gan bang 0)." << endl;
    } else {
        cout << "Ma tran L (Don vi tam giac duoi):" << endl; res.first.output();
        cout << "Ma tran D (Duong cheo):" << endl; res.second.output();
        cout << "Ma tran L^T:" << endl; res.first.outputTranspose();
    }
    return 0;
}
