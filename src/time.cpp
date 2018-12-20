#include <Rcpp.h>
#include "time.h"

//' Convert years to steps
//'
//' @param years Number of years
//' @param substep Substeps per day
//' @export
// [[Rcpp::export]]
int years_to_steps(const int years, const int substep){
  return years * 365 * substep;
}

//' Convert days to steps
//'
//' @param days Number of days
//' @param substep Substeps per day
//' @export
// [[Rcpp::export]]
int days_to_steps(const int days, const int substep){
  return days * substep;
}
