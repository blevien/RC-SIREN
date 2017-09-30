#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEO_PIN 3
#define RX_PIN 8

unsigned long pulses = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, NEO_PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  pinMode(RX_PIN, INPUT);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  pulses = pulseIn(RX_PIN, HIGH);

  if(pulses < 1300)       //Bottom Position
  {
    siren(200);
  }
  else if (pulses > 1700) // Top Position
  {
    colorWipe(strip.Color(0, 0, 0),0);
  }
  else                   //Middle Position
  {
    colorWipe(strip.Color(255, 255, 255),0);
  }
  
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void siren(uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
    strip.show();
    delay(wait);
    
    for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  strip.show();
  delay(wait);
}


void allOff() {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(0, 0);
  }
  strip.show();
  
}

//Theatre-style crawling lights.
void theaterChase(uint8_t wait) {

    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, strip.Color(0, 0, 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, strip.Color(255, 0, 0));        //turn every third pixel off
      }
    }
}
