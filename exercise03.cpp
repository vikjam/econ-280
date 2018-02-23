/**
 * @Author: Shunsuke Hori
 * @Date:   2018-02-22T20:20:52-08:00
 * @Filename: exercise03.cpp
 * @Last modified by:   Shunsuke Hori
 * @Last modified time: 2018-02-22T20:45:47-08:00
 */

#include <iostream>
#include <math.h>
#include <armadillo>

using namespace std;
using namespace arma;

int main(){

    const int p = 2;
    const int T = 25;
    const double c = 0.5;
    const double phi1 = 0.5;
    const double phi2 = 0.3;

    // solution of characteristic function
    mat lambda;
    lambda << (phi1+sqrt(pow(phi1, 2.) + 4*phi2))/2 << endr
           << (phi1-sqrt(pow(phi1, 2.) + 4*phi2))/2 << endr;

    // constant term
    double mu = c/as_scalar(prod(ones(p, 1) - lambda, 0));

    // MA coefficients
    mat omega = pow(lambda, p-1)/(p*lambda-as_scalar(sum(lambda)));
    mat temp = zeros(p, T+1);
    for (int t = 0; t < T+1; t++)
      temp.col(t) = pow(lambda, t);
    mat psi = sum(omega.t() * temp, 0);

    // compute path
    mat epsilon = eye(T+1, T+1);
    mat y = mu + epsilon*psi.t();

    cout << "y by MA process" << endl;
    y.print();

    // compute path by AR(2)
    double y_ar2 [T+1];
    y_ar2[0] = c + phi1*mu + phi2*mu + 1;
    y_ar2[1] = c + phi1*y_ar2[0] + phi2*mu;
    for (int t = 2; t < T+1; t++)
        y_ar2[t] = c + phi1*y_ar2[t-1] + phi2*y_ar2[t-2];

    cout << "y by AR(2) process" << endl;
    for (int i = 0; i < T+1; i++)
        cout << y_ar2[i] << endl;

    cin.get();
 }
