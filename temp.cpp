#include<bits/stdc++.h>
using namespace std;
  
vector<vector<double>>multiply(vector<vector<double>>&A,vector<vector<double>>&B){
    int n=A.size();
    int  m=B[0].size();
    int p=B.size();
    vector<vector<double>>c(n,vector<double>(m,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<p;k++){
                c[i][j]+=A[i][k]*B[k][j];
            }
        }
    }
    return c;
}
vector<vector<double>>transpose(vector<vector<double>>&A){
    int n=A.size();
    int m=A[0].size();
    vector<vector<double>>T(m,vector<double>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            T[j][i]=A[i][j];
        } 
       }
       return T;
}
vector<vector<double>>identity(int n){
    vector<vector<double>>I(n,vector<double>(n,0));
    for(int i=0;i<n;i++){
        I[i][i]=1.0;
    }
    return I;
}
vector<double>solve(vector<vector<double>>A,vector<double>b){
   int n=A.size();
    for(int i=0;i<n;i++){
        int pivot=i;
    }
    for(int j=i+1;j<n;j++){
        if(abs(A[j][i])>abs(A[pivot][i]))pivot=j;
    }
        swap(A[i],A[pivot]);
        swap(b[i],b[pivot]);

double diag=A[i][i];
for(int j=i;j<n;j++) A[i][j]/=diag;
    b[i]/=diag;


for(int k = i+1; k < n; k++){
            double factor = A[k][i];
            for(int j = i; j < n; j++) A[k][j] -= factor * A[i][j];
            b[k] -= factor * b[i];
        }
    }

    vector<double> x(n);
    for(int i = n-1; i >= 0; i--){
        x[i] = b[i];
        for(int j = i+1; j < n; j++) x[i] -= A[i][j] * x[j];
    }
    return x;
}


