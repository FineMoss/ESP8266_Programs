
#define BLYNK_PRINT Serial
#define PIN_BUTTON 0
#define REED_PIN 4
#define PIN_BUZZER 13
#define NEO_PIN 15


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>
#include <Adafruit_NeoPixel.h>
#include <Temboo.h>


WiFiClient client;
WidgetTerminal terminal1(V1);
WidgetTerminal terminal2(V2);
WidgetTerminal terminal3(V3);
WidgetLCD terminal(V0);
Adafruit_NeoPixel pixel = Adafruit_NeoPixel(1, NEO_PIN, NEO_GRB + NEO_KHZ800);


char auth[] = "3c3fc83636f148079aea3ad0faff4ed4";
char ssid[] = "CS390N";
char pass[] = "internetofthings";


bool door_open;
bool is_triggered = false;
bool alarm_armed = false;
bool is_red = false;
bool red_state = false;

bool event_flag = false;

String log_event = "";

unsigned long previousMillis = 0;

int calls = 1;
int maxCalls = 10;

const String spreadsheetID = "12vd2gqGDlKXt1H6KC7_yRNtsaz9mz0hOsU3UMQvCz1M";
const String clientSecret = "FJBMzw-G97gS7n4yMSvR1VEJ";
const String refreshToken = "1/zPSHjpDgKxBLa2_JDO1JJt_aoJn9Ks_43kE5DDfm4sk";

void green() {
  pixel.setPixelColor(0, pixel.Color(0,255,0));
  pixel.show();
  is_red = false;
}

void red() {
  pixel.setPixelColor(0, pixel.Color(255,0,0));
  pixel.show();
  is_red = true;
  red_state = true;
}

void lightOff() {
  pixel.setPixelColor(0, pixel.Color(0,0,0));
  pixel.show();
  is_red = false;
}

void blink_off() {
  pixel.setPixelColor(0, pixel.Color(0,0,0));
  pixel.show();
}

void sound_alarm() {
  analogWrite(PIN_BUZZER, 256);
  analogWriteFreq(104);
}

void stop_alarm() {
  analogWrite(PIN_BUZZER, 0);
}

void door() {
  if (digitalRead(REED_PIN) == HIGH) {
    door_open = true;
    log_event = "Door was opened";
    terminal.print(0,0, "Door opened.");
  }
  else {
    door_open = false;
    log_event = "Door was closed";
    terminal.print(0,0, "Door closed.");
  }
  event_flag = true;
}

void trigger_alarm() {
  red();
  sound_alarm();
  Blynk.notify("door open");
  log_event = "Alarm triggered";
  event_flag = true;
  is_triggered = true;
}

void disarm_alarm() {
  lightOff();
  stop_alarm();
  alarm_armed = false;
  is_triggered = false;
  log_event = "Alarm disarmed";
  event_flag = true;
  Blynk.virtualWrite(V3,0);
}

BLYNK_WRITE(V1) {
  int val = param.asInt();
  if(is_triggered) {
    if (val >=1) {
      disarm_alarm();
      alarm_armed = false;
      Blynk.virtualWrite(V3,0);
    }
  }
}

BLYNK_WRITE(V2) {
  int val = param.asInt();
  if(is_triggered) {
    if (val >=1) {
      Blynk.notify("Notify Police");
      log_event = "Police were notified";
      event_flag = true;
    }
  }
}

BLYNK_WRITE(V3) {
  green();
  int val = param.asInt();
  if (val >=1) {
    green();
    alarm_armed=true;
    log_event = "Alarm activated";
    event_flag = true;
  }
  else {
    lightOff();
    alarm_armed=false;
    disarm_alarm();
    log_event = "Alarm deactivated";
    event_flag = true;
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  pinMode(PIN_BUTTON ,INPUT_PULLUP);
  pinMode(REED_PIN, INPUT_PULLUP);
  pinMode(PIN_BUZZER, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(REED_PIN), door, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), disarm_alarm, RISING);

  pixel.begin();
  pixel.setBrightness(48);
  pixel.show();
  door();
 
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
  Blynk.run();

  if (alarm_armed && door_open && !is_triggered) {
    trigger_alarm();
  }

  unsigned long currentMillis = millis();

  if (is_red) {

    if (currentMillis - previousMillis >= 500) {
      previousMillis = currentMillis;
      if (red_state) {
        blink_off();
        red_state = false;
      }
      else {
        red();
        
      }
    }
    
  }

  unsigned long now = millis();
  if (event_flag) {
    //Serial.println("Running InitializeOAuth - Run #" + String(calls++));
    
    TembooChoreo AppendValuesChoreo(client);
    
    // Invoke the Temboo client
    AppendValuesChoreo.begin();
    
    // Set Temboo account credentials
    AppendValuesChoreo.setAccountName("jakeseabass");
    AppendValuesChoreo.setAppKeyName("myFirstApp");
    AppendValuesChoreo.setAppKey("00FZ1KTzTKva8qJKSqXCKbsp7TYVbePg");

    // Identify the Choreo to run
    AppendValuesChoreo.setChoreo("/Library/Google/Sheets/AppendValues");


    // Set Choreo inputs
    AppendValuesChoreo.addInput("Scope", "https://spreadsheets.google.com/feeds/");
    AppendValuesChoreo.addInput("ClientID", "281013315187-9gegl1vnouk2ajfml3sdnptr7nc2j22u.apps.googleusercontent.com");
    AppendValuesChoreo.addInput("ClientSecret", clientSecret);
    AppendValuesChoreo.addInput("RefreshToken", refreshToken);
    AppendValuesChoreo.addInput("SpreadsheetID", spreadsheetID);

    //Data
    String rowData = "[[\"" + String(currentMillis) + "\", \"" + log_event + "\"]]";
    AppendValuesChoreo.addInput("Values", rowData);
    // Run the Choreo; when results are available, print them to serial
    unsigned int returnCode = AppendValuesChoreo.run();

    if (returnCode == 0) {
      Serial.println("Success!");
    } else {
        while (AppendValuesChoreo.available()) {
        char c = AppendValuesChoreo.read();
        Serial.print(c);
      }
      Serial.println();
    }
    
    AppendValuesChoreo.close();
    
    event_flag = false;
  }
  
}




















