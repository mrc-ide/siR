#include <Rcpp.h>
#include <string>
#include <cmath>
#include "demog.h"
#include "person.h"
#include "helper.h"

//' @export
// [[Rcpp::export]]
std::vector<int> demog_test(int N, std::vector<double> time,
                            std::vector<double> age_distribution, std::vector<double> life_distribution){
  Rcpp::Rcout << "START" << std::endl;

  // Initialise the time step
  int t = 0;
  /// ***** Need to make sure it can work with non-interger time steps
  double dt = 1;
  // Initialise propoprtion of birth that are female
  double prop_f = 0.5;
  // Initialise a pointer to a person
  Person *p1;
  // Initialise death scheduler
  ////// **** Need to fix this so there are check again length
  std::vector<std::vector<Person* > > death_scheduler(time.size() + 100000);
  // Initialise a death tracker
  std::vector<int> deaths(time.size());

  // Initialise population
  std::vector<Person* > Pop;
  // Populate population
  for(unsigned int i = 0; i < N; i++){
    p1 = new Person(time[t], prop_f, age_distribution, life_distribution);
    Pop.push_back(p1);
    // If death occurs within timeframe, add to scheduler.
    if(p1->lifespan < time.back()){
      ////// ***** Need to think about the bets way for this # steps to be calcualted
      int t1 = int(p1->lifespan);
      death_scheduler[t1].push_back(p1);
    }
  }

  // Cycle through time steps
   for(int t = 0; t < time.size(); t++){
  //
     deaths[t] = death_scheduler[t].size();
  //   // Scheduled deaths
     if(death_scheduler[t].size() > 0){
   // Rcpp::Rcout << death_scheduler[t].size() << " deaths in timestep " << t << std::endl;
      for(int d = 0; d < death_scheduler[t].size(); d++){
  //       // Replace the dead person
         death_scheduler[t][d]->new_birth(time[t], prop_f, life_distribution);
  //       // Schedule the new person's death if within time window
         //if((time[t] + death_scheduler[t][d]->lifespan) < time.back()){
           int t1 = int((time[t] + death_scheduler[t][d]->lifespan) / dt);
           death_scheduler[t1].push_back(death_scheduler[t][d]);
         //}
       }
     }
   }

  return deaths;
}


