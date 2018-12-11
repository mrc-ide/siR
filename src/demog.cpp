#include <Rcpp.h>
#include <string>
#include <cmath>
#include "demog.h"
#include "person.h"
#include "helper.h"
#include "time.h"

//' @export
// [[Rcpp::export]]
std::vector<int> demog_test(int N, int days, int substep,
                            std::vector<double> age_distribution, std::vector<double> life_distribution){

  // Initialise model time
  int t = 0;
  // Maximum time steps
  int maxt = steps(days, substep);
  // Propoprtion of births that are female
  double prop_f = 0.5;

  // Death scheduler
  std::vector<std::vector<Person* > > death_scheduler(maxt);
  // Death tracker
  std::vector<int> deaths(maxt);

  // Population
  std::vector<Person> Pop;
  Pop.reserve(N);

  // Populate Pop vector
  for(int i = 0; i < N; i++){
    // New person
    Person np = Person(t, substep, prop_f, age_distribution, life_distribution);
    // Add to pop vector
    Pop.push_back(np);
    // If death occurs within timeframe, add a pointer to the person to scheduler.
    if(np.death_time < maxt){
      death_scheduler[np.death_time].push_back(&Pop[i]);
    }
  }

  // Cycle through time steps
  for(int t = 0; t < maxt; t++){
    if(t % substep == 0){
      deaths[t] = death_scheduler[t].size();
      // Scheduled deaths
      for(unsigned int d = 0; d < death_scheduler[t].size(); d++){
        // Replace the dead person
        death_scheduler[t][d]->new_birth(t, substep, prop_f, life_distribution);
        // Schedule the new person's death if within time window
        if(death_scheduler[t][d]->death_time < maxt){
          death_scheduler[death_scheduler[t][d]->death_time].push_back(death_scheduler[t][d]);
        }
      }
    }
  }

  return deaths;
}


