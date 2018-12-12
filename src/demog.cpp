#include <Rcpp.h>
#include <string>
#include <cmath>
#include "demog.h"
#include "person.h"
#include "helper.h"
#include "time.h"

//' @export
// [[Rcpp::export]]
std::vector<int> demog_test(int N, int days, int substep, std::vector<double> age_of_death,
                            std::vector<int> birth_times, std::vector<int> death_times){

  // Initialise model time
  int t = 0;
  // Maximum time steps
  int maxt = steps(days, substep);
  // Propoprtion of births that are female
  double prop_f = 0.5;

  // Death tracker
  std::vector<int> deaths(maxt);
  int cur_death;
  int year_death;
  int day_death;

  // Population
  std::vector<Person2> Pop;
  Pop.reserve(N);

  // Populate Pop vector
  for(int i = 0; i < N; i++){
    // New person
    Person2 np = Person2(birth_times[i], death_times[i] - birth_times[i]);
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
      if(Pop[p].death == t){
        // Record death
        cur_death ++;
        // Draw age of death for new person
        year_death = weighted_sample(age_of_death, 0);
        day_death = int(R::runif(0, 365));
        // Replace with new person
        Person2 np = Person2(t, t + year_death * 365 + day_death);
        Pop[p] = np;
      }
    }
    // Record deaths in timestep
    deaths[t] = cur_death;
  }

  return deaths;
}



