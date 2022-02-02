#include <FastLED.h>              
#define NUMLEDS 37             
#define DATA_PIN 3                
#define SENSITIVITY 100          
#define MAX_BRIGHTNESS 255        
#define ENVELOPE_PIN A0           
#define SATURATION 100            
#define MINVAL 60
#define HUE_INIT 10
#define HUE_CHANGE 1
 
CRGB leds[NUMLEDS];
byte brightness[NUMLEDS];
byte hue[NUMLEDS];
int analogVal;
int DELAY;
 
void setup() { 
  Serial.begin(1); 
  pinMode(ENVELOPE_PIN, INPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUMLEDS);
 
  for(int i = 0; i <= NUMLEDS; i++){
    brightness[i] = 0;
    hue[i] = 0;
  }
  for(int i=0; i <= NUMLEDS; i++)  
  {
  leds[i] = CRGB::Black;
  }
  FastLED.show();
}
void loop() {
  analogVal = analogRead(ENVELOPE_PIN);
 
  if(analogVal > SENSITIVITY)
  analogVal = SENSITIVITY;
 
  if(analogVal < MINVAL)
  analogVal = 0;
   BrightnessReactive();
  FastLED.show();
}
void BrightnessReactive(){
  byte val = map(analogVal, 0, SENSITIVITY+1, 0, MAX_BRIGHTNESS);
  byte hue = HUE_INIT;
  for(int i = 0; i <= NUMLEDS; i++){
    leds[i] = CHSV(hue += HUE_CHANGE, SATURATION, val);
  }
}
 
