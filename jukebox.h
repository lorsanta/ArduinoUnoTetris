#ifndef JUKEBOX_H
#define JUKEBOX_H

#include "Arduino.h"

#define LEN_MELODY 93

class Jukebox {
public:
  Jukebox();
  unsigned long play();
  void setBpm(unsigned long bpm);
  
private:
  unsigned long duration[LEN_MELODY];
  unsigned long bpm;
  byte current_note;
};

#endif
