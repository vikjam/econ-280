/**
 * @Author: Shunsuke Hori
 * @Date:   2018-02-17T08:48:03-08:00
 * @Filename: exercise02.cpp
 * @Last modified by:   Shunsuke Hori
 * @Last modified time: 2018-02-17T20:11:22-08:00
 */

#include <iostream>
#include <random>

using namespace std;

random_device seed_gen;
default_random_engine engine(seed_gen());
normal_distribution<> dist(0.0, 0.46);

// simulate ar1 process
void simulate_ar1(double *ys, int T, double y_init){
    ys[0] = y_init;
    for (int i = 1; i < T; i++){
        ys[i] = 0.21 + 0.75*ys[i-1] + dist(engine);
    }
}

// compute mean of ys
double mean(double *ys, int T){
    double sum = 0.0;
    for (int i = 0; i < T; i++){
        sum = sum + ys[i];
    }
    return sum/T;
}

// compute autocovariance of ys
double autocov(double *ys, int T, double average){
    double sum = 0;
    for (int i = 1; i < T; i++){
        sum = sum + (ys[i] - average)*(ys[i-1] - average);
    }
    return sum/(T-1);
}

//  compute average and autocovariance of ys
void compute_statistics(int T, double init){
    double ys [T];
    simulate_ar1(ys, T, init);
    double average_y = mean(ys, T);
    cout << "average of simulated y is " << average_y << endl;
    double autocov_y = autocov(ys, T, average_y);
    cout << "autocovariance of simulated y is " << autocov_y << endl;
}

int main(){

    double y_mean = 0.21/0.25;
    cout << "theoretical mean is " << y_mean << endl;

    // Part (b)
    cout << "Part (b)" << endl;
    compute_statistics(100, y_mean);

    // Part (c)
    cout << "Part (c)" << endl;
    compute_statistics(10000, y_mean);

    return 0;
}
