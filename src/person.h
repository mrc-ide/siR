#ifndef person_h
#define person_h


class Person{
  public:
    // Default constructor
    Person(int &t, int &substep, double &prop_f, std::vector<double> &age_dist, std::vector<double> &prob_death);

    // New birth
    void new_birth(int &t, int &substep, double &prop_f, std::vector<double> &prob_death);

    // Draw sex of individual
    char attribute_sex(double prop_f = 0.5);

    // Attributes
    int birth_time;
    int death_time;
    char sex;

};

#endif
