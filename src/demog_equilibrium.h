#ifndef demog_equilibrium_h
#define demog_equilibrium_h

int draw_equilibrium_age(std::vector<int> &age_years, std::vector<double> &equilibrium_age);
int draw_equilibrium_death_age(int age, std::vector<int> &age_years, std::vector<double> age_of_death, int max_age);
#endif
