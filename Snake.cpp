#include "Snake.h"
#include "Graphics.h"

SnakeSection::SnakeSection() { } //Konstruktor der Klasse SnakePart

SnakeSection::sectionCoord(uint8_t positionX, uint8_t positionY) {

  x = positionX;
  y = positionY;
}

Snake::Snake() { } //Konstruktor der Klasse Snake

void Snake::initialise(Arduboy *adb, uint8_t gameState) {

  direction = DIRECTION_RIGHT; //die Schlange startet immer rechts

  foodEaten = 0; //die Menge an Futter, die gefressen wurde
  
  isDead = false; //
 
  arduboy = adb;

  if (gameState == GAMESTATE_GAME) { //die Schlange wird im Spiel initialisiert

    x = 72; //Startkoordinaten der Schlange (X-Achse)
    y = 32; //Startkoordinaten der Schlange (Y-Achse)
    
    sectionCounter = 5;
    sectionCountStart = 0;
    sections[0] = sectionCoord(56, 32);
    sections[1] = sectionCoord(60, 32);
    sections[2] = sectionCoord(64, 32);
    sections[3] = sectionCoord(68, 32);
    sections[4] = sectionCoord(72, 32);
  
    speed = 1;
    arduboy->setFrameRate(speed); //die Framerate liegt dadurch bei einem Frame pro Sekunde
  
    food.initialise(arduboy);
  
    food.generate();
  }
}

void Snake::move() {

  if (direction == DIRECTION_UP) {
  
    y -= GRAPHICS_SIZE; //y = y - GRAPHICS_SIZE
  }
  else if (direction == DIRECTION_DOWN) {
  
    y += GRAPHICS_SIZE; //y = y + GRAPHICS_SIZE
  }
  else if (direction == DIRECTION_LEFT) {
  
    x -= GRAPHICS_SIZE; //x = x - GRAPHICS_SIZE
  }
  else {
  
    x += GRAPHICS_SIZE; //x = x + GRAPHICS_SIZE
  }

  if (checkCollisionWithItself() || checkCollisionWithBorder()) { //Überprüfung, ob die Schlange mit dem Rand oder mit sich selbst kollidiert
    
    isDead = true; //Die Schlange ist tot :/

    if (canMakeSound) {
      
      arduboy->tunes.tone(1100, 80);
      delay(100);
      arduboy->tunes.tone(1000, 80);
      delay(100);
      arduboy->tunes.tone(500, 500);
    }
  }
  if (checkCollisionWithFood()) { //Überprüfung, ob die Schlange mit Futter in Berührung kommt
   
    sections[(sectionCountStart + sectionCounter) % MAX_SECTIONS] = sectionCoord(x, y);
    sectionCounter++;
    
    
    foodEaten++; //der Zähler für das gefressene Futter erhöht sich um eins

     //Erhöhen der Spielgeschwindigkeit bei steigendem Highscore
    if (foodEaten % 3 == 0 && speed < 13) { //sollte der Rest von foodEaten / 3 0 sein und (&&) die Geschwindigkeit kleiner als 13 ist...

      speed++;//...wird die Geschwindigkeit um 1 erhöht (speed = speed + 1)
      if (speed == 3) speed++; //Bug, wenn die Geschwindigkeit auf 3 gesetzt wird, aus welchen Gründen auch immer
      arduboy->setFrameRate(speed); //Die vorher erhöhte Geschwindigkeit entspricht jetzt den FPS (Frames pro Sekunde)
    }
  
    food.generate();

    if (canMakeSound) {
      
      arduboy->tunes.tone(500, 50);
      delay(80);
      arduboy->tunes.tone(800, 50);
      delay(80);
      arduboy->tunes.tone(1100, 100);
    }
  }
  else {
  
    sections[(sectionCountStart + sectionCounter) % MAX_SECTIONS] = sectionCoord(x, y);
    partsStart = (partsStart + 1) % MAX_SNAKE_PARTS;
  }
}

void Snake::draw() {

  uint8_t currentSection;

  for (uint8_t i=0; i<sectionCounter; i++) {
    
    currentPart = (sectionCountStart + i) % MAX_SECTIONS;
    
    if (i == (sectionCounter - 1))
      if (direction == DIRECTION_UP) {
        arduboy->drawBitmap(sections[currentPart].x, sections[currentPart].y, snakeHeadUp, GRAPHICS_SIZE, GRAPHICS_SIZE, 1);
      }
      else if (direction == DIRECTION_DOWN) {
        arduboy->drawBitmap(sections[currentPart].x, sections[currentPart].y, snakeHeadDown, GRAPHICS_SIZE, GRAPHICS_SIZE, 1);
      }
      else if (direction == DIRECTION_LEFT) {
        arduboy->drawBitmap(sections[currentPart].x, sections[currentPart].y, snakeHeadLeft, GRAPHICS_SIZE, GRAPHICS_SIZE, 1);
      }
      else {
        arduboy->drawBitmap(sections[currentPart].x, sections[currentPart].y, snakeHeadRight, GRAPHICS_SIZE, GRAPHICS_SIZE, 1);
      }
    } 
    
    else {
      arduboy->drawBitmap(sections[currentPart].x, sections[currentPart].y, snakeBody, GRAPHICS_SIZE, GRAPHICS_SIZE, 1);
    }
  }

bool Snake::checkCollisionWithFood() { //Überprüfung, ob die Schlange mit dem Futter in Berührung kommt
  
  if (x == food.x && y == food.y) 
    {
      return true;} //wenn die Koordinaten der Schlange mit denen des Futters übereinstimmen, wird true zurückgegeben
  else {
    return false;
    }
}

bool Snake::checkCollisionWithBorder() { 
  
  if (x == 0 || x == 124 || y == 0 || y == 60) {return true;}
  else {return false;}
}

bool Snake::checkCollisionWithItself() { 

  uint8_t currentPart; 


  for (uint8_t i=0; i<sectionCounter; i++) {

    currentPart = (sectionCountStart + i) % MAX_SECTIONS;

    if (x == sections[currentPart].x && y == sections[currentPart].y) {
      
      return true;
    }
  }
  
  return false;
}
