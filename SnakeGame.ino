#include <Arduboy.h> //Arduboybibliotek
#include "Snake.h"
#include "Graphics.h"

Arduboy arduboy; //Objekt der Klasse Arduboy
Snake snake; //Objekt der Klasse Schlange
uint8_t gameState; //gibt den Spielzustand wieder 
char scoreText[4]; //derzeitiger Score
uint8_t highScore = 0; //Highscore
char highScoreText[4];  
uint8_t blinkingTextState = 0; //blinkender Text

void setup() {

  arduboy.begin();

  //Lädt das beste Ergebnis aus dem EEPROM
  highScore = EEPROM.read(EEPROM_ADDRESS); //wenn die Adresse dem Wert 255 entspricht
  if (highScore == 255) {                  // bedeutet dass, das hier noch nichts im Speicher beschrieben wurde
    
    highScore = 0;
    EEPROM.update(EEPROM_ADDRESS, highScore);
  }

  //Das Hauptmenü wird zu aller erst angezeigt
  gameState = GAMESTATE_MAINMENU;
  snake.initialise(&arduboy, GAMESTATE_MAINMENU); //& als Referenz
}

void loop() {

  if (snake.isDead) { 
    
    //Anpassung an das Textgeflimmer
    arduboy.setFrameRate(1);

    if (snake.foodEaten > highScore) { //Wenn der derzeitige Score höher als der Highscore ist...

      
      highScore = snake.foodEaten; //...wird der derzeitige Highscore mit dem neuen überschrieben...
      EEPROM.update(EEPROM_ADDRESS, snake.foodEaten); //...und im EEPROM aktualisiert
    }
  
    //Wenn der B-Knopf gedrückt wird...
    if (arduboy.pressed(B_BUTTON)) {

      //...kommt man ins Hauptmenü
      gameState = GAMESTATE_MAINMENU;
      snake.initialise(&arduboy, GAMESTATE_MAINMENU); //Schlange wird initialisiert
  
      delay(200); //Verzögerung um zu verhindern, dass der Knopf sofort wieder gedrückt wird

      return;
    }

    if (!arduboy.nextFrame()) return;
    
    arduboy.clear();

    //"GAME OVER" wird geschrieben
    arduboy.setTextSize(2);
    arduboy.setCursor(10, 2);
    arduboy.print("GAME OVER");

    //der Score wird geschrieben
    arduboy.setTextSize(1);
    arduboy.setCursor(19, 25);
    arduboy.print("Dein Score: ");
    arduboy.setCursor(91, 25);
    sprintf(scoreText, "%03u", snake.foodEaten);
    arduboy.print(scoreText);

    //der Highscore wird geschrieben
    arduboy.setCursor(19, 40);
    arduboy.print("Highscore:");
    arduboy.setCursor(91, 40);
    sprintf(highScoreText, "%03u", highScore);
    arduboy.print(highScoreText);
  
    //"Press B to continue" wird geschrieben
    blinkingTextState = (blinkingTextState + 1) % 6;
    if (blinkingTextState < 3) {
  
      arduboy.setCursor(7, 55);
      arduboy.print("B zum Fortfahren");
    }
       
    arduboy.display(); //Alles oben geschriebene wird auf dem Bildschirm ausgegeben
  }
  
  else if (gameState == GAMESTATE_GAME) {

    //hier wird geregelt, was bei welchem Knopfdruck passiert
    if (arduboy.pressed(UP_BUTTON)) { //Wenn auf dem Steuerkreuz nach oben gedrückt wird...
  
      snake.direction = DIRECTION_UP; //...wird die Richtung entsprechend geändert
    }
    else if (arduboy.pressed(DOWN_BUTTON)) { //Wenn auf dem Steuerkreuz nach unten gedrückt wird...
      
      snake.direction = DIRECTION_DOWN; //...wird die Richtung entsprechend geändert   
    }
    else if (arduboy.pressed(LEFT_BUTTON)) { //Wenn auf dem Steuerkreuz nach links gedrückt wird...
      
      snake.direction = DIRECTION_LEFT; //...wird die Richtung entsprechend geändert    
    }
    else if (arduboy.pressed(RIGHT_BUTTON)) { //Wenn auf dem Steuerkreuz nach rechts gedrückt wird...
      
      snake.direction = DIRECTION_RIGHT; //...wird die Richtung entsprechend geändert     
    }
    else if (arduboy.pressed(A_BUTTON)) {
  
      //An- oder Ausschalten des Tons
      arduboy.setTextSize(1);
      if (snake.canMakeSound) {
  
        snake.canMakeSound = false;
        arduboy.setCursor(28, 0);
        arduboy.print("            ");
        arduboy.setCursor(34, 0);
        arduboy.print("Sound: AUS");
      }
      else {
  
        snake.canMakeSound = true;
        arduboy.setCursor(31, 0);
        arduboy.print("           ");
        arduboy.setCursor(37, 0);
        arduboy.print("Sound: AN");
        arduboy.tunes.tone(1000, 200);
      }
      arduboy.display();
      delay(1000);
    }
    else if (arduboy.pressed(B_BUTTON)) {
      
      gameState = GAMESTATE_PAUSED;
      
      delay(200);    
    }
    
    if (!arduboy.nextFrame()) return;
    
    snake.move();
    if (snake.isDead) return;

    arduboy.clear();

    //die Feldbegrenzung 
    arduboy.drawRect(2, 2, 124, 60, 1); //ein Rechteck wird gezeichnet, dabei sind (2/2) die Koordinaten, 124/60 die Höhe und Breite des Rechtecks und 1 die Farbe weiß.

    arduboy.setTextSize(1);
    arduboy.setCursor(49, 0);
    arduboy.print("     ");
    arduboy.setCursor(55, 0);
    sprintf(scoreText, "%03u", snake.foodEaten);
    arduboy.print(scoreText);
   
    snake.draw();
    snake.food.draw();
  
    arduboy.display();
  }

  //solang das Spiel pausiert ist, wird eine entsprechende Nachricht angezeigt
  else if (gameState == GAMESTATE_PAUSED) {

    //nochmaliges Drücken führt das Spiel fort
    if (arduboy.pressed(B_BUTTON)) {
    
      gameState = GAMESTATE_GAME;
  
      delay(200);
    }

    if (!arduboy.nextFrame()) return;
    
    //"PAUSE"-Bildschirm wird gezeichnet
    arduboy.fillRect(22, 18, 84, 28, 0);
    arduboy.drawRect(23, 19, 82, 26, 1);
    arduboy.setTextSize(2);
    arduboy.setCursor(29, 25);
    arduboy.print("PAUSE");
  
    arduboy.display();
  }

  //Standardmäßig wird das Hauptmenü angezeigt
  else {

    arduboy.setFrameRate(20);

    if (arduboy.pressed(B_BUTTON)) {

      //Spielstart
      gameState = GAMESTATE_GAME;
      snake.initialise(&arduboy, GAMESTATE_GAME);

      delay(200);

      return;
    }
    
    if (!arduboy.nextFrame()) return;
  
    arduboy.clear();
    
    //Titel
    arduboy.setTextSize(2);
    arduboy.setCursor(10, 11);
    arduboy.print("SNAKE");
    arduboy.setTextSize(1);
    
    //"B zum Starten"-Text
    blinkingTextState = (blinkingTextState + 1) % 30;
    if (blinkingTextState < 15) {
    
      arduboy.setCursor(16, 44);
      arduboy.print("B zum Starten");
    }

    snake.draw();
  
    arduboy.display();
  }
}
