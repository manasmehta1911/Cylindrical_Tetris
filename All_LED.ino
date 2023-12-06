#include <FastLED.h>
#include <Wire.h>

#define NUM_LEDS 600
#define LED_PIN  4
#define LED_TYPE WS2812
#define COLOR_ORDER GRB
#define FRAMES_PER_SECOND 50
#define MAX_HUE_OFFSET 25

CRGB leds[NUM_LEDS];

void setup() {
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps( 5, 1500);
  Serial.begin(9600);
}

void loop() { 
  for(int i = 0;i < 600;i++){
    leds[i]=CHSV(0,250,255);
  }

  FastLED.show();
  FastLED.delay(1000/FRAMES_PER_SECOND);
}
