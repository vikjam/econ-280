#include <iostream>
#include <math.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

struct model_params{
    double alpha;
    double beta;
    double delta;
    double theta;
    double g;
};

int model_f(const gsl_vector * var, void *params, gsl_vector * f){
    double alpha = ((struct model_params *) params) -> alpha;
    double beta = ((struct model_params *) params) -> beta;
    double delta = ((struct model_params *) params) -> delta;
    double theta = ((struct model_params *) params) -> theta;
    double g = ((struct model_params *) params) -> g;

    const double C = gsl_vector_get (var, 0);
    const double H = gsl_vector_get (var, 1);
    const double K = gsl_vector_get (var, 2);

    const double y0 = theta*C/(1-H)-alpha*pow(K, 1-alpha)*pow(H, alpha-1);
    const double y1 = beta/(1+g)*((1-alpha)*pow(K, -alpha)*pow(H, alpha)+1-delta)-1;
    const double y2 = pow(K, 1-alpha)*pow(H, alpha)+(1-delta)*K-C-(1-g)*K;

    gsl_vector_set(f, 0, y0);
    gsl_vector_set(f, 0, y1);
    gsl_vector_set(f, 0, y2);
}

int main(){
    const gsl_multiroot_fsolver_type *T;
    gsl_multiroot_fsolver *s;

    int status;
    size_t i, iter = 0;

    const size_t n = 3;
    struct model_params p = {0.667, 0.984, 0.025, 3.48, 0.04};
    gsl_multiroot_function f = {&model_f, n, &p};

    double x_init[3] = {1.0, 1.0, 1.0};
    gsl_vector *x = gsl_vector_alloc (n);

    gsl_vector_set (x, 0, x_init[0]);
    gsl_vector_set (x, 1, x_init[1]);
    gsl_vector_set (x, 2, x_init[2]);

    T = gsl_multiroot_fsolver_hybrids;
    s = gsl_multiroot_fsolver_alloc (T, 3);

    return 0;
}

