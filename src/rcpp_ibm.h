#ifndef rcpp_ibm_h
#define rcpp_ibm_h

Rcpp::NumericVector seq_rcpp(int t0, int tf, double dt);
Rcpp::List ibm_closed_sir_rcpp(double sigma, double beta, int N, int i0, int t_final, double dt);

#endif
