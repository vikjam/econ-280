#include <iostream>
#include <armadillo>
#include <math.h>
#include "plotting.cpp"
#include "csv_read.cpp"

using namespace std;
using namespace arma;
                                         
int main(){
    vector<vector<double>> data;

    string filename = "US_Data.csv";
    
    // a. read csv file by Getdata
    cout << "reading " << filename << "..." << endl;
    data = Getdata<double>(filename);

    // b. plot log of two data
    int T = data.size(); 
    mat logdata(T, 2);
    for (int t = 0; t<T; t++){
        logdata(t, 0) = log(data[t][0]);
        logdata(t, 1) = log(data[t][1]);
    }
    mat time = linspace(0, T-1, T);
    vector<string> labels{"Real GDO", "Hours"};
    plot(time, logdata, vector<int> {1, 2}, labels);


    // c.
    mat y = exp(logdata.col(0));
    mat X = ones<mat>(T, 2);
    X.col(1) = linspace(1, T, T);
    mat param = solve(trans(X)*X, trans(X)*y);
    cout << "estimated coefficients" << endl;
    param.print();

    // d.
    mat y_tr = X*param;
    vector<string> labels_d{"raw GDP data", "trend component"};
    plot(time, join_rows(y, y_tr), vector<int> {1, 2}, labels_d);
    
    // e.
    mat y_c = y - y_tr;
    vector<string> label{"cyclical component"};
    plot(time, y_c, vector<int> {1}, label);

    cout << "standard deviation of cyclical component is " << stddev(y_c, 0) << endl;
    cout << "Frst-order autocorrelation ofcyclical component is " << cor(y_c.rows(1, T-1), y_c.rows(0, T-2)) << endl;

    cin.get();

    return 0;
}