#ifndef FOOD_H
#define FOOD_H

#include "Arduboy.h"

class Food {
  
  public:

    uint8_t x; //X-Koordinate des Futters
    uint8_t y; //Y-Koordinate des Futters

    Food(); //Konstruktor der Klasse Food
    void generate();
    void initialise(Arduboy *adb);
    void draw();

  private:
  
    Arduboy *arduboy;
};

#endif
