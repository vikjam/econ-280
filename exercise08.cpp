#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

double pi(int s, int a, int ap, double w, double gamma){
    double pi_val = min(s, ap) - w*ap - gamma*pow(ap-a, 2);
    return pi_val;
}

double pi2(int s, int a, int ap, double w, double gamma){
    double pi_val = min(s, ap) - w*ap - gamma*pow(min(ap-a, 0), 2);
    return pi_val;
}

int main(){
    const double w = 0.7;
    const double gamma = 0.1;
    const double beta = 0.95;
    const int s_size = 20;
    const mat s_grid = linspace(0, 19, s_size);
    const mat P = ones(s_size, s_size)/s_size;
    const mat a_grid = linspace(0, 19, s_size);
    const double tol = 1e-8;
    const int max_iter = 1e3;
    double dif = 1.0;

    mat obj = zeros(s_size);
    mat v = zeros(s_size, s_size);
    mat v_n = v;
    mat a_opt = zeros(s_size, s_size);
    for (int iter = 0; iter < max_iter; iter++){
        for (int i_a = 0; i_a < s_size; i_a++){
            for (int i_s = 0; i_s < s_size; i_s++){
              for (int i_ap = 0; i_ap < s_size; i_ap++){
                  obj(i_ap) = pi(s_grid(i_s), a_grid(i_a), a_grid(i_ap), w, gamma)
                              + beta * dot(P.row(i_s), v.row(i_a));
              }
              v_n(i_a, i_s) = obj.max();
              a_opt(i_a, i_s) = obj.index_max();
            }
        }
        dif = max(abs(v_n - v), 1).max();
        cout << "iteration = " << iter << ": dif = " << dif << endl;
        if (dif < tol){
            cout << "converged" << endl;
            break;
        }
        v = v_n;
    }
    a_opt.save("a_opt.csv", csv_ascii);
    v.save("v.csv", csv_ascii);
    return 0;

}
