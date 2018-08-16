#include <Rcpp.h>
#include "person.h"
#include "helper.h"
#include "string.h"
#include "time.h"

Person::Person(int &t, int &substep, double &prop_f, std::vector<double> &prob_survive, std::vector<double> &prob_death){
  // Birth time
  int year = weighted_sample(prob_survive, 0);
  int day = int(R::runif(1, 366));
  int age =  (year * 365) - day;
  birth_time = t - days_to_steps(age, substep);
  // Rcpp::Rcout << "Birth time = " << birth_time << std::endl;
  // Death time
  //Rcpp::Rcout << "Age day = " << day << std::endl;
  year = weighted_sample(prob_death, year);
  //Rcpp::Rcout << "Death year = " << year << std::endl;
  death_time = birth_time + years_to_steps(year, substep);
  // Rcpp::Rcout << "Death time = " << death_time << std::endl;
  // Sex
  sex = Person::attribute_sex(prop_f);
}

char Person::attribute_sex(double prop_f){
  char s = 'f';
  if(R::runif(0, 1) > prop_f){
    s = 'm';
  }
  return s;
}

void Person::new_birth(int &t, int &substep, double &prop_f, std::vector<double> &prob_death){
  birth_time = t;
  int year = weighted_sample(prob_death, 0);
  int day = int(R::runif(1, 366));
  int lifespan = (year * 365) + day;
  death_time = birth_time + days_to_steps(lifespan, substep);
  sex = Person::attribute_sex(prop_f);
}
