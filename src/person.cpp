#include <Rcpp.h>
#include "person.h"
#include "sample.h"
#include "string.h"
#include "time.h"

Person::Person(int birth_t, int death_t){
  birth_time = birth_t;
  death_time = death_t;
}

char Person::attribute_sex(double prop_f){
  char s = 'f';
  if(sample_double(0, 1) > prop_f){
    s = 'm';
  }
  return s;
}



