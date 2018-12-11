#include <Rcpp.h>
#include "time.h"

//' @export
// [[Rcpp::export]]
int steps(int &days, int &substep){
  return days * substep;
}

//' @export
// [[Rcpp::export]]
int years_to_steps(int &years, int &substep){
  return years * 365 * substep;
}

//' @export
// [[Rcpp::export]]
int days_to_steps(int &days, int &substep){
  return days * substep;
}
