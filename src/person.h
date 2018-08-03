#ifndef person_h
#define person_h

#include <string>

class Person{
  public:
    // Default constructor
    Person(double &t);

    // Overload constructor
    Person(double &t, std::vector<double> &agedist, double prop_f);

    // Draw sex of individual
    std::string attribute_sex(double prop_f = 0.5);

    // Get function(s)
    std::string get_sex() const;
    double get_age(double &t) const;
    double get_death_time() const;

    // Edit function(s)


  private:
    double birth_time;
    double death_time;
    std::string sex;
};

#endif
