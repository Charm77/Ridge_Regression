#include<bits/stdc++.h>

using namespace std;

double meanSquaredError( const vector<double>& y_true, const vector<double>& y_pred)
{
    double mse=0.0;
    for(size_t i=0; i<y_true.size();i++)
    {
        mse += (y_true[i] - y_pred[i]) * (y_true[i] - y_pred[i]);
    }
    return mse / y_true.size();
}


vector<double> linearRegression(const vector<vector<double>>& X, const vector<double>& y)
{
    int n = X.size();
    int d = X[0].size();

    vector<vector<double>> XtX(d, vector<double>(d, 0));
    vector<double>Xty(d,0);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<d; j++)
        {
            Xty[j] += X[i][j] * y[i];
            for(int k=0; k<d; k++)
            {
                XtX[j][k] += X[i][j] * X[i][k];
            }
        }
    }

    vector<double> w=Xty; 

    for(int i=0; i<d; i++)
    {
        double diag = XtX[i][i];
        for(int j=0; j<d; j++)
        {
            XtX[i][j]/=diag;
        }
        w[i] /= diag;

        for(int k=0; k<d; k++)
        {
            if(k==i)continue;

            double factor= XtX[k][i];

            for(int j=0; j<d; j++)
            {
               XtX[k][j] -= factor * XtX[i][j];
            }
            w[k] -= factor * w[i];
        }
    }
    return w;
    
}



vector<double> ridgeRegression(const vector<vector<double>>& X, const vector<double>& y, double alpha)
{
    int n = X.size();
    int d = X[0].size();

    vector<vector<double>> XtX(d, vector<double>(d, 0));
    vector<double>Xty(d,0);

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<d; j++)
        {
            Xty[j] += X[i][j] * y[i];
            for(int k=0; k<d; k++)
            {
                XtX[j][k] += X[i][j] * X[i][k];
            }
        }
    }

    for(int i=0; i<d; i++)
    {
        XtX[i][i] += alpha;
    }
    
    vector<double> w=Xty;
    for(int i=0; i<d; i++)
    {
        double diag = XtX[i][i];
        for(int j=0; j<d; j++)
        {
            XtX[i][j]/=diag;
        }
        w[i] /= diag;

        for(int k=0; k<d; k++)
        {
            if(k==i)continue;

            double factor= XtX[k][i];

            for(int j=0; j<d; j++)
            {
               XtX[k][j] -= factor * XtX[i][j];
            }
            w[k] -= factor * w[i];
        }
    }
    return w;
} 


int main()
{
    srand(0);
    int n=100;
    vector<vector<double>> X(n, vector<double>(2, 1));

    vector<double> y(n);

    for (int i=0; i<n; i++)
    {
        double xi((rand()%1000) / 1000.0) * 10 - 5;
        X[i][1] = xi;
        y[i] = 2 + 4 * xi +((rand()%1000) / 1000.0) * 10 - 5;
    }

    vector<double> w_lr = linearRegression(X, y);

    vector<double> w_ridge = ridgeRegression(X, y, 10.0);

    vector<double> y_pred_lr(n), y_pred_ridge(n);

    for (int i=0; i<n; i++)
    {
        y_pred_lr[i] = w_lr[0] * X[i][0] + w_lr[1] * X[i][1];
        y_pred_ridge[i]= w_ridge[0] * X[i][0] + w_ridge[1] * X[i][1];
    }
    
    cout << "Linear Regression weigts: Bias=" << w_lr[0] << "Slope=" << w_lr[1] <<endl;
    cout << "Ridge Regression Weights: Bias=" << w_ridge[0] << "Slope=" << w_ridge[1] << endl;
     
    cout << "Linear Regression MSE: " << meanSquaredError(y, y_pred_lr) << endl; 
    cout << "Rdige Regression MSE: " << meanSquaredError(y, y_pred_ridge) << endl; 

    return 0;
}

