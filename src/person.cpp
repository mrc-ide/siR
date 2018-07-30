#include <Rcpp.h>
#include <string>
#include "person.h"
#include "helper.h"

Person::Person(){
  age = 0;
  sex = Person::attribute_sex();
}

Person::Person(std::vector<double> &agedist, double prop_f){
  age = weighted_sample(agedist);
  sex = Person::attribute_sex(prop_f);
}

std::string Person::attribute_sex(double prop_f){
  std::string s = "f";
  if(R::runif(0, 1) > prop_f){
    s = "m";
  }
  return s;
}

std::string Person::get_sex() const {
  return sex;
}

double Person::get_age() const {
  return age;
}

