#include <iostream>
#include <armadillo>
#include "plotting.cpp"
#include "csv_read.cpp"

using namespace std;
using namespace arma;

// The function for part a. and b.
mat calculate_H_loop(double lambda, int T){
    mat H = zeros<mat>(T, T);
    for (int t = 0; t < T; t++){
        if (t == 0){
            H(t, 0) = 1+lambda;
            H(t, 1) = -2*lambda;
            H(t, 2) = lambda;
        }
        else if (t == 1){
            H(t, 0) = -2*lambda;
            H(t, 1) = 1+5*lambda;
            H(t, 2) = -4*lambda;
            H(t, 3) = lambda;
        }
        else if (t == T-2){
            H(t, T-4) = lambda;
            H(t, T-3) = -4*lambda;
            H(t, T-2) = 1+5*lambda;
            H(t, T-1) = -2*lambda;
        }
        else if (t == T-1){
            H(t, T-3) = lambda;
            H(t, T-2) = -2*lambda;
            H(t, T-1) = 1+lambda;
        }
        else{ 
            H(t, t-2) = lambda;
            H(t, t-1) = -4*lambda;
            H(t, t) = 1+6*lambda;
            H(t, t+1) = -4*lambda;
            H(t, t+2) = lambda;
        }
    }
    return H;
}
int main(){

    // c. Apply HP-filter
    string filename = "US_Data.csv";
    vector<vector<double>> data = Getdata<double>(filename);
    int T = data.size(); 
    mat y(T, 1);
    for (int t = 0; t<T; t++)
        y(t, 0) = data[t][0];
    
    mat logy = log(y);
    mat H1600 = calculate_H_loop(1600.0, T);
    mat logytr1600 = solve(H1600, logy);
    mat H100000 = calculate_H_loop(100000, T);
    mat logytr100000 = solve(H100000, logy);
    
    // Plot
    mat time = linspace(0, T-1, T);
    vector<string> labels_c{"lambda = 1,600", "lambda = 100,000", "raw value"};
    plot(time, join_rows(join_rows(logytr1600, logytr100000), logy), 
        vector<int> {1, 2, 3}, labels_c, "log of real GDP");
    
    // d.
    mat yc1600 = y - exp(logytr1600);
    mat yc100000 = y - exp(logytr100000);
    vector<string> labels_d{"lambda = 1,600", "lambda = 100,000"};
    plot(time, join_rows(yc1600, yc100000), 
        vector<int> {1, 2}, labels_c, "cyclical component of real GDP");
    return 0;
}
