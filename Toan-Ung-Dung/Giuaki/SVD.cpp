#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std;
using namespace Eigen;

double EPS = 1e-5;

MatrixXd fixEpsilon(MatrixXd A)
{
    for(int i=0;i<A.rows();i++)
        for(int j=0;j<A.cols();j++)
            if(fabs(A(i,j)) < EPS)
                A(i,j) = 0;
    return A;
}

void transpose(MatrixXd& V, MatrixXd& V1, int row, int col)
{
    for (int i = 0; i < col; i++)
        for (int j = 0; j < row; j++)
            V1(i,j) = V(j,i);
}

void reverse_matrix(MatrixXd& matrix)
{
    for (int j = 0; j < matrix.cols()/2; j++)
        for (int i = 0; i < matrix.rows(); i++)
            swap(matrix(i,j), matrix(i, matrix.cols()-1-j));
}

double matrixMultiply(VectorXd v1, VectorXd v2, int n)
{
    double ans = 0;

    for(int i = 0; i < n; i++)
        ans += v1[i] * v2[i];

    return ans;
}

int main()
{
    int m,n;

    cout << "Number of rows:\n";
    cin >> m;

    cout << "Number of columns:\n";
    cin >> n;

    MatrixXd A(m,n), At(n,m);

    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
        {
            cout<<"A["<<i+1<<"]["<<j+1<<"]= ";
            cin>>A(i,j);
        }

    transpose(A,At,m,n);

    MatrixXd U(m,m),D(m,n),V(n,n),VT(n,n),ATA;

    U.setZero();
    D.setZero();
    VT.setZero();

    ATA = At * A;

    cout<<"ATA:\n"<<fixEpsilon(ATA)<<endl;

    SelfAdjointEigenSolver<MatrixXd> eigensolver(ATA);

    V = eigensolver.eigenvectors();

    reverse_matrix(V);

    MatrixXd eigenvalues = eigensolver.eigenvalues().matrix();

    vector<long double> a;

    for(int i=0;i<eigenvalues.size();i++)
        if(eigenvalues(i,0) > 1e-9)
            a.push_back(eigenvalues(i,0));

    sort(a.rbegin(),a.rend());

    int pos = a.size();

    for(int i=0;i<a.size();i++)
        D(i,i) = sqrt(a[i]);

    for(int i=0;i<a.size();i++)
    {
        MatrixXd Ui = (1.0/D(i,i)) * A * V.col(i);

        for(int j=0;j<m;j++)
            U(j,i) = Ui(j,0);
    }

    while(pos < m)
    {
        MatrixXd e(m,1);
        e.setZero();
        e(pos,0) = 1;

        MatrixXd Ui = e;

        for(int i=0;i<pos;i++)
        {
            MatrixXd ui = U.col(i);
            ui = (matrixMultiply(e,ui,m) / matrixMultiply(ui,ui,m)) * ui;
            Ui = Ui - ui;
        }

        long double norm = 0;

        for(int i=0;i<m;i++)
            norm += Ui(i,0)*Ui(i,0);

        for(int j=0;j<m;j++)
            U(j,pos) = Ui(j,0)/sqrt(norm);

        pos++;
    }

    cout<<"Matrix U:\n"<<fixEpsilon(U)<<endl;
    cout<<"Matrix D:\n"<<fixEpsilon(D)<<endl;
    cout<<"Matrix V:\n"<<fixEpsilon(V)<<endl;

    transpose(V,VT,n,n);

    cout<<"Matrix VT:\n"<<fixEpsilon(VT)<<endl;

    MatrixXd AA = U * D * VT;

    cout<<"Matrix A = U * D * VT:\n";
    cout<<fixEpsilon(AA)<<endl;

    cout<<"Test A - (U*D*VT):\n";
    cout<<fixEpsilon(AA - A)<<endl;
}
