#include <Rcpp.h>
#include <algorithm>
#include <vector>
using namespace Rcpp;

std::vector<double> seq_rcpp3(const int &tf, const double &dt){
  std::vector<double> out((tf / dt) + 1);
  out[0] = 0;
  for(std::size_t i = 1; i < out.size(); i++){
    out[i] = out[i - 1] + dt;
  }
  return out;
}

//' ibm_closed_sir_rcpp 3
//'
//' @inheritParams ibm_closed_sir
//'
//' @return IBM model output
//' @export
// [[Rcpp::export]]
List ibm_closed_sir_rcpp3(const double sigma = 2, const double beta = 4, const int N = 1000, const int i0 = 1, const int t_final = 100, const double dt = 0.01){

  double prob_inf;
  double N2 = N;
  double N_inv = 1 / N2;
  int new_infections;
  int new_recoveries;

  // daily prob of infection
  double prob_recover = 1 - exp(-sigma * dt);

  // Create vector of times
  std::vector<double> t = seq_rcpp3(t_final, dt);

  // State variables
  std::vector<int> S(t.size());
  std::vector<int> I(t.size());
  std::vector<int> R(t.size());

  // Initialise people
  std::vector<int> susceptible(N);
  std::vector<int> infected;
  std::vector<int> recovered;

  for(int i = 0; i < N; i++){
    susceptible[i] = i;
  }

  // Sample infecteds
  std::vector<int> firstinfected = as<std::vector<int> >(sample(N, i0));

  // Remove from susceptible and add to infected
  for(unsigned int i = 0; i < firstinfected.size(); i++){
    susceptible.erase(susceptible.begin() + (firstinfected[i] - 1));
    infected.push_back(firstinfected[i] - 1);
  }

  // Initialise state counters
  // Calculate the output variables
  S[0] = N - i0;
  I[0] =  i0;
  R[0] = 0;

  int index;

  // Loop through all times
  for(unsigned int i = 1; i < t.size(); i++){

    prob_inf = 1 - exp(-beta * I[i - 1] * N_inv * dt);

    new_infections = R::rbinom(S[i - 1], prob_inf);
    new_recoveries = R::rbinom(I[i - 1], prob_recover);

    // Remove from susceptible and add to infected
    std::random_shuffle(susceptible.begin(), susceptible.end());
    std::random_shuffle(infected.begin(), infected.end());

    for(unsigned int j = 0; j < new_infections; j++){
      infected.push_back(susceptible[susceptible.size()]);
      susceptible.pop_back();

    }

    std::reverse(infected.begin(), infected.end());

    // Remove from susceptible and add to infected
    for(unsigned int k = 0; k < new_recoveries; k++){
      recovered.push_back(infected[infected.size()]);
      infected.pop_back();
    }


    S[i] = S[i-1] - new_infections;
    I[i] = I[i-1] + new_infections - new_recoveries;
    R[i] = R[i-1] + new_recoveries;
  }


  return Rcpp::List::create(
    Rcpp::Named("t") = t,
    Rcpp::Named("S") = S,
    Rcpp::Named("I") = I,
    Rcpp::Named("R") = R);
}
