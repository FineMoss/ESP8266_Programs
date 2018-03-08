#include <EEPROM.h>
#include <Ticker.h>

#define PIN_BUZZER 13

PROGMEM const int freqs[] = {31, 49, 78, 123, 196, 311, 494, 784, 1245, 1976, 3136, 4978};

Ticker secondTick;
volatile int watchdogCount = 0;
volatile int freqIdx = 0;  //the index that will store the last frequency before it restarts.
int EEPROM_Addr = 0;       //the address of the EEPROM that will store the freqIdx. It can be any value from 0 to 4095 since we have 4K EEROM.


//The Watchdog Interrupt Service Routine (ISR)
void ISRwatchdog() {
  watchdogCount++;
  //The watchdog will be waken up when the couter reaches 4
  if (watchdogCount == 4) {
    //restarting the board
    ESP.restart(); 
  }
}


void setup() {
  // disabling the built-in watchdog
  ESP.wdtDisable(); 
  //registering the watchdog ISR
  secondTick.attach(1, ISRwatchdog);
  //initializing the EEROM of size 4KB
  EEPROM.begin(4096); 
  Serial.begin(115200);
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {

  Serial.print("Watchdog counter = ");
  Serial.println(watchdogCount);
  watchdogCount = 0;

  //read the value stored at the address
  int val_read = EEPROM.read(EEPROM_Addr); 
  Serial.println(val_read);

  // generating 50% PWM
  analogWrite(PIN_BUZZER, 256);
  analogWriteFreq(freqs[val_read]);  

  delay(random(1,5) * 1000);

  freqIdx = random(0,11);
  //value to write to EEPROM
  int val_write = freqIdx; 
  //write the value to the address
  EEPROM.write(EEPROM_Addr, val_write);
  //commit to EEPROM to make all the changes
  EEPROM.commit();
  
  
}













