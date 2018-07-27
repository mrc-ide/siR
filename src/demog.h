#ifndef demog_h
#define demog_h

#include <string>

class Person{
public:
  // Default constructor
  Person();

  // Overload constructor
  Person(int age, std::string sex);

  // Test funcion
  std::string attribute_sex();

  std::string get_sex() const;


private:
  int age;
  std::string sex;
};

#endif
