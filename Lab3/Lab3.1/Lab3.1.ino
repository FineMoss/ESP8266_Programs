
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


void setup() {
  // pin 12 is connected to the buzzer on the prototype board.
  pinMode(PIN_BUZZER, OUTPUT);

}

void loop() {
  // play note at a given frequency


  play_note(NOTE_E5);
  play_note(NOTE_DS5);
  play_note(NOTE_E5);
  play_note(NOTE_DS5);
  play_note(NOTE_E5);
  play_note(NOTE_B4);
  play_note(NOTE_D5);
  play_note(NOTE_C5);
  play_note(NOTE_A4);
  delay(200);
  play_note(0);
  delay(100);
  play_note(NOTE_C4);
  play_note(NOTE_E4);
  play_note(NOTE_A4);
  play_note(NOTE_B4);
  delay(200);
  play_note(0);
  delay(100);
  play_note(NOTE_E4);
  play_note(NOTE_GS4);
  play_note(NOTE_B4);
  play_note(NOTE_C5);
  delay(200);
  play_note(0);
  delay(100);
  play_note(NOTE_E4);
  play_note(NOTE_E5);
  play_note(NOTE_DS5);
  play_note(NOTE_E5);
  play_note(NOTE_DS5);
  play_note(NOTE_E5);
  play_note(NOTE_B4);
  play_note(NOTE_D5);
  play_note(NOTE_C5);
  play_note(NOTE_A4);
  delay(200);
  play_note(0);
  delay(100);
  play_note(NOTE_C4);
  play_note(NOTE_E4);
  play_note(NOTE_A4);
  play_note(NOTE_B4);
  play_note(NOTE_E4);
  play_note(NOTE_C5);
  play_note(NOTE_B4);
  play_note(NOTE_A4);
  delay(500);
  play_note(0);
  delay(5000);

  
}
