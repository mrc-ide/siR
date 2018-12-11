#ifndef ibm_schedule
#define ibm_schedule

Rcpp::List ibm_scheduled(double sigma, double beta, int N, int i0, int days, int substep,
                         std::vector<double> age_distribution, std::vector<double> life_distribution);

#endif
