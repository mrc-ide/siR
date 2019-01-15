#include <Rcpp.h>
#include <string>
#include <cmath>
#include "demog.h"
#include "person.h"
#include "sample.h"
#include "time.h"
#include "demog_equilibrium.h"

//' Test demography
//'
//' @param N Population size
//' @param days Simulation time (days)
//' @param substep Substeps per day
//' @param age_of_death Probability of age of death
//' @param equilibrium_age Equilibrium age distribution
//' @param beta Beta parameter (per day)
//' @param i0 Initial number of infecteds
//' @param sigma Recovery rate (per day)
//' @export
// [[Rcpp::export]]
Rcpp::List open_sir(int N, int days, int substep,
                    std::vector<double> age_of_death,
                    std::vector<double> equilibrium_age,
                    double beta, double sigma, int i0){

  // Convert rates in days to rates in substeps
  beta = beta / substep;
  sigma = sigma / substep;

  double prob_inf;
  double prob_recover =  1 - exp(-sigma);
  double N_inverse = 1 / (double)N;

  // Maximum time steps
  int maxt = days_to_steps(days, substep);
  Rcpp::Rcout << "Maxt: " << maxt << std::endl;

  // Initialise demog vars
  int equil_age;
  int equil_death;

  // Initialise vector of age years
  std::vector<int> age_years(90);
  for(unsigned int i = 0; i < 90; i++){
    age_years[i] = i;
  }

  // Deaths
  //// Tracking
  std::vector<int> deaths(maxt);
  int year_death;
  int day_death;
  //// Scheduling
  std::vector<std::vector<int > > death_scheduler(maxt);
  Rcpp::Rcout << "Death scheduler size: " << death_scheduler.size() << std::endl;

  std::vector<int> S(maxt);
  std::vector<int> I(maxt);
  std::vector<int> R(maxt);
  S[0] = N - i0;
  I[0] = i0;
  R[0] = 0;

  // Population
  std::vector<Person> Pop;
  Pop.reserve(N);

  // Populate Pop vector
  for(int i = 0; i < N; i++){
    equil_age = draw_equilibrium_age(age_years, equilibrium_age);
    equil_death = draw_equilibrium_death_age(equil_age, age_years,
                                             age_of_death, 89);
    // New person
    Person np = Person(-equil_age, equil_death - equil_age);
    // Add to pop vector
    Pop.push_back(np);
    // Schedule their death (Adjust for step size?)
    if(days_to_steps(np.death_time, substep) < maxt){
      //Rcpp::Rcout << "Max schedule: " << days_to_steps(np.death_time, substep) << std::endl;
      death_scheduler[days_to_steps(np.death_time, substep)].push_back(i);
    }
  }
  // Initialise infecteds (Need to be careful that selecting the first n
  //// remains random)
  for(int i = 0; i < i0; i++){
    Pop[i].status = infected;
  }

  // Cycle through time steps
  for(int t = 1; t < maxt; t++){
    // Initialise counters for current timestep
    S[t] = S[t - 1];
    I[t] = I[t - 1];
    R[t] = R[t - 1];
    // Update the probability of infection
    prob_inf = 1 - exp(-beta * I[t - 1] * N_inverse);

    // State changes -----------------------------------------------------------
    for(int i = 0; i < N; i++){
      //Rcpp::Rcout << "Status: " << Pop[i].status << std::endl;
      switch(Pop[i].status){

      case susceptible: {
        if(R::runif(0, 1) < prob_inf){
        // Infection occurs
        Pop[i].status = infected;
        I[t] ++;
        S[t] --;
      }
        break;
      }

      case infected: {
        if(R::runif(0, 1) < prob_recover){
        // Recovery occurs
        Pop[i].status = recovered;
        R[t]++;
        I[t]--;
      }
        break;
      }

      case recovered: {
        // No action required for recovered individuals
        break;
      }
      }
    }
    // -------------------------------------------------------------------------


    // Deaths ------------------------------------------------------------------
    // Record deaths in timestep
    deaths[t] = death_scheduler[t].size();
    // Implement scheduled deaths (replace with new born)
    if(death_scheduler[t].size() > 0){
      for(unsigned int d = 0; d < death_scheduler[t].size(); d++){
        switch(Pop[death_scheduler[t][d]].status){
        case susceptible: break;
        case infected: {
          I[t] --;
          S[t] ++;
          break;
        }
        case recovered: {
          R[t] --;
          S[t] ++;
        }
        }
        // Draw for new person
        year_death = weighted_sample_int(age_years, age_of_death);
        day_death = sample_int(0, 364);
        // Replace with new person
        Person np = Person(t, t + year_death * 365 + day_death);
        Pop[death_scheduler[t][d]] = np;
        // Schedule death of new person
        if(days_to_steps(np.death_time, substep) < maxt){
          death_scheduler[days_to_steps(np.death_time, substep)].push_back(d);
        }
      }
    }
    // -------------------------------------------------------------------------
  }


  // Convert for R export ------------------------------------------------------
  Rcpp::NumericVector deaths_out = Rcpp::wrap(deaths);
  Rcpp::NumericVector S_out = Rcpp::wrap(S);
  Rcpp::NumericVector I_out = Rcpp::wrap(I);
  Rcpp::NumericVector R_out = Rcpp::wrap(R);

  return Rcpp::List::create(
    Rcpp::Named("S") = S_out,
    Rcpp::Named("I") = I_out,
    Rcpp::Named("R") = R_out,
    Rcpp::Named("deaths") = deaths_out);
  // ---------------------------------------------------------------------------
}



