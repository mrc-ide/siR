#include <Rcpp.h>
#include <string>
#include <cmath>
#include "demog.h"
#include "person.h"
#include "sample.h"
#include "time.h"
#include "demog_equilibrium.h"

//' Test demography
//'
//' @param N Population size
//' @param days Simulation time (days)
//' @param substep Substeps per day
//' @param age_of_death Probability of age of death
//' @param equilibrium_age Equilibrium age distribution
//' @export
// [[Rcpp::export]]
Rcpp::List demog_test(int N, int days, int substep, std::vector<double> age_of_death, std::vector<double> equilibrium_age){

  // Maximum time steps
  int maxt = days_to_steps(days, substep);

  // Initialise demog vars
  int equil_age;
  int equil_death;

  // Initialise vector of age years
  std::vector<int> age_years(90);
  for(unsigned int i = 0; i < 90; i++){
    age_years[i] = i;
  }

  // Deaths
    // Tracking
  std::vector<int> deaths(maxt);
  int year_death;
  int day_death;
    // Scheduling
  std::vector<std::vector<int > > death_scheduler(maxt);

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
    // Schedule their death (Adjust for step size?)
    death_scheduler[np.death_time].push_back(i);
  }

  // Cycle through time steps
  for(int t = 0; t < maxt-1; t++){
    // Record deaths in timestep
    deaths[t] = death_scheduler[t].size();
    if(death_scheduler[t].size() > 0){
      for(int d = 0; d < death_scheduler[t].size(); d++){
        // Draw for new person
        year_death = weighted_sample_int(age_years, age_of_death);
        day_death = sample_int(0, 364);
        // Replace with new person
        Person np = Person(t, t + year_death * 365 + day_death);
        Pop[death_scheduler[t][d]] = np;
        // Schedule death of new person
        if(np.death_time < days){
          death_scheduler[np.death_time].push_back(d);
        }
      }
    }
  }

  Rcpp::NumericVector deaths_out = Rcpp::wrap(deaths);

  return Rcpp::List::create(
    Rcpp::Named("deaths") = deaths_out);
}



