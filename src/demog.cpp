#include <Rcpp.h>
#include <string>
#include <cmath>
#include "demog.h"
#include "person.h"
#include "helper.h"

//' @export
// [[Rcpp::export]]
void demog_test(int N, std::vector<double> agedist, std::vector<double> time){

  // Initialise death scheduler
  std::vector<std::list<Person* > > death_scheduler(time.size());

  double dt = 0.1;
  // Initialise vector of people
  std::vector<Person> Pop;
  // Populate from given age distribution and 50:50 sex ratio
  for(int i = 0; i < N; i++){
    Person p1 = Person(time[0], agedist, 0.5);
    Pop.push_back(p1);
    death_scheduler[(Pop[i].get_death_time() - time[0]) / dt].push_back(&Pop[i]);
  }


  for(unsigned int t = 0; t < death_scheduler.size(); t++){
    if(death_scheduler[t].size() > 0){
      for(std::list<Person* >::iterator it = death_scheduler[t].begin();
          it != death_scheduler[t].end(); ++it){
        Person p1 = Person(time[1], agedist, 0.5);
        // Assign a new person to the memory that the it pointer points to
        **it = p1;
      }
    }
  }

  // double t = 1.0;
  // for(unsigned int i = 0; i < Pop.size(); i++){
  //   Rcpp::Rcout << "Person " << i + 1 << std::endl;
  //   Rcpp::Rcout << "Person" << i + 1 << " Age is " << Pop[i].get_age(t) << std::endl;
  //   Rcpp::Rcout << "Person" << i + 1 << " death time is " << Pop[i].get_death_time() << std::endl;
  // }
  //
  // t = 100;
  // for(unsigned int i = 0; i < Pop.size(); i++){
  //   Rcpp::Rcout << "Person " << i + 1 << std::endl;
  //   Rcpp::Rcout << "Person" << i + 1 << " Age is " << Pop[i].get_age(t) << std::endl;
  // }

  //for(unsigned int i = 0; i < Pop.size(); i++){
  // Rcpp::Rcout << "Person " << i + 1 << std::endl;
  //Rcpp::Rcout << "Sex is " << Pop[i].get_sex() << std::endl;
  //Rcpp::Rcout << "Age is " << Pop[i].get_age() << std::endl;
  //}

}


