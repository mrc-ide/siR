#include <Rcpp.h>
using namespace Rcpp;

struct person{
  int age;
  double heterogeneity;
};

// [[Rcpp::export]]
List ibm_het(double sigma = 2, double beta = 4, int N = 1000, int i0 = 1, NumericVector times = 0, double dt = 0.1, bool het = false){

  // Intialise variables /////////////////////////////////////////////////////
  double prob_inf;
  double N_inverse = 1 / (double)N;
  // daily prob of infection
  double prob_recover =  1 - exp(-sigma * dt);
  // Convert times to c++ type for consistency
  std::vector<double> t = as< std::vector<double> >(times);
  ///////////////////////////////////////////////////////////////////////////

  // Initialise the population //////////////////////////////////////////////
  std::vector<person> pop(N);
  for(int p = 1; p < N; p++){
    pop[p].age = R::runif(0, 80);
    pop[p].heterogeneity = 1;
  }
  // Including heteogeneity in infection prob (lower on average than without het)
  if(het){
    for(int p = 1; p < N; p++){
      pop[p].heterogeneity = R::rbeta(2, 1);
    }
  }
  ////////////////////////////////////////////////////////////////////////////

  // Initialise lists of pointers tracking S, I and R ////////////////////////
  std::list<person* > susceptible;
  std::list<person* > infected;
  std::list<person* > recovered;

  // Add pointers to all people into susceptible list
  for(int i = 0; i<N; i++){
    susceptible.push_back(&pop[i]);
  }
  // Sample initial infections
  std::vector<int> initial_infected = as< std::vector<int> >(runif(i0, 0, (N - 1)));
  // Remove initial infections from suceptible and add to infected
  int counter = 0;
  for (std::list<person* >::iterator it = susceptible.begin(); it != susceptible.end(); ++it){
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
  IntegerVector S(t.size());
  IntegerVector I(t.size());
  IntegerVector R(t.size());

  S[0] = N - i0;
  I[0] =  i0;
  R[0] = 0;

  int running_total_susceptible = S[0];
  int running_total_infected = I[0];
  int running_total_recovered = R[0];
  /////////////////////////////////////////////////////////////////////////////

  // Loop through all times
  for(unsigned int time = 1; time < t.size(); time++){
    // Update the probability of unfection
    prob_inf = 1 - exp(-beta * I[time - 1] * N_inverse * dt);

    // Infections
    for (std::list<person* >::iterator it = susceptible.begin(); it != susceptible.end(); ++it){
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

    // Recoveries
    for (std::list<person* >::iterator it = infected.begin(); it != infected.end(); ++it){
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
