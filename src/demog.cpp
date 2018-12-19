#include <Rcpp.h>
#include <string>
#include <cmath>
#include "demog.h"
#include "person.h"
#include "sample.h"
#include "time.h"
#include "demog_equilibrium.h"

//' @export
// [[Rcpp::export]]
Rcpp::List demog_test(int N, int days, int substep, std::vector<double> age_of_death, std::vector<double> equilibrium_age){

  // Maximum time steps
  int maxt = steps(days, substep);

  // Initialise demog vars
  int equil_age;
  int equil_death;

  // Initialise vector of age years
  std::vector<int> age_years(90);
  for(unsigned int i = 0; i < 90; i++){
    age_years[i] = i;
  }

  // Death tracker
  std::vector<int> deaths(maxt);
  int cur_death;
  int year_death;
  int day_death;

  // Population
  std::vector<Person> Pop;
  Pop.reserve(N);

  // Populate Pop vector
  for(int i = 0; i < N; i++){
    //Rcpp::Rcout << i << std::endl;
    equil_age = draw_equilibrium_age(age_years, equilibrium_age);
    //Rcpp::Rcout << "ea " << equil_age << std::endl;
    equil_death = draw_equilibrium_death_age(equil_age, age_years, age_of_death, 89);
    //Rcpp::Rcout << "ed " << equil_death << std::endl;
    // New person
    Person np = Person(-equil_age, equil_death - equil_age);
    // Add to pop vector
    Pop.push_back(np);
  }

  // Cycle through time steps
  for(int t = 0; t < maxt-1; t++){
    // Reset death counter for current timestep
    cur_death = 0;
    // Cycle through people
    for(int p = 0; p < N; p++){
      // If person dies
      if(Pop[p].death_time == t){
        // Record death
        cur_death ++;
        // Draw age of death for new person
        year_death = weighted_sample_int(age_years, age_of_death);
        day_death = sample_int(0, 364);
        // Replace with new person
        Person np = Person(t, t + year_death * 365 + day_death);
        Pop[p] = np;
      }
    }
    // Record deaths in timestep
    deaths[t] = cur_death;
  }

  Rcpp::NumericVector deaths_out = Rcpp::wrap(deaths);

  return Rcpp::List::create(
    Rcpp::Named("deaths") = deaths_out);
}



