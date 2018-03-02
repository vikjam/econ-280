#include <iostream>
#include <random>

extern "C"{
#include <gnuplot_i.h>
}

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

// plotting function
void plot(double *ys, int T, char *filename, char *title){
    gnuplot_ctrl * g = gnuplot_init();

    gnuplot_cmd(g, "set terminal png");
    gnuplot_cmd(g, filename);
    gnuplot_setstyle(g, "lines");
    gnuplot_plot_x(g, ys, T, title);
    gnuplot_close(g);
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
    plot(ys_b, Tb, "set output \"exercise02_ar1_100.png\"", "AR(1) simulation");

    // Part (c)
    cout << "Part (c)" << endl;
    int Tc = 10000;
    double ys_c [Tc];
    simulate_ar1(ys_c, Tc, y_mean);
    compute_statistics(ys_c, Tc);
    plot(ys_c, Tc, "set output \"exercise02_ar1_10000.png\"", "AR(1) simulation");

    // Plot 
    
    return 0;
}
