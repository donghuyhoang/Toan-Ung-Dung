#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;

const double EPS = 1e-5;

// Định nghĩa kiểu dữ liệu cho gọn
typedef vector<vector<double>> Mat;
typedef vector<double> Vec;

// 1. In ma trận
void printMatrix(const string& name, const Mat& M) {
    cout << name << ":\n";
    for (const auto& row : M) {
        for (double val : row) {
            // Fix lỗi số thực rất nhỏ (ví dụ -0.0000) hiển thị cho đẹp
            if (abs(val) < EPS) val = 0.0; 
            cout << setw(10) << setprecision(4) << fixed << val << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// 2. Chuyển vị ma trận (Transpose)
Mat transpose(const Mat& A) {
    int rows = A.size(), cols = A[0].size();
    Mat T(cols, vector<double>(rows, 0.0));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            T[j][i] = A[i][j];
        }
    }
    return T;
}

// 3. Nhân 2 ma trận (Matrix x Matrix)
Mat multiply(const Mat& A, const Mat& B) {
    int rA = A.size(), cA = A[0].size(), cB = B[0].size();
    Mat res(rA, vector<double>(cB, 0.0));
    for (int i = 0; i < rA; i++) {
        for (int j = 0; j < cB; j++) {
            for (int k = 0; k < cA; k++) res[i][j] += A[i][k] * B[k][j];
        }
    }
    return res;
}

// 4. Nhân ma trận với vector (Matrix x Vector)
Vec multiplyMatVec(const Mat& A, const Vec& V) {
    int rows = A.size(), cols = A[0].size();
    Vec res(rows, 0.0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) res[i] += A[i][j] * V[j];
    }
    return res;
}

// 5. Tích vô hướng của 2 vector (Dot product)
double dotProduct(const Vec& A, const Vec& B) {
    double sum = 0;
    for (size_t i = 0; i < A.size(); i++) sum += A[i] * B[i];
    return sum;
}

// 6. Trừ 2 vector (A - B)
Vec subtractVec(const Vec& A, const Vec& B) {
    Vec res(A.size());
    for (size_t i = 0; i < A.size(); i++) res[i] = A[i] - B[i];
    return res;
}

// 7. Nhân vector với một số vô hướng (A * scalar)
Vec scaleVec(const Vec& A, double scalar) {
    Vec res(A.size());
    for (size_t i = 0; i < A.size(); i++) res[i] = A[i] * scalar;
    return res;
}

// 8. Tính độ dài vector (Norm) và Chuẩn hóa (Normalize)
double norm(const Vec& A) {
    return sqrt(dotProduct(A, A));
}

Vec normalize(const Vec& A) {
    double n = norm(A);
    Vec res(A.size(), 0.0);
    if (n > EPS) {
        for (size_t i = 0; i < A.size(); i++) res[i] = A[i] / n;
    }
    return res;
}

// 9. Tiện ích: Lấy và Gán cột của ma trận
Vec getCol(const Mat& M, int colIdx) {
    Vec res(M.size());
    for (size_t i = 0; i < M.size(); i++) res[i] = M[i][colIdx];
    return res;
}

void setCol(Mat& M, int colIdx, const Vec& V) {
    for (size_t i = 0; i < M.size(); i++) M[i][colIdx] = V[i];
}

int main() {
    int n, m;
    cout << "Nhap so hang n: "; cin >> n;
    cout << "Nhap so cot m: "; cin >> m;
    
    Mat A(n, vector<double>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "Nhap A[" << i << "][" << j << "]: ";
            cin >> A[i][j];
        }
    }

    // 1. Tính S = A^T * A
    Mat A_T = transpose(A);
    Mat S = multiply(A_T, A);

    // Dùng Eigen ĐỂ TÌM TRỊ RIÊNG / VECTOR RIÊNG
    MatrixXd Eigen_S(m, m);
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < m; j++) Eigen_S(i, j) = S[i][j];

    SelfAdjointEigenSolver<MatrixXd> solver(Eigen_S);
    if (solver.info() != Success) {
        cout << "Tinh eigen that bai\n"; return 0;
    }

    VectorXd eigenVals = solver.eigenvalues();
    MatrixXd eigenVecs = solver.eigenvectors();

    // Rút xuất kết quả từ Eigen ra mảng thuần C++, SẮP XẾP GIẢM DẦN
    Vec sorted_eigenvalues(m);
    Mat V(m, vector<double>(m));
    for (int i = 0; i < m; i++) {
        int targetIdx = m - 1 - i; // Lấy từ cuối lên để có thứ tự giảm dần
        sorted_eigenvalues[i] = eigenVals(targetIdx);
        for (int j = 0; j < m; j++) {
            V[j][i] = eigenVecs(j, targetIdx);
        }
    }

    // 2. Khởi tạo Sigma và U
    Mat Sigma(n, vector<double>(m, 0.0));
    Mat U(n, vector<double>(n, 0.0));
    int rank = 0;

    // Tính các cột của U với sigma > 0
    for (int i = 0; i < min(n, m); i++) {
        if (sorted_eigenvalues[i] > EPS) {
            double sigma = sqrt(sorted_eigenvalues[i]);
            Sigma[i][i] = sigma;
            
            // Tính công thức: u_i = (A * v_i) / sigma_i
            Vec v_i = getCol(V, i);
            Vec Av_i = multiplyMatVec(A, v_i);
            Vec u_i = scaleVec(Av_i, 1.0 / sigma);
            
            setCol(U, i, u_i);
            rank++;
        }
    }

    // 3. Trực giao hóa Gram-Schmidt cho các cột còn thiếu của U
    if (rank < n) {
        int current_col = rank;
        for (int i = 0; i < n && current_col < n; i++) {
            // Khởi tạo vector cơ sở chuẩn e_i = [0, 0, ..., 1, ..., 0]
            Vec vec(n, 0.0);
            vec[i] = 1.0;

            // Thuật toán gọt giũa (trừ đi hình chiếu lên các vector u đã có)
            for (int j = 0; j < current_col; j++) {
                Vec u_j = getCol(U, j);
                double projection = dotProduct(vec, u_j);
                Vec proj_vec = scaleVec(u_j, projection);
                vec = subtractVec(vec, proj_vec);
            }

            // Nếu độ dài > EPS, nó là một vector mới hợp lệ
            if (norm(vec) > EPS) {
                setCol(U, current_col, normalize(vec));
                current_col++;
            }
        }
    }

    // 4. In kết quả và kiểm tra (Reconstruction)
    Mat V_T = transpose(V);
    cout << "\n--- KET QUA SVD ---\n";
    printMatrix("Ma tran U", U);
    printMatrix("Ma tran Sigma", Sigma);
    printMatrix("Ma tran V^T", V_T);

    // Kiểm tra A = U * Sigma * V^T
    Mat USigma = multiply(U, Sigma);
    Mat Reconstructed_A = multiply(USigma, V_T);
    printMatrix("Kiem tra (U * Sigma * V^T)", Reconstructed_A);

    return 0;
}
