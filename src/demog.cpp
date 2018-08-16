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

  // Initialise the time step
  int t = 0;
  int maxt = steps(days, substep);
  // Rcpp::Rcout << "Max T = " << maxt << std::endl;
  // Initialise propoprtion of births that are female
  double prop_f = 0.5;

  // Initialise death scheduler
  std::vector<std::vector<Person* > > death_scheduler(maxt);
  // Initialise a death tracker
  std::vector<int> deaths(maxt);

  // Initialise population
  std::vector<Person> Pop;
  Pop.reserve(N);
  // Populate Pop vector
  for(int i = 0; i < N; i++){
    Person np = Person(t, substep, prop_f, age_distribution, life_distribution);
    Pop.push_back(np);
    // If death occurs within timeframe, add to scheduler.
    if(np.death_time < maxt){
      death_scheduler[np.death_time].push_back(&Pop[i]);
    }
  }

  // Cycle through time steps
  for(int t = 0; t < maxt; t++){
    deaths[t] = death_scheduler[t].size();
    // Scheduled deaths
    if(death_scheduler[t].size() > 0){
      // Rcpp::Rcout << death_scheduler[t].size() << " deaths in timestep " << t << std::endl;
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


