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