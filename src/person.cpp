#include <Rcpp.h>
#include "person.h"
#include "sample.h"
#include "string.h"
#include "time.h"

Person::Person(int birth_t, int death_t){
  birth = birth_t;
  death = death_t;
}

char Person::attribute_sex(double prop_f){
  char s = 'f';
  if(R::runif(0, 1) > prop_f){
    s = 'm';
  }
  return s;
}



