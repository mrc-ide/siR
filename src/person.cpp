#include <Rcpp.h>
#include "person.h"
#include "helper.h"
#include "string.h"

Person::Person(double &time, double &prop_f, std::vector<double> &prob_survive, std::vector<double> &prob_death){
  // Draw year age
  int age = weighted_sample(prob_survive, 0);
  //Rcpp::Rcout << "Current_age = " <<  age << std::endl;
  // Draw day age
  //int day = int(R::runif(1, 366));

  birth_date = time - age;
  int death_age = weighted_sample(prob_death, age);
  //Rcpp::Rcout << "Age of death = " << death_age << std::endl;
  //Rcpp::Rcout << "Years to live = " << death_age - age << std::endl;
  lifespan = death_age - age;//(death_age * 365 + day) - (365 * age + day) ;
  //Rcpp::Rcout << "ls " << (lifespan - day) / 365 << std::endl;
  sex = Person::attribute_sex(prop_f);
}

std::string Person::attribute_sex(double prop_f){
  std::string s = "f";
  if(R::runif(0, 1) > prop_f){
    s = "m";
  }
  return s;
}

void Person::new_birth(double &time, double &prop_f, std::vector<double> &prob_death){
  birth_date = time;

  // Draw day age
  //int day = int(R::runif(1, 366));
  lifespan = weighted_sample(prob_death, 0);// * 365 + day;
  //Rcpp::Rcout << "NEw person ls = " <<  lifespan  << std::endl;
  sex = Person::attribute_sex(prop_f);
}
