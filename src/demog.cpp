#include <Rcpp.h>
#include <string>
#include "demog.h"

std::string Person::attribute_sex(){
  std::string s = "f";
  if(R::runif(0, 1) > 0.5){
    s = "m";
  }
  return s;
}

Person::Person(){
  age = 0;
  sex = Person::attribute_sex();
}

Person::Person(int age, std::string sex){
  age = age;
  sex = sex;
}


std::string Person::get_sex() const {
  return sex;
}

//' @export
// [[Rcpp::export]]
void demog_test(int N){
  std::vector<Person> Pop(N);
  for(int i = 0; i < N; i++){
    Person p1;
    Pop[i] = p1;
  }

  for(int i = 0; i < Pop.size(); i++){
    Rcpp::Rcout << "Person " << i + 1 << std::endl;
    Rcpp::Rcout << "Sex is " << Pop[i].get_sex() << std::endl;
  }

}
