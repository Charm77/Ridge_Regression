#include<bits/stdc++.h>
using namespace std;
  int n,m,p,i,j,k;
vector<vector<double>>multiply(vector<double>>&A,vector<vector<double>>&B){
     n=A.size();
     m=B[0].size();
     p=B.size();
    vector<vector<double>>C(n,vector<double>(m,0));
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            for(k=0;k<p;k++){
                c[i][j]+=A[i][k];*B[k][j];
            }
        }
    }
    return C;
}
vector<vector<double>>transpose(vector<vector<double>>&A){
    n=A.size();
    m=A[0].size();
    vector<vector<double>>T(m,vector<double>(n));
    for(i=0;i<n;i++){
        for(j=0;j<m;j++){
            T[j][i]=A[i][j];
        } 
       }
       return T;
}
vector<vector<double>>identity(n){
    vector<vector<double>>I(n,vector<double>(n,0));
    for(i=0;i<n;i++){
        I[i][j]=1.0;
    }
    return I;
}
