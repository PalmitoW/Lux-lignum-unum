#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// On a Trinket or Gemma we suggest changing this to 1
#define PIN            1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      42

//RANDOM POWER
#define RANDPWR         1

int ledFadeTime = 5;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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

  strip.begin();
  ColorSet(strip.Color(255, 0, 255));
  strip.show(); // Initialize all pixels to 'off'
  delay(100);
}

void loop() {
  breathRand();
  //rgbFadeInAndOut(ledFadeTime);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

// Set all pixels to a color (synchronously)
void ColorSet(uint32_t color)
{
    for (int i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, color);
    }
    strip.show();
}

// Returns the Red component of a 32-bit color
uint8_t Red(uint32_t color)
{
    return (color >> 16) & 0xFF;
}

// Returns the Green component of a 32-bit color
uint8_t Green(uint32_t color)
{
    return (color >> 8) & 0xFF;
}

// Returns the Blue component of a 32-bit color
uint8_t Blue(uint32_t color)
{
    return color & 0xFF;
}

byte wheelPixelsCurrent[NUMPIXELS];
byte wheelPixelsNext[NUMPIXELS];

#define TOTAL_STEPS 100
void breathRand() {
    // Init next color
    for(int i=0; i < NUMPIXELS; i++) {
      wheelPixelsNext[i] = constrain(170 + random(120) - 60, 0, 255);
    }

    for(int Index=0; Index < TOTAL_STEPS; Index++) {
      for(int i=0; i < NUMPIXELS; i++) {
        uint32_t colorCurrent  = Wheel(wheelPixelsCurrent[i]);
        uint32_t colorNext     = Wheel(wheelPixelsNext[i]);
        
        uint8_t red = ((Red(colorCurrent) * (TOTAL_STEPS - Index)) + (Red(colorNext) * Index)) / TOTAL_STEPS;
        uint8_t green = ((Green(colorCurrent) * (TOTAL_STEPS - Index)) + (Green(colorNext) * Index)) / TOTAL_STEPS;
        uint8_t blue = ((Blue(colorCurrent) * (TOTAL_STEPS - Index)) + (Blue(colorNext) * Index)) / TOTAL_STEPS;

        strip.setPixelColor(i, strip.Color(red, green, blue));
      }

      strip.show();
      delay(20);
    }

    // Copy to previous
    for(int i=0; i < NUMPIXELS; i++) {
      wheelPixelsCurrent[i] = wheelPixelsNext[i];
    }
}
