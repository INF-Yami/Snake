//hier werden die Sprites für die Schlange und das Futter gespeichert

#ifndef GRAPHICS_H
#define GRAPHICS_H

//   X   X
// X   X  
//   X   X
// X   X  
//
PROGMEM const uint8_t foodGraphic[] = {
  
  0b00001010,
  0b00000101,
  0b00001010,
  0b00000101
};

//     X X
//   X   X
// X X X X
// X X X X
//
PROGMEM const uint8_t snakeHeadLeft[] = {
  
  0b00001100,
  0b00001110,
  0b00001101,
  0b00001111
};

// X X    
// X   X  
// X X X X
// X X X X
//
PROGMEM const uint8_t snakeHeadRight[] = {
  
  0b00001111,
  0b00001101,
  0b00001110,
  0b00001100
};

//     X X
//   X X X
// X   X X
// X X X X
//
PROGMEM const uint8_t snakeHeadUp[] = {
  
  0b00001100,
  0b00001010,
  0b00001111,
  0b00001111
};

// X X X X
// X X   X
// X X X  
// X X    
//
PROGMEM const uint8_t snakeHeadDown[] = {
  
  0b00001111,
  0b00001111,
  0b00000101,
  0b00000011
};

//   X X X
// X   X X
// X X   X
// X X X   
//
PROGMEM const uint8_t snakeBody[] = {
  
  0b00001110,
  0b00001101,
  0b00001011,
  0b00000111
};

#endif
