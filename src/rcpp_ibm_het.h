#ifndef rcpp_ibm_het_h
#define rcpp_ibm_het_h

Rcpp::List ibm_het(double sigma, double beta, int N, int i0, Rcpp::NumericVector times, double dt, bool het,
                   std::vector<double> age_distribution, std::vector<double> life_distribution);

#endif
