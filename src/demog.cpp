#include <Rcpp.h>
#include <string>
#include <cmath>
#include "demog.h"
#include "person.h"
#include "sample.h"
#include "time.h"

//' @export
// [[Rcpp::export]]
std::vector<int> demog_test(int N, int days, int substep, std::vector<double> age_of_death,
                            std::vector<int> birth_times, std::vector<int> death_times){

  // Maximum time steps
  int maxt = steps(days, substep);

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
    // New person
    Person np = Person(birth_times[i], death_times[i] - birth_times[i]);
    // Add to pop vector
    Pop.push_back(np);
  }

  // Cycle through time steps
  for(int t = 0; t < maxt; t++){
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

  return deaths;
}



