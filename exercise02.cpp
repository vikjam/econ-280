#include <iostream>
#include <random>
#include "plotting.cpp"

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
void compute_statistics(double *ys, int T){
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
    int Tb = 100;
    double ys_b [Tb];
    simulate_ar1(ys_b, Tb, y_mean);
    compute_statistics(ys_b, Tb);
    mat time_b = linspace(0, Tb-1, Tb);
    mat data_b(ys_b, Tb, 1);
    vector<string> labels{"AR(1) simulation"};
    plot(time_b, data_b, vector<int> {1}, labels);

    // Part (c)
    cout << "Part (c)" << endl;
    int Tc = 10000;
    double ys_c [Tc];
    simulate_ar1(ys_c, Tc, y_mean);
    compute_statistics(ys_c, Tc);
    mat time_c = linspace(0, Tc-1, Tc);
    mat data_c(ys_c, Tc, 1);
    plot(time_c, data_c, vector<int> {1}, labels);
    
    return 0;
}
