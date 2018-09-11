#include <Rcpp.h>
#include "person.h"
#include "helper.h"
#include "string.h"
#include "time.h"

Person::Person(int &t, int &substep, double &prop_f, std::vector<double> &age_dist, std::vector<double> &prob_death){
  // Birth time
  int year = weighted_sample(age_dist, 0);
  int day = int(R::runif(0, 365));
  int age =  (year * 365) - day;
  birth_time = t - days_to_steps(age, substep);
  // Death time
  year = weighted_sample(prob_death, year);
  death_time = birth_time + years_to_steps(year, substep);
  // Sex
  sex = Person::attribute_sex(prop_f);
  heterogeneity = 1.0;
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
  int day = int(R::runif(0, 365));
  int lifespan = (year * 365) + day;
  death_time = birth_time + days_to_steps(lifespan, substep);
  sex = Person::attribute_sex(prop_f);
  heterogeneity = 1.0;
}
