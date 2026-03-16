#include <iostream>
#include <cmath>
#include <stdexcept>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;

// Hàm làm sạch số 0 do sai số dấu phẩy động
MatrixXd fixZero(MatrixXd A) {
    for (int i = 0; i < A.rows(); i++)
        for (int j = 0; j < A.cols(); j++)
            if (fabs(A(i, j)) < 1e-10)
                A(i, j) = 0;
    return A;
}

// 1. NHÂN MA TRẬN (Thủ công)
MatrixXd multiply_manual(const MatrixXd& A, const MatrixXd& B) {
    int x = A.rows();
    int n = A.cols(); // Cần bằng B.rows()
    int y = B.cols();
    
    MatrixXd C = MatrixXd::Zero(x, y);

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            for (int k = 0; k < n; k++) {
                C(i, j) += A(i, k) * B(k, j);
            }
        }
    }
    return C;
}

// 2. TÍNH ĐỊNH THỨC (Thủ công - Tối ưu bằng Khử Gauss O(N^3))
double determinant_manual(MatrixXd A) {
    int n = A.rows();
    double det = 1.0;

    for (int i = 0; i < n; i++) {
        // Partial Pivoting: Tìm phần tử trị tuyệt đối lớn nhất trong cột i
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(A(j, i)) > fabs(A(pivot, i))) {
                pivot = j;
            }
        }
        
        // Hoán vị dòng nếu cần, mỗi lần đổi dòng định thức đổi dấu
        if (pivot != i) {
            A.row(i).swap(A.row(pivot));
            det *= -1.0;
        }

        // Nếu phần tử trục = 0 -> Định thức = 0
        if (fabs(A(i, i)) < 1e-10) return 0.0;

        det *= A(i, i);

        // Khử các dòng bên dưới
        for (int j = i + 1; j < n; j++) {
            double factor = A(j, i) / A(i, i);
            for (int k = i; k < n; k++) {
                A(j, k) -= factor * A(i, k);
            }
        }
    }
    return det;
}

// 3. NGHỊCH ĐẢO MA TRẬN (Thủ công - Gauss-Jordan với Partial Pivoting)
MatrixXd inverse_manual(MatrixXd A) {
    int n = A.rows();
    MatrixXd aug = MatrixXd::Zero(n, 2 * n);

    // Tạo ma trận mở rộng [A | I]
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            aug(i, j) = A(i, j);
        }
        aug(i, i + n) = 1.0;
    }

    // Khử Gauss-Jordan
    for (int i = 0; i < n; i++) {
        // Partial Pivoting
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(aug(j, i)) > fabs(aug(pivot, i))) {
                pivot = j;
            }
        }
        if (pivot != i) {
            aug.row(i).swap(aug.row(pivot));
        }

        if (fabs(aug(i, i)) < 1e-10) {
            throw runtime_error("Ma tran khong kha nghich!");
        }

        // Chuẩn hóa dòng trục về 1
        double pivot_val = aug(i, i);
        for (int j = 0; j < 2 * n; j++) {
            aug(i, j) /= pivot_val;
        }

        // Khử các phần tử khác trên cùng cột
        for (int j = 0; j < n; j++) {
            if (i != j) {
                double factor = aug(j, i);
                for (int k = 0; k < 2 * n; k++) {
                    aug(j, k) -= factor * aug(i, k);
                }
            }
        }
    }

    // Tách lấy nửa bên phải [I | A^-1]
    MatrixXd result(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result(i, j) = aug(i, j + n);
        }
    }
    return result;
}

int main() {
    int row, col;
    cout << "Nhap so hang va cot cua ma tran A (Phai la ma tran vuong): ";
    cin >> row >> col;

    if (row != col) {
        cout << "Loi: De cheo hoa, ma tran phai la ma tran vuong!" << endl;
        return -1;
    }

    MatrixXd A(row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> A(i, j);
        }
    }

    cout << "\n--- MA TRAN A ---\n" << A << endl;

    // CHỈ DÙNG EIGEN CHO TRỊ RIÊNG VÀ VECTƠ RIÊNG
    EigenSolver<MatrixXd> solver(A);
    VectorXd eigenValues = solver.eigenvalues().real();
    MatrixXd P = solver.eigenvectors().real();

    cout << "\n--- Tri Rieng ---\n" << fixZero(eigenValues) << endl;
    cout << "\n--- MA TRAN P ---\n" << fixZero(P) << endl;

    // Tự tạo ma trận đường chéo D
    MatrixXd D = MatrixXd::Zero(row, col);
    for (int i = 0; i < row; i++) {
        D(i, i) = eigenValues(i);
    }
    cout << "\n--- MA TRAN D ---\n" << fixZero(D) << endl;

    // Dùng hàm tính định thức thủ công kiểm tra
    double det_P = determinant_manual(P);
    if (fabs(det_P) < 1e-10) {
        cout << "\nDinh thuc cua P = 0. Ma tran khong the cheo hoa!" << endl;
        return 0;
    }

    // Dùng hàm nghịch đảo thủ công
    MatrixXd Pinv = inverse_manual(P);
    cout << "\n--- MA TRAN P^-1 ---\n" << fixZero(Pinv) << endl;

    // Dùng hàm nhân thủ công để kiểm chứng A = P * D * P^-1
    MatrixXd PD = multiply_manual(P, D);
    MatrixXd PDPinv = multiply_manual(PD, Pinv);

    cout << "\n--- KIEM CHUNG P * D * P^-1 ---\n" << fixZero(PDPinv) << endl;

    return 0;
}
