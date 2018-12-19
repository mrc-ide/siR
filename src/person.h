#ifndef person_h
#define person_h

// Define an enumerator to denote status of an individual
enum state {
  susceptible, infected, recovered
};

class Person{
public:
  // Default constructor
  Person(int birth_t, int death_t);

  // Draw sex of individual
  char attribute_sex(double prop_f = 0.5);

  // Attributes
    // Demography
  int birth_time;
  int death_time;
    // Epi
  state status;
};



#endif
