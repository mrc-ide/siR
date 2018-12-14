#include <Rcpp.h>
#include "sample.h"

//' Sample single integer from range.
//'
//' @param from Starting integer (inclusive)
//' @param to End integer (inclusive)
//' @export
// [[Rcpp::export]]
int sample_integer(int from, int to){
  return int(R::runif(from, to + 1));
}

//' Sample single double from range.
//'
//' @param from Starting double (inclusive)
//' @param to End double (inclusive)
//' @export
// [[Rcpp::export]]
double sample_double(double from, double to){
  return R::runif(from, to);
}

//' @export
// [[Rcpp::export]]
int weighted_sample_int(std::vector<int> &x, std::vector<double> &weights){
  double sum_of_weight = 0;
  for(unsigned int i = 0; i < weights.size(); i++) {
    sum_of_weight += weights[i];
  }

  double rnd = sample_double(0, sum_of_weight);
  for(unsigned int i = 0; i < weights.size(); i++) {
    if(rnd < weights[i])
      return x[i];
    rnd -= weights[i];
  }
  assert(!"should never get here");
  return 1;
}

//' @export
// [[Rcpp::export]]
double weighted_sample_double(std::vector<double> &x, std::vector<double> &weights){
  double sum_of_weight = 0;
  for(unsigned int i = 0; i < weights.size(); i++) {
    sum_of_weight += weights[i];
  }

  double rnd = sample_double(0, sum_of_weight);
  for(unsigned int i = 0; i < weights.size(); i++) {
    if(rnd < weights[i])
      return x[i];
    rnd -= weights[i];
  }
  assert(!"should never get here");
  return 1;
}
