#include <Rcpp.h>
#include <algorithm>
#include <vector>
using namespace Rcpp;

struct person{
  int s;
  int i;
  int r;
};


std::vector<double> seq_rcpp2(const int &tf, const double &dt){
  std::vector<double> out((tf / dt) + 1);
  out[0] = 0;
  for(std::size_t i = 1; i < out.size(); i++){
    out[i] = out[i - 1] + dt;
  }
  return out;
}

bool compareByLength(const person &person1, const person &person2){
  return person1.s > person2.s;
}

//' @export
// [[Rcpp::export]]
List ibm_closed_sir_rcpp2(const double sigma = 2, const double beta = 4, const int N = 1000, const int i0 = 1, const int t_final = 100, const double dt = 0.01){

  double prob_inf;
  double N2 = N;
  double N_inv = 1 / N2;
  int new_infections;
  int new_recoveries;

  // daily prob of infection
  double prob_recover = 1 - exp(-sigma * dt);

  // Create vector of times
  std::vector<double> t = seq_rcpp2(t_final, dt);

  // State variables
  std::vector<int> S(t.size());
  std::vector<int> I(t.size());
  std::vector<int> R(t.size());

  // Initialise people
  std::vector<person> pop(N);
  for(int i = 0; i < N; i++){
    pop[i].s = 1;
    pop[i].i = 0;
    pop[i].r = 0;
  }

  // Initialise infection
    // Shuffle the vector
  std::random_shuffle (pop.begin(), pop.end());
    // Infect first i0 people
  for(int i = 0; i < i0; i++){
    pop[i].s = 0;
    pop[i].i = 1;
    pop[i].r = 0;
  }

  // Calculate the output variables
  S[0] = N - i0;
  I[0] =  i0;
  R[0] = 0;

  for(int i = 1; i < t.size(); i++){
    prob_inf = 1 - exp(-beta * I[i - 1] * N_inv * dt);
    new_infections = R::rbinom(S[i - 1], prob_inf);
    new_recoveries = R::rbinom(I[i - 1], prob_recover);

    // Shuffle the vector
    std::random_shuffle(pop.begin(), pop.end());
    // Sorts the vector
    std::sort(pop.begin(), pop.end(), compareByLength);

    for(int j = 1; j < new_infections; j++){
      pop[j].s = 0;
      pop[j].i = 1;
    }

    for(int k = N-1; k > N - (new_recoveries); k--){
      pop[k].i = 0;
      pop[k].r = 1;
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
