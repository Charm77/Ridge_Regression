// ridge_lambda_effect.cpp
#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

// Ridge Regression using Normal Equation
VectorXd ridge_regression(const MatrixXd &X, const VectorXd &y, double lambda) {
    int n_features = X.cols();
    MatrixXd I = MatrixXd::Identity(n_features, n_features);
    I(0,0) = 0; // do not regularize bias
    return (X.transpose() * X + lambda * I).ldlt().solve(X.transpose() * y);
}

int main() {
    srand(42);
    int n = 100;
    VectorXd X = 2 * VectorXd::Random(n).array().abs();
    VectorXd noise = VectorXd::Random(n) * 2;
    VectorXd y = 4 + 3 * X.array() + noise.array();

    // Add bias column
    MatrixXd X_b(n, 2);
    X_b << VectorXd::Ones(n), X;

    // Train/test split (80/20)
    int split = int(0.8 * n);
    MatrixXd X_train = X_b.topRows(split);
    MatrixXd X_test  = X_b.bottomRows(n - split);
    VectorXd y_train = y.head(split);
    VectorXd y_test  = y.tail(n - split);

    vector<double> lambdas = {0, 0.1, 1, 10, 100};
    cout << "Lambda | Train MSE | Test MSE\n";

    for(double lam : lambdas) {
        VectorXd theta = ridge_regression(X_train, y_train, lam);
        VectorXd y_train_pred = X_train * theta;
        VectorXd y_test_pred  = X_test * theta;

        double train_mse = (y_train - y_train_pred).squaredNorm() / y_train.size();
        double test_mse  = (y_test  - y_test_pred ).squaredNorm() / y_test.size();

        cout << lam << " | " << train_mse << " | " << test_mse << "\n";
    }
    return 0;
}
