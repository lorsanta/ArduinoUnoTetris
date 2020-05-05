#include "jukebox.h"

#define PIN 6

#define Gsl   207
#define Al    220
#define B     246
#define C     261
#define D     293
#define E     329
#define F     349
#define G     392
#define Gsh   415
#define Ah    440
#define R     0

#define MINIM       500 // 1/2
#define QUARTER_DOT 375
#define QUARTER     250 // 1/4
#define EIGHTH      125 // 1/8

const unsigned notes[LEN_MELODY] = {
    E, B, C, D, C, B, Al, Al, C, E, D, C, B, C, D, E, C, Al, Al, 
    D, F, Ah, G, F, E, C, E, D, C, B, B, C, D, E, C, Al, Al, R,
    //
    E, B, C, D, C, B, Al, Al, C, E, D, C, B, C, D, E, C, Al, Al, 
    D, F, Ah, G, F, E, C, E, D, C, B, B, C, D, E, C, Al, Al, R,
    //
    E, C, D, B, C, Al, Gsl, B, R, E, C, D, B, C, E, Ah, Gsh
  };

const unsigned long values[LEN_MELODY] = {
    QUARTER, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER_DOT, EIGHTH, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, // 19
    QUARTER_DOT, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER_DOT, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, // 19     
    //
    QUARTER, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER_DOT, EIGHTH, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, // 19
    QUARTER_DOT, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER_DOT, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER, EIGHTH, EIGHTH, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, // 19     
    //
    MINIM, MINIM, MINIM, MINIM, MINIM, MINIM, MINIM, QUARTER, QUARTER, MINIM, MINIM, MINIM, MINIM, QUARTER, QUARTER, MINIM, MINIM // 17
};
                                    
Jukebox::Jukebox() 
{
  bpm = 0;
  current_note = 0;
}

unsigned long Jukebox::play()
{
  if(current_note >= LEN_MELODY) 
    current_note = 0;
  
  if(notes[current_note]) 
    tone(PIN, notes[current_note]);
  else 
    noTone(PIN);
  
  return duration[current_note++];
}

void Jukebox::setBpm(unsigned long bpm)
{
  this->bpm = bpm;
  for(byte i = 0; i < LEN_MELODY; ++i)
  {
    // (60 * 4*250 / bpm) => if bpm=60 -> 4*250 = 1000ms = 1s
    duration[i] = 60 * 4 * values[i] / bpm;
  }
}
