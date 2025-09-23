// ridge_lambda_effect.cpp
#include <bits/stdc++.h>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

// Ridge Regression using Normal Equation
VectorXd ridge_regression(const MatrixXd &X, const VectorXd &y, double lambda) {
    int n_features = X.cols();
    MatrixXd I = MatrixXd::Identity(n_features, n_features);
    I(0,0) = 0; // do not regularize bias term
    // Solve (XᵀX + λI)θ = Xᵀy
    return (X.transpose() * X + lambda * I).ldlt().solve(X.transpose() * y);
}

int main() {
    srand(42); // fix random seed for reproducibility
    cout << "Random seed fixed at 42\n";

    int n = 100; // number of data points
    VectorXd X = 2 * VectorXd::Random(n).array().abs(); // input feature
    VectorXd noise = VectorXd::Random(n) * 2; // noise term
    VectorXd y = 4 + 3 * X.array() + noise.array(); // true relation: y = 4 + 3x + noise

    // bias column addition (1 for intercept term)
    MatrixXd X_b(n, 2);
    X_b << VectorXd::Ones(n), X;

    // Train/test split (80/20)
    int split = int(0.8 * n);
    MatrixXd X_train = X_b.topRows(split);
    MatrixXd X_test  = X_b.bottomRows(n - split);
    VectorXd y_train = y.head(split);
    VectorXd y_test  = y.tail(n - split);

    // Different regularization strengths
    vector<double> lambdas = {0, 0.1, 1, 10, 100};
    cout << "Lambda | Train MSE | Test MSE | Coefficients (bias, slope)\n";

    for(double lam : lambdas) {
        VectorXd theta = ridge_regression(X_train, y_train, lam);
        VectorXd y_train_pred = X_train * theta;
        VectorXd y_test_pred  = X_test * theta;

        double train_mse = (y_train - y_train_pred).squaredNorm() / y_train.size();
        double test_mse  = (y_test  - y_test_pred ).squaredNorm() / y_test.size();

        // print lambda, errors, and learned coefficients
        cout << lam << " | " << train_mse << " | " << test_mse
             << " | [" << theta(0) << ", " << theta(1) << "]\n";
    }

    cout << "Note: As lambda increases, coefficients shrink towards zero.\n";
    return 0;
}
