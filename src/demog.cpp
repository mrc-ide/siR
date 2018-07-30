#include <Rcpp.h>
#include <string>
#include "demog.h"
#include "person.h"
#include "helper.h"

//' @export
// [[Rcpp::export]]
void demog_test(int N, Rcpp::NumericVector ad){
  std::vector<double> agedist = Rcpp::as< std::vector<double> >(ad);

  std::vector<Person> Pop(N);
  for(int i = 0; i < N; i++){
    Person p1 = Person(agedist, 0.5);
    Pop[i] = p1;
  }

  // for(unsigned int i = 0; i < Pop.size(); i++){
  //   Rcpp::Rcout << "Person " << i + 1 << std::endl;
  //   Rcpp::Rcout << "Sex is " << Pop[i].get_sex() << std::endl;
  //   Rcpp::Rcout << "Age is " << Pop[i].get_age() << std::endl;
  // }

}
