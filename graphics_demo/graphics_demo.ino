#include <Gamby.h>
#include <avr/pgmspace.h>

// Fill patterns (4x4 pixel grids as 16b ints)

#define PATTERN_WHITE           0x0000
#define PATTERN_BLACK           0xFFFF
#define PATTERN_GRAY            0x5a5a  // B0101101001011010
#define PATTERN_DK_GRAY         0xfaf5  // B1111101011110101
#define PATTERN_LT_GRAY         0x050a  // B0000010100001010
#define PATTERN_DK_L_DIAGONAL   0xedb7  // B1110110110110111
#define PATTERN_LT_L_DIAGONAL   0x1248  // B0001001001001000
#define PATTERN_DK_R_DIAGONAL   0x7bde  // B0111101111011110
#define PATTERN_LT_R_DIAGONAL   0x8421  // B1000010000100001
#define PATTERN_DK_GRID_SOLID   0xeeef  // B1110111011101111
#define PATTERN_LT_GRID_SOLID   0x1110  // B0001000100010000
#define PATTERN_DK_GRID_DOTS    0xfafa  // B1111101011111010
#define PATTERN_LT_GRID_DOTS    0x0505  // B0000010100000101
#define PATTERN_CHECKER         0x33cc  // B0011001111001100
#define PATTERN_CHECKER_INV     0xcc33  // B1100110000110011

const prog_uchar smiley8x8[] PROGMEM = {
  8, 8, 
  0x3c, 0x42, 0xad, 0xa1, 0xad, 0x91, 0x42, 0x3c
};

const prog_uchar smiley8x8_mask[] PROGMEM = {
  8, 8, 
  0x3c, 0x7e, 0xff, 0xff, 0xff, 0xff, 0x7e, 0x3c
};

const prog_uchar test8x8[] PROGMEM = {
  8, 8, 
  B11111111,
  B00000001,
  B11111101,
  B00000101,
  B11110101,
  B00010101,
  B11010101,
  B01010101,

};

const prog_uchar box8x8[] PROGMEM = {
  8, 8, 
  B11111111,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B10000001,
  B11111111
};


GambyGraphicsMode gamby;

byte frameNum = 0;
int runs = 0;

void setup () {
  gamby = GambyGraphicsMode();
}


void loop () {
  gamby.clearScreen();
  gamby.update();
  int r, c;
  
  for (r=0; r<NUM_ROWS; r+=2) {
    for(c=0; c<NUM_COLUMNS; c+=2) {
      gamby.setPixel(c,r,false);
    }
  }
  gamby.update();
  delay(1000);
  
  gamby.clearScreen();
  gamby.drawPattern = 0;
  for (r=4; r<NUM_ROWS>>1;r+=4) {
    gamby.circle(NUM_COLUMNS >> 1, NUM_ROWS >> 1, r);
    if (r % 8)
    gamby.update();
    delay(50);
  }

  concentricCircles();
  
  moire(0);
  delay(1000);
  
  gamby.clearScreen();
  randomCircles();
  gamby.update();
  delay(1000);
  
  drawSpriteGrid(smiley8x8, smiley8x8_mask);
  delay(1000);
  
  runs++;
}


void concentricCircles() {
  int p, r;
  for (r=NUM_ROWS>>1; r>1;r-=4) {
    p = p == 0 ? 0xFFFF : 0;
    gamby.drawPattern = p;
    gamby.disc(NUM_COLUMNS >> 1, NUM_ROWS >> 1, r);
    if (r % 8)
    gamby.update();
    delay(50);
  }    
}

void moire(int pat) {
  int i;
  gamby.drawPattern = pat;
  for (i=0; i < NUM_COLUMNS; i+=3) {
    gamby.line(NUM_COLUMNS >> 1, NUM_ROWS >> 1, i, 0);
    if (i % 8 == 0)
      gamby.update();
  }

  for (i=0; i < NUM_ROWS; i+=3) {
    gamby.line(NUM_COLUMNS >> 1, NUM_ROWS >> 1,NUM_COLUMNS-1,i);
    if (i % 8 == 0)
      gamby.update();
  }

  for (i=NUM_COLUMNS-1; i >= 0; i-=3) {
    gamby.line(i, NUM_ROWS-1, NUM_COLUMNS >> 1, NUM_ROWS >> 1);
    if (i % 8 == 0)
      gamby.update();
  }

  for (i=NUM_ROWS-1; i >= 0; i-=3) {
    gamby.line(NUM_COLUMNS >> 1, NUM_ROWS >> 1,0,i);
    if (i % 8 == 0)
      gamby.update();
  }
}

int pats[] = {0x0000, 0xFFFF, 0x5a5a, 0xfaf5, 0x050a, 0xedb7, 0x1248, 0x7bde, 0x8421, 0xeeef, 0x1110, 0xfafa, 0x0505, 0x33cc, 0xcc33};

void randomCircles() {
  int p = PATTERN_WHITE;
  int x, y, r;
  for (int i=0; i<50; i++) {
    gamby.drawPattern = pats[p];
    x = random(0,NUM_COLUMNS);
    y = random(0,NUM_ROWS);
    r = random(8,20);
    gamby.disc(x,y,r);
    gamby.drawPattern = 0;
    gamby.circle(x,y,r);
    if (i % 10)
      gamby.update();
    p = p < 14 ? p+1 : 0;
  }
  gamby.drawPattern=0xFFFF;
}

void drawSpriteGrid(const prog_uchar *spriteIdx, const prog_uchar *maskIdx) {
  for (int i=2; i<NUM_ROWS-8; i+=10) {
    for (int j=2; j<NUM_COLUMNS-8; j+=10) {
      gamby.drawSprite(j, i, spriteIdx, maskIdx);
    }
  }
  gamby.update();
}
