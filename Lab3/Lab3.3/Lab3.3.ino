
#include "pitches.h"
#define PIN_BUZZER 13 // the digital pin the Buzzer is attached to
#define PIN_BUTTON 0

// play note at given frequency (Hz)
// if frequency is 0, turn off buzzer
void play_note(int freq) {
  if(freq>0) {
    // send square wave at freq Hz with 50% duty cycle
    analogWrite(PIN_BUZZER, 256);
    analogWriteFreq(freq);
   } else {
    analogWrite(PIN_BUZZER, 0);
  }
  delay(400);
}

bool is_stopped = false;
int i = 0;

void toggle() {
  is_stopped = !is_stopped;
  i = 0;
}

void setup() {
  // pin 12 is connected to the buzzer on the prototype board.
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), toggle, RISING);
  
}

const int music[] PROGMEM = {NOTE_DS5,NOTE_E5,NOTE_DS5,NOTE_E5,NOTE_B4,NOTE_D5,NOTE_C5,NOTE_A4,0,NOTE_C4,NOTE_E4,NOTE_A4,NOTE_B4,0,NOTE_E4,NOTE_GS4,NOTE_B4,NOTE_C5,0,NOTE_E4,NOTE_E5,NOTE_DS5,NOTE_E5,NOTE_DS5,NOTE_E5,NOTE_B4,NOTE_D5,NOTE_C5,NOTE_A4,0,NOTE_C4,NOTE_E4,NOTE_A4,NOTE_B4,NOTE_E4,NOTE_C5,NOTE_B4,NOTE_A4,0};

void loop() {
  // put your main code here, to run repeatedly:

  
  for(i = 0; i < sizeof(music); i++) {
    if (!is_stopped){
      play_note(music[i]); 
    }
    else {
      play_note(0);
    }
  }

}
