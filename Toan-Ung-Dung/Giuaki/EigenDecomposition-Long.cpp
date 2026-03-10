#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;

double Det(MatrixXd A, int rows)
{
    double s = 1;
    double det;
    MatrixXd a(A.rows(), A.cols());

    if (rows == 1)
    {
        return A(0, 0);
    }
    else
    {
        det = 0;

        for (int c = 0; c < rows; c++)
        {
            int m = 0;
            int n = 0;

            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < rows; j++)
                {
                    a(i, j) = 0;

                    if (i != 0 && j != c)
                    {
                        a(m, n) = A(i, j);

                        if (n < (rows - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }

            det = det + s * (A(0, c) * Det(a, rows - 1));
            s = -1 * s;
        }
    }

    return det;
}

MatrixXd fixZero(MatrixXd A)
{
    for (int i = 0; i < A.rows(); i++)
    {
        for (int j = 0; j < A.cols(); j++)
        {
            if (fabs(A(i, j)) < 1e-10)
            {
                A(i, j) = 0;
            }
        }
    }

    return A;
}

MatrixXd inverse_Matrix(MatrixXd A)
{
    double r, a;
    MatrixXd inc(A.rows(), A.cols() * 2);

    for (int i = 0; i < inc.rows(); i++)
    {
        for (int j = 0; j < inc.cols(); j++)
        {
            if (j < A.rows())
                inc(i, j) = A(i, j);
            else
                inc(i, j) = (i == (j - A.rows())) ? 1 : 0;
        }
    }

    for (int i = 0; i < A.rows(); i++)
    {
        for (int j = 0; j < A.rows(); j++)
        {
            if (i != j)
            {
                r = inc(j, i) / inc(i, i);

                for (int k = 0; k < inc.cols(); k++)
                {
                    inc(j, k) -= r * inc(i, k);
                }
            }
        }
    }

    for (int i = 0; i < A.rows(); i++)
    {
        a = inc(i, i);

        for (int j = 0; j < inc.cols(); j++)
        {
            inc(i, j) /= a;
        }
    }

    MatrixXd rs(A.rows(), A.cols());

    for (int i = 0; i < A.rows(); i++)
    {
        for (int j = 0; j < A.cols(); j++)
        {
            rs(i, j) = inc(i, j + A.cols());
        }
    }

    return rs;
}

MatrixXd multiply(MatrixXd A, MatrixXd B, int x, int n, int y)
{
    MatrixXd rs(x, y);
    rs.setZero();

    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < n; k++)
            {
                rs(i, j) += A(i, k) * B(k, j);
            }
        }
    }

    return rs;
}

int main()
{
    int row, col;

    cout << "Nhap so hang va so cot cho ma tran A: " << endl;
    cin >> row >> col;

    MatrixXd A(row, col);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << "A[" << i + 1 << "][" << j + 1 << "] = ";
            cin >> A(i, j);
        }
    }

    cout << endl;
    cout << "Ma tran A luc ban dau: " << endl;
    cout << A << endl;

    EigenSolver<MatrixXd> solver(A);

    MatrixXd EigenVa = solver.eigenvalues().real().matrix();

    cout << "Cac eigenvalue la: " << endl;
    cout << EigenVa << endl;

    cout << "Ma tran P = " << endl;

    MatrixXd EigenVe = fixZero(solver.eigenvectors().real());

    cout << EigenVe << endl;

    if (Det(EigenVe, EigenVe.rows()) == 0)
    {
        cout << "Ma tran khong co nghich dao!" << endl;
        return 0;
    }

    cout << "Ma tran P^(-1) = " << endl;
    cout << fixZero(inverse_Matrix(EigenVe)) << endl;

    MatrixXd D(A.rows(), A.cols());
    D.setZero();

    for (int i = 0; i < D.rows(); i++)
    {
        for (int j = 0; j < D.cols(); j++)
        {
            if (i == j)
                D(i, j) = EigenVa(i);
        }
    }

    cout << "Ma tran D:" << endl;
    cout << D << endl;

    cout << "P * D = " << endl;
    cout << multiply(EigenVe, D, EigenVe.rows(), EigenVe.cols(), D.cols()) << endl;

    cout << "A * P = " << endl;
    cout << multiply(A, EigenVe, A.rows(), A.cols(), EigenVe.cols()) << endl;

    cout << "P * D * P^(-1) = " << endl;
    cout << fixZero(
        multiply(
            multiply(EigenVe, D, EigenVe.rows(), EigenVe.cols(), D.cols()),
            inverse_Matrix(EigenVe),
            EigenVe.rows(),
            EigenVe.cols(),
            EigenVe.cols()
        )
    ) << endl;

    return 0;
}
