// Including this files header at the start will ensure it is self sufficient and can be included elsewhere
// #include <thisfile.h>
#include <Rcpp.h>
/// Don't use this, use Rcpp:: where possible
using namespace Rcpp;


NumericVector seq_rcpp(int t0, int tf, double dt){
  NumericVector out(((tf - t0) / dt) + 1);
  out[0] = t0;
  for(int i = 1; i <= ((tf - t0) / dt); i++){
    out[i] = out[i - 1] + dt;
  }
  return out;
}

//' @export
// [[Rcpp::export]]
NumericMatrix ibm_closed_sir_rcpp(double sigma = 2, double beta = 4, int N = 1000, int i0 = 1, int t_final = 100, double dt = 0.01){

  double prob_inf;

  // Create vector of times
  NumericVector t = seq_rcpp(0, t_final, dt);
  NumericMatrix out(t.length(), 4);
  // daily prob of infection
  double prob_recover =  1 - exp(-sigma * dt);

  // State variables
  IntegerVector S(t.length());
  IntegerVector I(t.length());
  IntegerVector R(t.length());

  // Individual variables
  IntegerVector susceptible(N, 1);
  IntegerVector infected(N, 0);
  IntegerVector recovered(N, 0);
  IntegerVector schedule_recovery_time(N, 1);

  double N2 = N;
  double N_inv = 1 / N2;
  IntegerVector Ns = seq(0, N-1);

  // Initialise infection
  IntegerVector first_infected = sample(Ns, i0);
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

  for(int i = 1; i < t.length(); i++){
    prob_inf = 1 - exp(-beta * RunningTotal_Infected * N_inv * dt);

    for(int j = 0; j < N; j++){

      if(susceptible[j] == 1){
        random_binom = R::rbinom(1, prob_inf);
        if(random_binom == 1){
          susceptible[j] = 0;
          infected[j] = 1;
          RunningTotal_Suceptible --;
          RunningTotal_Infected ++;
        }
      }

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
  out(_,0) = t;
  out(_,1) = S;
  out(_,2) = I;
  out(_,3) = R;
  return out;
}


