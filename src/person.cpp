#include <Rcpp.h>
#include <string>
#include "person.h"
#include "helper.h"

Person::Person(double &t){
  birth_time = t;
  sex = Person::attribute_sex();
  death_time = t + 10;
}

Person::Person(double &t, std::vector<double> &agedist, double prop_f){
  birth_time = t - weighted_sample(agedist);
  sex = Person::attribute_sex(prop_f);
  death_time = t + 10;
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

double Person::get_age(double &t) const {
  return t - birth_time;
}

double Person::get_death_time() const {
  return death_time;
}


