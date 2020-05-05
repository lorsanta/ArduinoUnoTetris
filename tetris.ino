#include <LiquidCrystal.h>

#include "tetris_game.h"
#include "jukebox.h"

#define RS 4
#define E 5
#define D4 7
#define D5 8
#define D6 10
#define D7 12

#define NBUTTONS 2

#define BUTTON2 3
#define BUTTON1 2

#define LOWERPIN 2

LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

Tetronimo tetronimo;
TetrisGame tetrisGame;

#if MUSIC_ON
  Jukebox jukebox;
#endif

int prevState[NBUTTONS];

void setup()
{
  pinMode(BUTTON2, INPUT);
  pinMode(BUTTON1, INPUT);
  
  tetrisGame.init_display(lcd);

#if MUSIC_ON
  jukebox.setBpm(180);
  //https://www.instructables.com/id/Arduino-Timer-Interrupts/
  cli();
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  
  
  sei();
#endif
  
  int buttonState[NBUTTONS];
  
  unsigned delay_time = 400;
  
  while(tetrisGame.start(lcd)) 
  {
    do 
    {
      // INPUT HANDLING
      unsigned long StartTime = millis();
      unsigned long ElapsedTime = 0;
      while(ElapsedTime < delay_time) 
      {
        for(byte i = 0; i < NBUTTONS; ++i)
        {
          buttonState[i] = digitalRead(LOWERPIN + i);
        
          if(buttonState[i] && prevState[i] != buttonState[i])
          {
            switch(LOWERPIN + i) 
            {
              case BUTTON2:
                tetrisGame.moveRight();
                break;
               
              case BUTTON1:
                tetrisGame.rotate();
            }
          }
          
          for(int i = 0; i < NBUTTONS; ++i)
          {
            prevState[i] = buttonState[i];
          }
        }
        
        ElapsedTime = millis() - StartTime;
      }
      // ------------
            
    }
    while(tetrisGame.update(lcd));
  
  }
  
}

#if MUSIC_ON
  ISR(TIMER1_COMPA_vect){
  unsigned long d = jukebox.play();
  OCR1A = 15624 * d / 1000;
  }
#endif


void loop() 
{
}
