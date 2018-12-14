#include <Rcpp.h>
#include "sample.h"
#include "demog_equilibrium.h"

//' Draw an age (in days) from the equilibrium age distribution
//'
//' @param age_year Vector of integersof possible age years
//' @param equilibrium_age Equilribrium age distribution
//' @return An integer age (days)
//' @export
// [[Rcpp::export]]
int draw_equilibrium_age(std::vector<int> &age_years, std::vector<double> &equilibrium_age){
  int current_age_year = weighted_sample_int(age_years, equilibrium_age);
  int current_age_day = sample_int(0, 364);
  return(current_age_year * 365 + current_age_day);
}
