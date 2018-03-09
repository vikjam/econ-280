
#include <iostream>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

using namespace std;

struct model_params{
    double alpha;
    double beta;
    double delta;
    double theta;
    double g;
};

int model_f (const gsl_vector * x, void *params, 
              gsl_vector * f){
    double alpha = ((struct model_params *) params) -> alpha;
    double beta = ((struct model_params *) params) -> beta;
    double delta = ((struct model_params *) params) -> delta;
    double theta = ((struct model_params *) params) -> theta;
    double g = ((struct model_params *) params) -> g;
  
    const double H = gsl_vector_get (x, 0);
    const double K = gsl_vector_get (x, 1);
  
    const double y0 = theta*(pow(K, 1-alpha)*pow(H, alpha)+(1-delta)*K-(1-g)*K)/(1-H)-alpha*pow(K, 1-alpha)*pow(H, alpha-1);
    const double y1 = beta/(1+g)*((1-alpha)*pow(K, -alpha)*pow(H, alpha)+1-delta)-1;
  
    gsl_vector_set (f, 0, y0);
    gsl_vector_set (f, 1, y1);
  
    return GSL_SUCCESS;
}


int print_state (size_t iter, gsl_multiroot_fsolver * s){
    cout << "iter = " << iter << 
          " x = " << 
          gsl_vector_get (s->x, 0) << ", " <<
          gsl_vector_get (s->x, 1) << ", " <<
          "f(x) = " <<
          gsl_vector_get (s->f, 0) << ", " <<
          gsl_vector_get (s->f, 1) << endl;
}

double compute_Y(const double alpha = 0.667, const double beta = 0.984,
                 const double delta = 0.025, const double theta = 3.48,
                 const double g = 0.04){

    const gsl_multiroot_fsolver_type *T;
    gsl_multiroot_fsolver *s;
  
    int status;
    size_t i, iter = 0;
  
    const size_t n = 2;
    struct model_params  p = {alpha, beta, delta, theta, g};
    gsl_multiroot_function f = {&model_f, n, &p};

    double x_init[2] = {0.1, 1.5};
    gsl_vector *x = gsl_vector_alloc (n);

    gsl_vector_set (x, 0, x_init[0]);
    gsl_vector_set (x, 1, x_init[1]);

    T = gsl_multiroot_fsolver_hybrids;
    s = gsl_multiroot_fsolver_alloc (T, 2);
    gsl_multiroot_fsolver_set (s, &f, x);

    
    do{
        iter++;
        status = gsl_multiroot_fsolver_iterate (s);

    
        if (status)   /* check if solver is stuck */
            break;

        status = gsl_multiroot_test_residual (s->f, 1e-7);
    }
    while (status == GSL_CONTINUE && iter < 1000);

    
    const double H = gsl_vector_get (s->x, 0); 
    const double K = gsl_vector_get (s->x, 1);

    gsl_multiroot_fsolver_free (s);
    gsl_vector_free (x);

    // b.
    const double Y = pow(K, 1-alpha)*pow(H, alpha);

    return Y;

}

int main (void){

    // a.
    const gsl_multiroot_fsolver_type *T;
    gsl_multiroot_fsolver *s;
  
    int status;
    size_t i, iter = 0;
  
    const size_t n = 2;
    const double alpha = 0.667;
    const double beta = 0.984;
    const double delta = 0.025;
    const double theta = 3.48;
    const double g = 0.04;
    struct model_params  p = {alpha, beta, delta, theta, g};
    gsl_multiroot_function f = {&model_f, n, &p};

    double x_init[2] = {0.1, 1.5};
    gsl_vector *x = gsl_vector_alloc (n);

    gsl_vector_set (x, 0, x_init[0]);
    gsl_vector_set (x, 1, x_init[1]);

    T = gsl_multiroot_fsolver_hybrids;
    s = gsl_multiroot_fsolver_alloc (T, 2);
    gsl_multiroot_fsolver_set (s, &f, x);

    print_state (iter, s);

    do{
        iter++;
        status = gsl_multiroot_fsolver_iterate (s);

        print_state (iter, s);

        if (status)   /* check if solver is stuck */
            break;

        status = gsl_multiroot_test_residual (s->f, 1e-7);
    }
    while (status == GSL_CONTINUE && iter < 1000);

    cout << "status = " << gsl_strerror (status) << endl;

    const double H = gsl_vector_get (s->x, 0); 
    const double K = gsl_vector_get (s->x, 1);
    const double C = pow(K, 1-alpha)*pow(H, alpha)+(1-delta)*K-(1-g)*K;

    gsl_multiroot_fsolver_free (s);
    gsl_vector_free (x);

    cout << "--- RESULT ---" << endl;
    cout << "C = " << C << endl;
    cout << "H = " << H << endl;
    cout << "K = " << K << endl;

    // b.
    cout << "let's see how alpha affects steady state output" << endl;
    const double Y_high_alpha = compute_Y(0.7);
    const double Y_low_alpha = compute_Y(0.6);
    cout << "Y with alpha = 0.7 is " << Y_high_alpha << endl;
    cout << "Y with alpha = 0.6 is " << Y_low_alpha << endl;

    return 0;
}
