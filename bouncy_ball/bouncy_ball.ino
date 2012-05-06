#include <Gamby.h>
#include <avr/pgmspace.h>

const prog_uchar smiley8x8[] PROGMEM = {
  8, 8, 
  0x3c, 0x42, 0xad, 0xa1, 0xad, 0x91, 0x42, 0x3c
};

const prog_uchar smiley8x8_mask[] PROGMEM = {
  8, 8, 
  0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c
};

GambyGraphicsMode gamby;
int xPos;
int yPos;
int hDirection;
int vDirection;

static int SPRITE_WIDTH = 8;
static int SPRITE_HEIGHT = 8;

void setup () {
  gamby = GambyGraphicsMode();
  xPos = 0;
  yPos = 0;
  hDirection = 1;
  vDirection = 1;
  gamby.clearScreen();
  gamby.update();
}

void loop () {
  gamby.clearScreen();
  gamby.drawSprite(xPos, yPos, smiley8x8, smiley8x8_mask);
  if (hDirection == 1) {xPos++;}
  else {xPos--;}
  if (vDirection == 1) {yPos++;}
  else {yPos--;}
  gamby.update();
  delay(50);
}

void updateDirection() {
  if (xPos < 0 || xPos > NUM_COLUMNS - SPRITE_WIDTH)
  {
    hDirection = (hDirection + 1) % 2;
  }
  if (yPos < 0 || yPos > NUM_ROWS - SPRITE_HEIGHT)
  {
    vDirection = (vDirection + 1) % 2;
  }  
}
