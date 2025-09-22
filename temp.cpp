#include<bits/stdc++.h>
using namespace std;

//Matrix multiplication function:C=A*B
  
vector<vector<double>>multiply(vector<vector<double>>&A,vector<vector<double>>&B){
    int n=A.size();
    int m=B[0].size();
    int p=B.size();
    //Initialize result matrix with Zeros
    vector<vector<double>>C(n,vector<double>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<p;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    return C;
}

//Matrix Transpose function :T=A^T
vector<vector<double>>transpose(vector<vector<double>>&A){
    int n=A.size();
    int m=A[0].size();
    vector<vector<double>>T(m,vector<double>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            T[j][i]=A[i][j];//swap rows and columns
        } 
       }
       return T;
}


//solve linear equation Ax=b using Gaussian elimination

vector<double> solve(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
         int pivot = i;//partial pivoting to avoid numerical errors
        for (int j = i + 1; j < n; j++) {
            if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
        }
        swap(A[i], A[pivot]);
        swap(b[i], b[pivot]);
        //Make pivot element =1
        double diag = A[i][i];
        for (int j = i; j < n; j++) A[i][j] /= diag;
        b[i] /= diag;
       
        //Eliminate other elements in column

        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i];
            for (int j = i; j < n; j++) A[k][j] -= factor * A[i][j];
            b[k] -= factor * b[i];
        }
    }

    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++)
         x[i] -= A[i][j] * x[j];
    }
    return x;
}


int main() 
{
    int n, m;
    cout << "Enter number of samples (n) and features (m): ";
    cin >> n >> m;

    vector<vector<double>> X(n, vector<double>(m+1, 1.0));
    vector<double> y(n);

    cout << "Enter feature matrix row-wise:\n";
    for(int i=0;i<n;i++)
        for(int j=1;j<=m;j++)
            cin >> X[i][j];

    cout << "Enter target values (y):\n";
    for(int i=0;i<n;i++) cin >> y[i];

    double lambda;
    cout << "Enter lambda (regularization parameter): ";
    cin >> lambda;

    vector<vector<double>> Xt = transpose(X);
    vector<vector<double>> XtX = multiply(Xt, X);

    // Add lambda to diagonal (skip intercept)
    for(int i=1;i<XtX.size();i++) XtX[i][i] += lambda;

    // Convert y to column vector for multiplication
    vector<vector<double>> y_col(n, vector<double>(1));
    for(int i=0;i<n;i++) y_col[i][0] = y[i];
    vector<vector<double>> XtY = multiply(Xt, y_col);

    // Convert XtY to 1D vector for solve
    vector<double> XtY_vec(m+1);
    for(int i=0;i<=m;i++) XtY_vec[i] = XtY[i][0];

    vector<double> beta = solve(XtX, XtY_vec);

    cout << "\nRidge Regression Coefficients (beta):\n";
    for(double val : beta) cout << val << " ";
    cout << endl;

    return 0;    

}
