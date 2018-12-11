#include <Rcpp.h>
#include <string>
#include <cmath>
#include "rcpp_ibm_het.h"
#include "person.h"
#include "helper.h"
#include "time.h"

//' @export
// [[Rcpp::export]]
Rcpp::List ibm_het(double sigma, double beta, int N, int i0, Rcpp::NumericVector times, double dt, bool het,
                   std::vector<double> age_distribution, std::vector<double> life_distribution){

  // Intialise variables /////////////////////////////////////////////////////
  double prob_inf;
  double N_inverse = 1 / (double)N;
  // daily prob of infection
  double prob_recover =  1 - exp(-sigma * dt);
  // Convert times to c++ type for consistency
  std::vector<double> t = Rcpp::as< std::vector<double> >(times);
  int substep = (int)1/dt;
  double prop_f = 0.5;
  ///////////////////////////////////////////////////////////////////////////

  // Initialise the population //////////////////////////////////////////////
  std::vector<Person> pop;
  pop.reserve(N);

  int temp = 0;
  // populate pop vector
  for(int i = 0; i < N; i++){
    // New person
    Person np = Person(temp, substep, prop_f, age_distribution, life_distribution);
    // Add to pop vector
    pop.push_back(np);
  }
  // Including heteogeneity in infection prob (lower on average than without het)
  if(het){
    for(int p = 0; p < N; p++){
      pop[p].heterogeneity = R::rbeta(2, 1);
    }
  }
  ////////////////////////////////////////////////////////////////////////////

  // Initialise lists of pointers tracking S, I and R ////////////////////////
  std::list<Person* > susceptible;
  std::list<Person* > infected;
  std::list<Person* > recovered;
  // Add pointers to all people into susceptible list
  for(int i = 0; i<N; i++){
    susceptible.push_back(&pop[i]);
  }
  // Sample initial infections
  std::vector<int> initial_infected = Rcpp::as< std::vector<int> >(Rcpp::runif(i0, 0, (N - 1)));
  // Remove initial infections from suceptible and add to infected
  int counter = 0;
  for (std::list<Person* >::iterator it = susceptible.begin(); it != susceptible.end(); ++it){
    for(int i = 0; i<i0; i++){
      if(counter == initial_infected[i]){
        infected.push_back(*it);
        it = susceptible.erase(it);
      }
    }
    counter ++;
  }
  /////////////////////////////////////////////////////////////////////////////

  // Initialise state variable outputs ///////////////////////////////////////
  Rcpp::IntegerVector S(t.size());
  Rcpp::IntegerVector I(t.size());
  Rcpp::IntegerVector R(t.size());

  S[0] = N - i0;
  I[0] =  i0;
  R[0] = 0;

  int running_total_susceptible = S[0];
  int running_total_infected = I[0];
  int running_total_recovered = R[0];
  /////////////////////////////////////////////////////////////////////////////

  // Loop through all times
  for(unsigned int time = 1; time < t.size(); time++){
    // Update the probability of infection
    prob_inf = 1 - exp(-beta * I[time - 1] * N_inverse * dt);

    // Recoveries (Before infections as infections adds to infected)
    for (std::list<Person* >::iterator it = infected.begin(); it != infected.end(); ++it){
      if(R::runif(0, 1) < prob_recover){
        // Add recovered to end to recovered pointer list
        recovered.push_back(*it);
        // Remove recovered from infected pointer list
        it = infected.erase(it);
        // Update running totals
        running_total_infected --;
        running_total_recovered ++;
      }
    }

    // Infections
    for (std::list<Person* >::iterator it = susceptible.begin(); it != susceptible.end(); ++it){
      // Probability of infection is population probability * individual heterogeneity
      if(R::runif(0, 1) < (prob_inf * (*it)->heterogeneity)){
        // Add infected to end to infected pointer list
        infected.push_back(*it);
        // Remove infected from susceptible pointer list
        it = susceptible.erase(it);
        // Update running totals
        running_total_susceptible --;
        running_total_infected ++;
      }
    }

    // Calculate the output variables
    S[time] = running_total_susceptible;
    I[time] = running_total_infected;
    R[time] = running_total_recovered;
  }

  // Return desired variables in a list
  return Rcpp::List::create(
    Rcpp::Named("t") = t,
    Rcpp::Named("S") = S,
    Rcpp::Named("I") = I,
    Rcpp::Named("R") = R);

}
