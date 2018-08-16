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
  Rcpp::Rcout << "START" << std::endl;

  // Initialise the time step
  int t = 0;
  int maxt = steps(days, substep);
  // Rcpp::Rcout << "Max T = " << maxt << std::endl;
  // Initialise propoprtion of births that are female
  double prop_f = 0.5;
  // Initialise a pointer to a person
  Person *p1;

  // Initialise death scheduler
  std::vector<std::vector<Person* > > death_scheduler(maxt);
  // Initialise a death tracker
  std::vector<int> deaths(maxt);

  // Initialise population
  std::vector<Person* > Pop;

  // Populate Pop vector
  for(int i = 0; i < N; i++){
    // Calling "new" looks for a block of contiguous memory large enough to hold the object
      // (in this case a Person), and returns a pointer to that object (p1), it then calls the
      // constructor associated with Person (to create a new person).
    p1 = new Person(t, substep, prop_f, age_distribution, life_distribution);
    Pop.push_back(p1);
    // If death occurs within timeframe, add to scheduler.
    if(p1->death_time < maxt){
      death_scheduler[p1->death_time].push_back(p1);
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


