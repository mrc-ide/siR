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

//' Sample single integer from vector with probability weights.
//'
//' @param x Vector of integers to sample from
//' @param weights Vector of weights
//' @return Probability weighted sample
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

//' Sample single double from vector with probability weights.
//'
//' @param x Vector of integers to sample from
//' @param weights Vector of weights
//' @return Probability weighted sample
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


//' Sample single integer from vector with probability weights conditional on
//' minimum lower bound.
//'
//' @param x Vector of integers to sample from (must be ordered)
//' @param weights Vector of weights
//' @param lower Lower value of x that must be exceeded
//' @return Probability weighted sample
//' @export
// [[Rcpp::export]]
int weighted_sample_min_int(std::vector<int> &x, std::vector<double> &weights, int lower){
  unsigned int start_i = 0;
  while(x[start_i] < lower){
    start_i++;
    if(start_i > x.size()){
      throw std::logic_error("Lower greater than all values in x");
    }
  }

  double sum_of_weight = 0;
  for(unsigned int i = start_i; i < weights.size(); i++) {
    sum_of_weight += weights[i];
  }

  double rnd = sample_double(0, sum_of_weight);
  for(unsigned int i = start_i; i < weights.size(); i++) {
    if(rnd < weights[i])
      return x[i];
    rnd -= weights[i];
  }
  throw std::logic_error("should never get here");
  return 1;
}

//' Sample single double from vector with probability weights conditional on
//' minimum lower bound.
//'
//' @param x Vector of integers to sample from (must be ordered)
//' @param weights Vector of weights
//' @param lower Lower value of x that must be exceeded
//' @return Probability weighted sample
//' @export
// [[Rcpp::export]]
double weighted_sample_min_double(std::vector<double> &x, std::vector<double> &weights, int lower){
  unsigned int start_i = 0;
  while(x[start_i] < lower){
    start_i++;
    if(start_i > x.size()){
      throw std::logic_error("Lower greater than all values in x");
    }
  }

  double sum_of_weight = 0;
  for(unsigned int i = start_i; i < weights.size(); i++) {
    sum_of_weight += weights[i];
  }

  double rnd = sample_double(0, sum_of_weight);
  for(unsigned int i = start_i; i < weights.size(); i++) {
    if(rnd < weights[i])
      return x[i];
    rnd -= weights[i];
  }
  throw std::logic_error("should never get here");
  return 1;
}
