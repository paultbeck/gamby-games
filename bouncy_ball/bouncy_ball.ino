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

static int Delta = 2;

int xPos;
int yPos;
int hDirection;
int vDirection;

int width = 16;
int height = 16;

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
  //gamby.drawSprite(xPos, yPos, smiley8x8, smiley8x8_mask);
  gamby.drawPattern=0xFFFF;
  gamby.disc(xPos + width / 2, yPos + height / 2, width / 2);
  if (hDirection == 1) {xPos+=Delta;}
  else {xPos-=Delta;}
  if (vDirection == 1) {yPos+=Delta;}
  else {yPos-=Delta;}
  gamby.update();
  updateDirection();
  delay(25);
}

void updateDirection() {
  if (xPos < 0 || xPos > NUM_COLUMNS - width)
  {
    hDirection = (hDirection + 1) % 2;
  }
  if (yPos < 0 || yPos > NUM_ROWS - height)
  {
    vDirection = (vDirection + 1) % 2;
  }  
}
