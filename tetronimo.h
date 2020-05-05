#ifndef TETRONIMO_H
#define TETRONIMO_H

#include "Arduino.h"

#include "global_tetris_variables.h"

#define N_TETRONIMO 7

class Tetronimo {
public: 
  Tetronimo();
  void rotateRight();
  void getRandomTetronimo();
  byte* getTetronimoBytes();
  byte getSize();
  byte getHeight();
  void reset();
  
  byte x, y;
  byte blocks_inuse[MAX_BLOCKS_INUSE];
  
private:

  byte* (*current_tetr)[MAX_SIZE_TETRONIMO];
  byte (*tetr_height)[MAX_SIZE_TETRONIMO];

  byte (*tetr_size)[MAX_SIZE_TETRONIMO];
  byte max_rotated;
  
  byte current_rotated;
  enum { I, O, T, J, L, S, Z } tetronimo;
  
};

#endif
