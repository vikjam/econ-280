#include <iostream>
#include <armadillo>
#include <math.h>
#include "plotting.cpp"
#include "csv_read.cpp"

using namespace std;
using namespace arma;
                        
int main(){
    
    // a. read csv file by Getdata
    string filename = "US_Data.csv";
    cout << "reading " << filename << "..." << endl;
    vector<vector<double>> data_temp = Getdata<double>(filename);
    int T = data_temp.size();
    mat data = zeros(T, 2);
    for (int t = 0; t < T; t++){
        data(t, 0) = log(data_temp[t][0]);
        data(t, 1) = log(data_temp[t][1]);
    }
    mat X = join_rows(ones(T-1, 1),
        join_rows(data.rows(0, T-2), linspace(2, T, T-1)));
    mat param = solve(trans(X)*X, trans(X)*data.submat(1, 0, T-1, 1));
    
    // b.
    mat eps_hat = data.submat(1, 0, T-1, 1) - X*param;
    mat x = linspace(1, T-1, T-1);
    vector<string> labels{"epsilon^y", "epsilon^h"};
    plot(x, eps_hat, vector<int> {1,2}, labels);
    mat sigma_yh = stddev(eps_hat, 1);
    cout << "esitimated standard deviation of error term" << endl;
    sigma_yh.print();
    
    mat autocor_y = cor(eps_hat.submat(1, 0, T-2, 0), eps_hat.submat(0, 0, T-3, 0));
    mat autocor_h = cor(eps_hat.submat(1, 1, T-2, 1), eps_hat.submat(0, 1, T-3, 1));
    cout << "estimated auto correlation of error term of y" << endl;
    autocor_y.print();
    cout << "estimated auto correlation of error termof h" << endl;
    autocor_h.print();

    // c.
    int T_simul = 240;
    int N = 1000;
    
    cube vars = zeros(2, N, T_simul);
    mat Phi = trans(param.rows(1, 2));
    // simulaltion using cube
    for (int t = 1; t < T_simul-1; t++){
        vars.slice(t) = Phi * vars.slice(t-1) + randn(2, N);
    }
    
    // d.
    mat stds_overT = zeros(2, N);

    // compute standard deviation for all n in N
    for (int n = 0; n < N; n++){
        mat temp = vars.subcube(span(), span(n), span());
        stds_overT.col(n) = trans(stddev(trans(temp), 1));
    }
    // standard deviation of standard deviation
    mat stds_overTN = trans(stddev(trans(stds_overT), 1));
    cout << "standard deviation of standard deviation" << endl;
    stds_overTN.print();
    
    return 0;
}

