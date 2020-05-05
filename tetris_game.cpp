#include "tetris_game.h"

#include <string.h>

TetrisGame::TetrisGame() 
{
  memset(tetris_display, 0, 4*DISPLAY_WIDTH);
  score = 0;
}

bool TetrisGame::moveRight()
{
  if(current_tetr.x + current_tetr.getSize() < DISPLAY_WIDTH)
    current_tetr.x++;
}

bool TetrisGame::rotate()
{
  current_tetr.rotateRight();
  return true;
}

void TetrisGame::init_display(LiquidCrystal& lcd) 
{
  byte block[BLOCK_WIDTH];
  memset(block, 0, BLOCK_WIDTH);

  for(byte i=0; i < NBLOCKS_DISPLAY; ++i) 
    lcd.createChar(i, block);

  lcd.begin(16,2);

  lcd.setCursor(9, 0);
  lcd.print("score:");
  lcd.setCursor(9,1);
  lcd.print(score);

  for(byte i=0; i < NBLOCKS_DISPLAY; ++i) 
  {
    switch(i) 
    {
      case(UPPER_L): 
      lcd.setCursor(3, 0);
      break; 
      case(UCENTER_L): 
      lcd.setCursor(2, 0);
      break; 
      case(BCENTER_L): 
      lcd.setCursor(1, 0);
      break; 
      case(BOTTOM_L): 
      lcd.setCursor(0, 0);
      break; 
      case(UPPER_R): 
      lcd.setCursor(3, 1);
      break; 
      case(UCENTER_R): 
      lcd.setCursor(2, 1);
      break; 
      case(BCENTER_R): 
      lcd.setCursor(1, 1);
      break; 
      case(BOTTOM_R): 
      lcd.setCursor(0, 1);
    }
    lcd.write(i);
  }

}

bool TetrisGame::start(LiquidCrystal& lcd)
{
  current_tetr.getRandomTetronimo();
  current_tetr.x = 0;
  current_tetr.y = 0;
  return update(lcd);
}

bool TetrisGame::update(LiquidCrystal& lcd)
{
  if(prev_tetr.getSize())
    clearPreviousTetronimo(lcd);

  if(!fitIn())
  {
    drawPreviousTetronimo(lcd);
    goto end_update;
  }

  addUp();

  renderBlocksInuse(lcd);

  if(current_tetr.y + current_tetr.getHeight() >= DISPLAY_HEIGHT) 
  {
    goto end_update;
  }

  prev_tetr = current_tetr;
  current_tetr.y++;

  return true;
  
end_update:
  checkTetris(lcd);
  current_tetr.reset();
  prev_tetr.reset();

  return false;
}      

void TetrisGame::addUp() 
{
  byte* tetronimo_bytes = current_tetr.getTetronimoBytes();  

  byte x = current_tetr.x; 
  byte y = current_tetr.y;

  for(byte i = 0; i < current_tetr.getSize(); ++i) 
  {
    uint32_t t = tetronimo_bytes[i]; // NEED IT!!  
    tetris_display[i + x] |= (t << y);
  }
}

void TetrisGame::checkTetris(LiquidCrystal& lcd) 
{

  uint32_t j_cache[DISPLAY_HEIGHT];
  byte ntetris = 0;
  uint32_t res = tetris_display[0];  

  for(byte i = 1; i < DISPLAY_WIDTH; ++i)
  {
    res &= tetris_display[i];
  }

  if(!res) return;
  
  for(uint32_t j = 1; j <= res; j <<= 1) 
  {
    if(res & j) 
      j_cache[ntetris++] = j;
  }
  
  for(byte i = 0; i < DISPLAY_WIDTH; ++i)
  {
    tetris_display[i] = tetris_display[i] & ~res;
    
    for(byte k = 0; k < ntetris; ++k) 
    {
      uint32_t j = j_cache[k];
                          // upper part                                                // lower part shifted by 1
      tetris_display[i] = ( tetris_display[i] & ( ((1<<DISPLAY_HEIGHT)-1) - (j-1)) ) | ( (tetris_display[i] & (j-1)) << 1 );
    }
    
  }
  
  updateScore(lcd, ntetris);
  
  renderAllBlocks(lcd);
}

void TetrisGame::updateScore(LiquidCrystal& lcd, byte ntetris)
{
  score += 2 << (ntetris-1);
  lcd.setCursor(9,1);
  lcd.print(score);
}

