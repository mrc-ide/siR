// Including this files header at the start will ensure it is self sufficient and can be included elsewhere
// #include <thisfile.h>
#include <Rcpp.h>
#include "rcpp_ibm.h"

Rcpp::NumericVector seq_rcpp(int t0, int tf, double dt){
  Rcpp::NumericVector out(((tf - t0) / dt) + 1);
  out[0] = t0;
  for(int i = 1; i <= ((tf - t0) / dt); i++){
    out[i] = out[i - 1] + dt;
  }
  return out;
}

//' ibm_closed_sir_rcpp 1
//'
//' @inheritParams ibm_closed_sir
//'
//' @return IBM model output
//' @export
// [[Rcpp::export]]
Rcpp::List ibm_closed_sir_rcpp(double sigma = 2, double beta = 4, int N = 1000, int i0 = 1, int t_final = 100, double dt = 0.01){

  double prob_inf;

  // Create vector of times
  Rcpp::NumericVector t = seq_rcpp(0, t_final, dt);

  // daily prob of infection
  double prob_recover =  1 - exp(-sigma * dt);

  // State variables
  Rcpp::IntegerVector S(t.size());
  Rcpp::IntegerVector I(t.size());
  Rcpp::IntegerVector R(t.size());

  // Individual variables
  Rcpp::IntegerVector susceptible(N, 1);
  Rcpp::IntegerVector infected(N, 0);
  Rcpp::IntegerVector recovered(N, 0);
  Rcpp::IntegerVector schedule_recovery_time(N, 1);

  double N2 = N;
  double N_inv = 1 / N2;
  Rcpp::IntegerVector Ns =  Rcpp::seq(0, N - 1);

  // Initialise infection
  Rcpp::IntegerVector first_infected =  Rcpp::sample(Ns, i0);
  susceptible[first_infected] = 0;
  infected[first_infected] = 1;
  double random_binom;

  // Calculate the output variables
  S[0] = N - i0;
  I[0] =  i0;
  R[0] = 0;

  int RunningTotal_Suceptible = S[0];
  int RunningTotal_Infected = I[0];
  int RunningTotal_Recovered = R[0];

  // Loop through all times
  for(int i = 1; i < t.length(); i++){
    prob_inf = 1 - exp(-beta * RunningTotal_Infected * N_inv * dt);
    // Loop through all people
    for(int j = 0; j < N; j++){
      // If S, draw for infection
      if(susceptible[j] == 1){
        random_binom = R::rbinom(1, prob_inf);
        if(random_binom == 1){
          susceptible[j] = 0;
          infected[j] = 1;
          RunningTotal_Suceptible --;
          RunningTotal_Infected ++;
        }
      }
      // If I, draw for recovery
      if(infected[j] == 1){
        random_binom = R::rbinom(1, prob_recover);
        if(random_binom == 1){
          infected[j] = 0;
          recovered[j] = 1;
          RunningTotal_Infected --;
          RunningTotal_Recovered ++;
        }
      }
    }

    // Calculate the output variables
    S[i] = RunningTotal_Suceptible;
    I[i] = RunningTotal_Infected;
    R[i] = RunningTotal_Recovered;
  }

  return Rcpp::List::create(
    Rcpp::Named("t") = t,
    Rcpp::Named("S") = S,
    Rcpp::Named("I") = I,
    Rcpp::Named("R") = R);
}



