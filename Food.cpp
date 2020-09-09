#include "Arduboy.h"
#include "SymbConst.h"
#include "Food.h"
#include "Graphics.h"

Food::Food() { } //Konstruktor der Klasse Food

void Food::initialise(Arduboy *adb) {

  arduboy = adb;
}

void Food::generate() { //Futter wird generiert

  x = random(1, 31) * GRAPHICS_SIZE; //Die X-Position des Futters wird zufällig gewählt
  y = random(1, 15) * GRAPHICS_SIZE; //Die Y-Position des Futters wird zufällig gewählt
}

void Food::draw() { //Das Futter wird auf den Bildschirm gezeichnet

  arduboy->drawBitmap(x, y, foodGraphic, GRAPHICS_SIZE, GRAPHICS_SIZE, 1);    //die ersten zwei Werte entsprechen den Koordinaten, foodSprite steht für die Sprite, 
                                                                              //die verwendet werden soll, die nächsten zwei Werte stehen für Breite und Höhe.
                                                                              //Alle Bits der Sprite, die 1 entsprechen werden weiß auf dem Bildschirm dargestellt, der Rest bleibt schwarz. 
}
