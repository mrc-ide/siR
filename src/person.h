#ifndef person_h
#define person_h


class Person{
  public:
    // Default constructor
    Person(double &time, double &prop_f, std::vector<double> &prob_survive, std::vector<double> &prob_death);

    // New birth
    void new_birth(double &t, double &prop_f, std::vector<double> &prob_death);

    // Draw sex of individual
    std::string attribute_sex(double prop_f = 0.5);

    // Attributes
    double birth_date;
    int lifespan;
    std::string sex;

};

#endif
