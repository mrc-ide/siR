#include <Rcpp.h>
#include "helper.h"

//' @export
// [[Rcpp::export]]
double weighted_sample(std::vector<double> &weights){
  double sum_of_weight = 0;
  for(unsigned int i = 0; i < weights.size(); i++) {
    sum_of_weight += weights[i];
  }

  double rnd = R::runif(0, sum_of_weight);
  for(unsigned int i = 0; i < weights.size(); i++) {
    if(rnd < weights[i])
      return i;
    rnd -= weights[i];
  }
  assert(!"should never get here");
  return 1.0;
}

//' @export
// [[Rcpp::export]]
std::vector<double> seq_cpp(double from, double to, double by){
  std::vector<double> outseq;
  double cur = from;
  outseq.push_back(cur);

  while(cur <= (to - by)){
    cur += by;
    outseq.push_back(cur);
  }

  return outseq;
}


