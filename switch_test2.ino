// Baton de GN
// #ProjetLuxLignumUnum

/*
*   Test interrupteurs part 2
*   Test des fonctions select ++, select --
*   Test de la fonction floor
*   Info: Delay est en milli secondes
*/

/******************** INTRODUCTION ENTREES SORTIES ********************/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define   BUTTON_PIN_SELECT  0    // Bouton du haut : select
#define   BUTTON_PIN_START   2    // Bouton du bas : start
#define   BUTTON_PIN_FLOOR   4    // Bouton pied de baton

#define   PIXEL_PIN          1    // Digital IO pin connected to the NeoPixels.

#define   NUM_LEDS           42
// baton d'alexis : led temoin : 17 & 18
#define   LED_TEMOIN         17

#define   MAXCASE            3

//int ledFadeTime = 5;

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

/******************** INTRODUCTION DES VARIABLES ********************/

bool oldSelect = LOW;
bool oldStart = LOW;
bool oldFloor = LOW;
int showType = 0;
//int timeCounter =0;

/*************************** BOUCLE SETUP ***************************/

void setup() { 
  pinMode(BUTTON_PIN_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_PIN_START, INPUT_PULLUP);
  pinMode(BUTTON_PIN_FLOOR, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  delay(100);
}

/************************ BOUCLE EST BOUCLEE ************************/

/*
* A FAIRE
* Objectifs:
*OK* l’interrupteur SELECT monte le programme
* l'interrupteur SELECT + FLOOR descend le pogramme OK A TESTER
* l’interrupteur START lance le programme OK A TESTER
* une led au dessus de la main indique sur quel programme on est OK A TESTER
* l’interrupteur FLOOR lance un petit effet floorShow (toujours le même?) OK A TESTER
*/


void loop() { 
  selectLoop();
  startLoop();
  floorLoop();
/*  timeCounter++;
  if(timeCounter==10000){
	timeCounter=0;
	timeShow();
  }
*/
}
/*************************** BUTTON LOOP ***************************/
void selectLoop(void){
    bool newSelect = digitalRead(BUTTON_PIN_SELECT);
    bool newFloor = digitalRead(BUTTON_PIN_FLOOR);
   // Check if state changed from low to high (button press).
  if (newSelect == HIGH && oldSelect == LOW) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still high after debounce.
    newSelect = digitalRead(BUTTON_PIN_SELECT);
    newFloor = digitalRead(BUTTON_PIN_FLOOR);
    if (newSelect == HIGH) {
      
      if (newFloor == LOW){
        showType++;
        if (showType > MAXCASE)
          showType=0;
//        selectShow(showType);
      }else{
        if(showType == 0){
          showType=MAXCASE;
        }else{
          showType--;
        }
 //       selectShow(showType);
      }
	}
  }
  oldSelect = newSelect;
  oldFloor = newFloor;
  selectShow(showType);
}

void startLoop(void){
  bool newStart = digitalRead(BUTTON_PIN_START);
  // Check if state changed from low to high (button press).
  if (newStart == HIGH && oldStart == LOW) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still high after debounce.
    newStart = digitalRead(BUTTON_PIN_START);
    if (newStart == HIGH) {
          startShow(showType);
    }
  }
  oldStart = newStart;
}
  
void floorLoop(void){
  bool newFloor = digitalRead(BUTTON_PIN_FLOOR);
  // Check if state changed from low to high (button press).
  if (newFloor == HIGH && oldFloor == LOW) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still high after debounce.
    newFloor = digitalRead(BUTTON_PIN_FLOOR);
    if (newFloor == HIGH) {
      floorShow();
    }
  }
  oldFloor = newFloor;
}
 
/*************************** SWITCH CASES ***************************/

/******** SELECT SHOW --> Affiche la led temoin ********/
void selectShow(int i){
  switch(i){
    case 0: setPixel(LED_TEMOIN, 0, 0, 0);
	  setPixel(LED_TEMOIN+1, 0, 0, 0);  
    break;
    case 1: setPixel(LED_TEMOIN, 255, 0, 0);
	  setPixel(LED_TEMOIN+1, 255, 0, 0);
    break;
    case 2: setPixel(LED_TEMOIN, 0, 255, 0);
	  setPixel(LED_TEMOIN+1, 0, 255, 0);
    break;
    case 3: setPixel(LED_TEMOIN, 0, 0, 255);
	  setPixel(LED_TEMOIN+1, 0, 0, 255);
    break;
  }
  showStrip();
}

/******** START SHOW --> effectue le programme ********/

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 0);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 10);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 10);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 10);  // Blue
            break;
  }
}
/******** FLOOR SHOW --> effet simple ********/
void floorShow(void){
      colorWipe(strip.Color(255, 255, 255), 10);  // White
	delay(20);
	setAll(0,0,0);
}
	
/******** TIME SHOW --> effet simple ********/
/*
void timeShow(void){
      colorWipe(strip.Color(255, 0, 255), 10);  // Pink
      delay(200);
      startShow(showType);
}	
*/
/*************************** BOUCLE EFFETS DE BASE ***************************/

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
    if(startBreak()==1){
	break;
    }
  }
}
/**************************** FONCTION PARAMETRES **********************/

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

bool startBreak(){
  bool newStart = digitalRead(BUTTON_PIN_START);
  bool breakBool = 0;
  // Check if state changed from low to high (button press).
  if (newStart == HIGH && oldStart == LOW) {
    // Short delay to debounce button.
    delay(10);
    // Check if button is still high after debounce.
    newStart = digitalRead(BUTTON_PIN_START);
    if (newStart == HIGH) {
          breakBool=1;
    }
    return breakBool; 
  }
}
