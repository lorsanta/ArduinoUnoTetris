#include "tetronimo.h"

#include <string.h>

#include "tetronimo_types.h"

Tetronimo::Tetronimo() 
{
  current_tetr = 0;
  x = 0; 
  y = 0;
  tetr_size = &tetr_null;
  tetr_height = &tetr_null;
  current_rotated = 0;
}

void Tetronimo::rotateRight()
{
  current_rotated++;
  
  if(current_rotated >= max_rotated)
    current_rotated = 0;
}

void Tetronimo::getRandomTetronimo() 
{
   switch(analogRead(A5) % N_TETRONIMO)
   {
     case I: 
       current_tetr = &ptetr_I;
       tetr_height = &tetr_I_height;
       max_rotated = ROTATED_TETR_I;
       tetr_size = &tetr_I_size;
     break;
     case O: 
       current_tetr = &ptetr_O;
       tetr_height = &tetr_O_height;
       max_rotated = ROTATED_TETR_O;
       tetr_size = &tetr_O_size;
     break;
     case T: 
       current_tetr = &ptetr_T;
       tetr_height = &tetr_T_height;
       max_rotated = ROTATED_TETR_T;
       tetr_size = &tetr_T_size;
     break;
     case J: 
       current_tetr = &ptetr_J;
       tetr_height = &tetr_J_height;
       max_rotated = ROTATED_TETR_J;
       tetr_size = &tetr_J_size;
     break;
     case L: 
       current_tetr = &ptetr_L;
       tetr_height = &tetr_L_height;
       max_rotated = ROTATED_TETR_L;
       tetr_size = &tetr_L_size;
     break;
     case S: 
       current_tetr = &ptetr_S;
       tetr_height = &tetr_S_height;
       max_rotated = ROTATED_TETR_S;
       tetr_size = &tetr_S_size;
     break;
     case Z: 
       current_tetr = &ptetr_Z;
       tetr_height = &tetr_Z_height;
       max_rotated = ROTATED_TETR_Z;
       tetr_size = &tetr_Z_size;              
   }
}

byte* Tetronimo::getTetronimoBytes() {
  return (*current_tetr)[current_rotated];
}

byte Tetronimo::getSize() {
  return (*tetr_size)[current_rotated];
}

byte Tetronimo::getHeight() {
  return (*tetr_height)[current_rotated];
}

void Tetronimo::reset() 
{
  current_rotated = 0;
  tetr_size = &tetr_null;
  tetr_height = &tetr_null;
}
