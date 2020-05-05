#ifndef TETRIS_DISPLAY_H
#define TETRIS_DISPLAY_H

#include <stdint.h>

#include "Arduino.h"
#include "LiquidCrystal.h"

#include "global_tetris_variables.h"
#include "tetronimo.h"

// The display is divided in 8 block(8 custom character)
#define NBLOCKS_DISPLAY 8
// Display width in pixel
#define DISPLAY_WIDTH 16
// Display height in pixel
#define DISPLAY_HEIGHT 20

enum { LEFT, RIGHT };
enum { UPPER, UCENTER, BCENTER, BOTTOM};
enum { UPPER_L, UCENTER_L, BCENTER_L, BOTTOM_L, UPPER_R, UCENTER_R, BCENTER_R, BOTTOM_R };

//
// The display is stored as an array of integer
// Each integer is a column of our display
// tetris_display  [0] [1] .. [15]
//                0 x   x      x
//                  .   .      .
//                  .   .      .
//               19 x   x      x
//
//
// SET (x,y, data)
// B[y] = (data & BLOCK_HEIGHT) << x; 
// GET
// B[j] & (1 << i) -> A[i][j]
//

class TetrisGame {
public:
  TetrisGame();
  void init_display(LiquidCrystal& lcd);
  bool start(LiquidCrystal& lcd);
  bool update(LiquidCrystal& lcd);

  bool moveRight();
  bool rotate();

private:
  void updateScore(LiquidCrystal& lcd, byte ntetris);
  void checkTetris(LiquidCrystal& lcd);
  void clearPreviousTetronimo(LiquidCrystal& lcd);
  void drawPreviousTetronimo(LiquidCrystal& lcd);
  bool fitIn();
  void addUp();
  void renderBlocksInuse(LiquidCrystal&  lcd);
  void renderAllBlocks(LiquidCrystal& lcd);
  // Get custom block from tetris_display
  void extractBlock(byte (&block)[NBLOCKS_DISPLAY], byte upper_bottom, byte left_right);
  // Get blocks where current tetronimo is 
  void getCurrentBlocksInuse(byte (&blocks_inuse)[MAX_BLOCKS_INUSE]);
  
  uint32_t tetris_display[DISPLAY_WIDTH];
  Tetronimo current_tetr, prev_tetr;
  
  uint16_t score;
};

#endif
