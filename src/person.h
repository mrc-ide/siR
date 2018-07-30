#ifndef person_h
#define person_h

#include <string>

class Person{
  public:
    // Default constructor
    Person();

    // Overload constructor
    Person(std::vector<double> &agedist, double prop_f);

    // Draw sex of individual
    std::string attribute_sex(double prop_f = 0.5);

    // Get function(s)
    std::string get_sex() const;
    double get_age() const;

  private:
    double age;
    std::string sex;
};

#endif
