#ifndef SNAKE_H
#define SNAKE_H

#include "SymbConst.h"
#include "Food.h"
#include "Arduboy.h"

class SnakeSection {
  
  public:

    uint8_t x; //X-Koordinate der zusätzlichen Schlangenteile
    uint8_t y; //Y-Koordinate der zusätzlichen Schlangenteile

    SnakeSection(); //Konstruktor der Klasse SnakePart
    sectionCoord(uint8_t positionX, uint8_t positionY);
};

class Snake {
  
  public:
  
    uint8_t x; //X-Koordinate der Schlange
    uint8_t y; //Y-Koordinate der Schlange
    uint8_t direction; //Richtung
    Food food; //Futter
    uint8_t foodEaten; //der Wert, wieviel Futter gefressen wurde um die Schlange anhand dessen zu verlängern
    bool isDead; //ein Boolean für den Tod der Schlange
    uint8_t speed; //Geschwindigkeit
    bool canMakeSound = true; //für Sounds

    Snake(); //Konstruktor der Klasse Snake
    void initialise(Arduboy *adb, uint8_t gameState);
    void move();
    void draw();
    
  private:

    uint8_t sectionCounter; 
    uint8_t sectionCountStart;
    SnakeSection sections[MAX_SECTIONS];
    Arduboy *arduboy; //Zeiger auf den Arduboy

    bool checkCollisionWithFood(); //Kollisionsabfrage mit dem Futter
    bool checkCollisionWithBorder(); //Kollisionsabfrage mit den Wänden
    bool checkCollisionWithItself(); //Kollisionsabfrage mit sich selbst
};

#endif
