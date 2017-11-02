// Baton de GN
// #ProjetLuxLignumUnum
// ATtiny85 on-board, 8K of flash, 512 byte of SRAM, 512 bytes of EEPROM

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

#define   MAXCASE            8

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
int floorType = 0;
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
 switch(i){
    case 0: setPixel(LED_TEMOIN, 100, 0, 0); // Rouge pour dire que c'est allumé
    break;
    case 1: setPixel(LED_TEMOIN, 175, 0, 255); // dague d'ombre
            setPixel(LED_TEMOIN+1, 175, 0, 255);
    break;
    case 2: setPixel(LED_TEMOIN, 175, 0, 255); // visage cauchemar
            setPixel(LED_TEMOIN+1, 255, 0, 0);
    break;
    case 3: setPixel(LED_TEMOIN, 0, 0, 0); // ténèbre
            setPixel(LED_TEMOIN+1, 175, 0, 255);
    break;
    case 4: setPixel(LED_TEMOIN, 0, 0, 125); // manteau d'ombre
            setPixel(LED_TEMOIN+1, 100, 0, 125);
    break;
    case 5: setPixel(LED_TEMOIN, 0, 255, 0); // amitié mort vivant
            setPixel(LED_TEMOIN+1, 0, 0, 0);
    break;
    case 6: setPixel(LED_TEMOIN, 175, 0, 255); // désenchantement
            setPixel(LED_TEMOIN+1, 0, 0, 0);
    break;
    case 7: setPixel(LED_TEMOIN, 255, 255, 255); // désorientation
            setPixel(LED_TEMOIN+1, 175, 0, 255);
    break;
    case 8: setPixel(LED_TEMOIN, 255, 255, 255); // la mort peut attendre
            setPixel(LED_TEMOIN+1, 100, 0, 100);
    break;
  }
  showStrip();
}

/******** START SHOW --> effectue le programme ********/

void startShow(int i) {
  switch(i){
case 0: setAll(0,0,0);
            break;
    case 1: dagueDombre(10, 20, 5); // zone violette proche main
            break;
    case 2: visageCauchemar(100); // strob violet et blanc
            break;
    case 3: tenebre(50); // bas du baton en violet
            break;
    case 4: manteauDombre(); // brille comme des étoiles? quentin?
            break; 
    case 5: amitieMortsVivants(50); // trait de lumière verte
            break;
    case 6: desenchantement(4); // s'allume et s'éteint lentement wait4 --> allume 1 sec
            break;
    case 7: desorientation(20); // strob violet et blanc haut baton
            break;
    case 8: laMortPeutAttendre(10); // lueure blanche haut baton à coder
            break;
  }
}
/******** FLOOR SHOW --> effet simple ********/
void floorShow(void){
      colorWipe(strip.Color(255, 255, 255), 10);  // White
	delay(20);
	setAll(0,0,0);
    switch(floorType){
	    case 0: traitCouleur(strip.Color(255, 255, 255), 42, 28);
	    break;
	    case 1: traitCouleur(strip.Color(255, 0, 0), 42, 28);
	    break;
	    case 2: traitCouleur(strip.Color(255, 0, 0), 28, 14);
	    break;
	    case 3: traitCouleur(strip.Color(255, 0, 0), 14, 0);
	    break;
	    case 4: traitCouleur(strip.Color(0, 255, 0), 42, 28); 
	    break;
	    case 5: traitCouleur(strip.Color(0, 255, 0), 28, 14); 
	    break;
	    case 6: traitCouleur(strip.Color(0, 255, 0), 14, 0); 
	    break;
	    case 7: traitCouleur(strip.Color(0, 0, 255), 42, 28); 
	    break;
	    case 8: traitCouleur(strip.Color(0, 0, 255), 28, 14); 
	    break;
	    case 9: traitCouleur(strip.Color(0, 0, 255), 14, 0); 
	    break; 
    }
    floorType ++;
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
  for(uint8_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
    if(startBreak()==1){
	break;
    }
  }
}

// effet trait de couleur pour floorshow

void traitCouleur(uint32_t c, uint8_t istart, uint8_t istop){
	for (uint8_t i=istart; i<istop; i--){
		strip.setPixelColor(i, c);
		strip.show();
		delay(50);
	}
	for (uint8_t i=istart; i<istop; i--){
		strip.setPixelColor(i, 0);
		strip.show();
		delay(50);
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