void TetrisGame::clearPreviousTetronimo(LiquidCrystal& lcd)
{
  byte* tetronimo_bytes = prev_tetr.getTetronimoBytes();

  byte x = prev_tetr.x; 
  byte y = prev_tetr.y;

  for(byte i = 0; i < prev_tetr.getSize(); ++i) 
  {
    uint32_t t = tetronimo_bytes[i];
    tetris_display[i + x] &= ~(t << y);
  }

}

void TetrisGame::drawPreviousTetronimo(LiquidCrystal& lcd)
{
  byte* tetronimo_bytes = prev_tetr.getTetronimoBytes();

  byte x = prev_tetr.x; 
  byte y = prev_tetr.y;

  for(byte i = 0; i < prev_tetr.getSize(); ++i) 
  {
    uint32_t t = tetronimo_bytes[i];
    tetris_display[i + x] |= (t << y);
  }

}

bool TetrisGame::fitIn()
{
  byte* tetronimo_bytes = current_tetr.getTetronimoBytes();  

  byte x = current_tetr.x; 
  byte y = current_tetr.y;

  for(byte i = 0; i < current_tetr.getSize(); ++i) 
  {
    uint32_t t = tetronimo_bytes[i]; // NEED IT!!  

    if(tetris_display[i + x] & (t << y)) 
      return false;
  }

  return true;
}

inline bool alreadyRendered(byte position, byte end, byte (&blocks_inuse)[MAX_BLOCKS_INUSE])
{
  for(byte i = 0; i < end; ++i)
  {
    if(blocks_inuse[i] == position) 
      return true;
  }

  return false;
}

void TetrisGame::renderBlocksInuse(LiquidCrystal& lcd) {
  byte block[NBLOCKS_DISPLAY];

  getCurrentBlocksInuse(current_tetr.blocks_inuse);

  for(byte i = 0; i < MAX_BLOCKS_INUSE; ++i) 
  {
    byte upper_bottom, left_right;

    if(alreadyRendered(current_tetr.blocks_inuse[i], i, current_tetr.blocks_inuse)) continue;

    upper_bottom = current_tetr.blocks_inuse[i] & 3;
    left_right = (current_tetr.blocks_inuse[i]>=4);

    extractBlock(block, upper_bottom, left_right);
    lcd.createChar(current_tetr.blocks_inuse[i], block);
  }

  if(prev_tetr.getSize() != 0) 
  {
    for(byte i=0; i < MAX_BLOCKS_INUSE; i++) 
    {
      byte upper_bottom, left_right;

      if(alreadyRendered(prev_tetr.blocks_inuse[i], MAX_BLOCKS_INUSE, current_tetr.blocks_inuse)) continue;

      upper_bottom = prev_tetr.blocks_inuse[i] & 3;
      left_right = (prev_tetr.blocks_inuse[i]>=4);

      extractBlock(block, upper_bottom, left_right);
      lcd.createChar(prev_tetr.blocks_inuse[i], block);
    }   
  }

}

void TetrisGame::renderAllBlocks(LiquidCrystal& lcd) {

  byte block[NBLOCKS_DISPLAY];

  for(byte block_i = 0; block_i < NBLOCKS_DISPLAY; ++block_i) 
  {
    byte upper_bottom, left_right;

    upper_bottom = block_i & 3;
    left_right = (block_i>=4);

    extractBlock(block, upper_bottom, left_right);
    lcd.createChar(block_i, block);
  }

}

void TetrisGame::extractBlock(byte (&block)[BLOCK_WIDTH], byte upper_bottom, byte left_right)
{
  for(byte j = 0; j < BLOCK_WIDTH; ++j) 
  {
    block[j] = (tetris_display[j + BLOCK_WIDTH * left_right] & (0x1F << (BLOCK_HEIGHT * upper_bottom))) >> (BLOCK_HEIGHT * upper_bottom);
  }
}

inline byte getBlockInuse(byte x, byte y)
{
  return ((NBLOCKS_DISPLAY/2) * (x >= 8)) + (y / BLOCK_HEIGHT);
}

void TetrisGame::getCurrentBlocksInuse(byte (&blocks_inuse)[MAX_BLOCKS_INUSE]) 
{
  byte x = current_tetr.x; 
  byte y = current_tetr.y;
  byte tetr_size = current_tetr.getSize();

  blocks_inuse[0] = getBlockInuse(x,y);
  blocks_inuse[1] = getBlockInuse(x + tetr_size, y);
  blocks_inuse[2] = getBlockInuse(x, y + BLOCK_HEIGHT);
  blocks_inuse[3] = getBlockInuse(x + tetr_size, y + BLOCK_HEIGHT);  
}



