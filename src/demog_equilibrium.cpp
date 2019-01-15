#include <Rcpp.h>
#include "sample.h"
#include "demog_equilibrium.h"

//' Draw an age (in days) from the equilibrium age distribution
//'
//' @param age_years Vector of integersof possible age years
//' @param equilibrium_age Equilribrium age distribution
//' @return An integer age (days)
//' @export
// [[Rcpp::export]]
int draw_equilibrium_age(std::vector<int> &age_years, std::vector<double> &equilibrium_age){
  int current_age_year = weighted_sample_int(age_years, equilibrium_age);
  int current_age_day = sample_int(0, 364);
  return(current_age_year * 365 + current_age_day);
}

//' Draw a death age conditional on an age from the equilibrium age distribution
//'
//' @param age Age (days) drawn from equilibrium age distribution
//' @param age_years Vector of integers of possible age years
//' @param age_of_death Equilribrium age of death distribution
//' @param max_age Maximum age (years)
//' @return An integer death age (days)
// [[Rcpp::export]]
int draw_equilibrium_death_age(int age, std::vector<int> &age_years, std::vector<double> age_of_death, int max_age){
  // Initialise variables
  int live_for_years;
  int lifespan;
  // Forcing to integer is equivalent of floor in R
  int year = int(age / 365);
  //Rcpp::Rcout << "year " << year << std::endl;
  int day = age % 365;
  //Rcpp::Rcout << "day " << day << std::endl;

  // How much of current year remains
  double current_year_prob_rescale = (365 - double(day)) / 365;
  // Rescale probability in current year
  //Rcpp::Rcout << "aoda " << age_of_death[year] << std::endl;
  age_of_death[year] = age_of_death[year] * current_year_prob_rescale;
  //Rcpp::Rcout << "aodb " << age_of_death[year] << std::endl;
  // Sample
  if(year == max_age){
    live_for_years = max_age;
  } else {
    live_for_years = weighted_sample_min_int(age_years, age_of_death, year);
    //Rcpp::Rcout << "lfy " << live_for_years << std::endl;
  }

  // If death will occur in current year
  if(live_for_years == year){
    //Rcpp::Rcout << "a " << year << std::endl;
    lifespan = year * 365 + sample_int(day, 365);
  } else {
    //Rcpp::Rcout << "b " << year << std::endl;
    lifespan = live_for_years * 365 + sample_int(1, 365);
  }

  return(lifespan);
}
