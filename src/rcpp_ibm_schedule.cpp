#include <Rcpp.h>
#include <string>
#include <cmath>
#include "rcpp_ibm_schedule.h"
#include "person.h"
#include "helper.h"
#include "time.h"

//' @export
// [[Rcpp::export]]
Rcpp::List ibm_scheduled(double sigma, double beta, int N, int i0, int days, int substep,
                         std::vector<double> age_distribution, std::vector<double> life_distribution){

  // Intialise variables /////////////////////////////////////////////////////
  double prob_inf;
  double N_inverse = 1 / (double) N;
  double substep_inverse = 1 / (double) substep;
  //Rcpp::Rcout << N_inverse << std::endl;
  // prob of infection
  double prob_recover = 1 / (sigma * substep_inverse);
  // Initialise model time
  int t = 0;
  // Maximum time steps
  int maxt = steps(days, substep);
  // Propoprtion of births that are female
  double prop_f = 0.5;
  // List of susceptibles
  std::list<Person* > susceptible;
  // Recover scheduler
  std::vector<std::vector<Person* > > recover_scheduler(maxt);
  // Infection time
  int infection_time;
  ///////////////////////////////////////////////////////////////////////////

  // Initialise the population //////////////////////////////////////////////
  // Population
  std::vector<Person> Pop;
  Pop.reserve(N);

  // Populate Pop vector
  for(int i = 0; i < N; i++){
    // New person
    Person np = Person(t, substep, prop_f, age_distribution, life_distribution);
    // Add to pop vector
    Pop.push_back(np);
    // Add to list of susceptibles
    susceptible.push_back(&Pop[i]);
  }
  ///////////////////////////////////////////////////////////////////////////

  // Initialise state variable outputs ///////////////////////////////////////
  Rcpp::IntegerVector S(maxt);
  Rcpp::IntegerVector I(maxt);
  Rcpp::IntegerVector R(maxt);

  S[0] = N - i0;
  I[0] = i0;
  R[0] = 0;

  int running_total_susceptible = S[0];
  int running_total_infected = I[0];
  int running_total_recovered = R[0];
  /////////////////////////////////////////////////////////////////////////////

  std::list<Person* >::iterator it;
  int random_draw;
  for(int i = 0; i < i0; i++){
    it = susceptible.begin();
    random_draw =  (int) R::runif(0, susceptible.size()-1);
    std::advance(it, random_draw);

    infection_time = (int) R::rexp(prob_recover);
    if(infection_time < maxt){
      // Add to recovery scheduler
      recover_scheduler[infection_time].push_back(*it);
    }
    // Remove from List
    susceptible.erase(it);
  }

  for(int t = 1; t < maxt; t++){
    // Update the probability of infection
    prob_inf = 1 - exp(-beta * I[t - 1] * N_inverse * substep_inverse);
    for (std::list<Person* >::iterator it = susceptible.begin(); it != susceptible.end(); ++it){
     if(R::runif(0, 1) < (prob_inf)){
        running_total_susceptible --;
        running_total_infected ++;
        // Draw infection time
        infection_time = (int) R::rexp(prob_recover);
        if((t + infection_time) < maxt){
          // Add to recovery scheduler
          recover_scheduler[t + infection_time].push_back(*it);
        }
        // Remove from list of susceptibles
        it = susceptible.erase(it);
      }
    }

    // Scheduled recoveries
    for(unsigned int r = 0; r < recover_scheduler[t].size(); r++){
      running_total_infected --;
      running_total_recovered ++;
    }

    // Calculate the output variables
    S[t] = running_total_susceptible;
    I[t] = running_total_infected;
    R[t] = running_total_recovered;
  }

  // Return desired variables in a list
  return Rcpp::List::create(
    Rcpp::Named("S") = S,
    Rcpp::Named("I") = I,
    Rcpp::Named("R") = R);
}
