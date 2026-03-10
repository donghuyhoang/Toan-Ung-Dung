#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;

MatrixXd fixZero(MatrixXd A)
{
    for (int i = 0; i < A.rows(); i++)
        for (int j = 0; j < A.cols(); j++)
            if (fabs(A(i, j)) < 1e-10)
                A(i, j) = 0;
    return A;
}

MatrixXd inverse_Matrix(MatrixXd A)
{
    int n = A.rows();
    MatrixXd aug(n, 2*n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < 2*n; j++)
        {
            if (j < n)
                aug(i,j) = A(i,j);
            else
                aug(i,j) = (i == j-n) ? 1 : 0;
        }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i != j)
            {
                double r = aug(j,i) / aug(i,i);
                for (int k = 0; k < 2*n; k++)
                    aug(j,k) -= r * aug(i,k);
            }

    for (int i = 0; i < n; i++)
    {
        double a = aug(i,i);
        for (int j = 0; j < 2*n; j++)
            aug(i,j) /= a;
    }

    MatrixXd result(n,n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result(i,j) = aug(i,j+n);

    return result;
}

MatrixXd multiply(MatrixXd A, MatrixXd B)
{
    MatrixXd C(A.rows(), B.cols());
    C.setZero();

    for (int i = 0; i < A.rows(); i++)
        for (int j = 0; j < B.cols(); j++)
            for (int k = 0; k < A.cols(); k++)
                C(i,j) += A(i,k) * B(k,j);

    return C;
}

int main()
{
    int row, col;

    cout << "Nhap so hang va cot cua ma tran A:\n";
    cin >> row >> col;

    MatrixXd A(row, col);

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
        {
            cout << "A[" << i+1 << "][" << j+1 << "] = ";
            cin >> A(i,j);
        }

    cout << "\nMa tran A:\n" << A << endl;

    EigenSolver<MatrixXd> solver(A);

    VectorXd eigenValues = solver.eigenvalues().real();
    MatrixXd P = solver.eigenvectors().real();

    cout << "\nEigenvalues:\n" << eigenValues << endl;

    cout << "\nMa tran P:\n" << fixZero(P) << endl;

    MatrixXd D = MatrixXd::Zero(row,col);

    for (int i = 0; i < row; i++)
        D(i,i) = eigenValues(i);

    cout << "\nMa tran D:\n" << D << endl;

    MatrixXd Pinv = inverse_Matrix(P);

    cout << "\nP^-1:\n" << fixZero(Pinv) << endl;

    cout << "\nP * D:\n";
    cout << fixZero(multiply(P,D)) << endl;

    cout << "\nA * P:\n";
    cout << fixZero(multiply(A,P)) << endl;

    cout << "\nP * D * P^-1:\n";
    cout << fixZero(multiply(multiply(P,D),Pinv)) << endl;

    return 0;
}
