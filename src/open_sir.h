#ifndef sir_test_h
#define sir_test_h

Rcpp::List open_sir_rcpp(int N, int days, int substep,std::vector<double> age_of_death,
                      std::vector<int> birth_times, std::vector<int> death_times);
#endif
