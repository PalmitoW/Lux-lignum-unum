// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN    1    // Digital IO pin connected to the NeoPixels.

#define NUM_LEDS 42
#define LED_TEMOIN 18

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      showType++;
      if (showType > 9)
        showType=0;
      startShow(showType);
    }
  }

  // Set the last button state to the old state.
  oldState = newState;
}
/*************************** SWITCH CASES ***************************/

/******** SELECT SHOW --> Affiche la led temoin ********/
void selectShow(int i){
  switch(i){
    case 0: setPixel(LED_TEMOIN, 0, 0, 0);
    break;
    case 1: setPixel(LED_TEMOIN, 100, 0, 100);
    break;
    case 2: setPixel(LED_TEMOIN, 255, 0, 125);
    break;
    case 3: setPixel(LED_TEMOIN, 255, 0, 125);
    break;
    case 4: setPixel(LED_TEMOIN, 0, 0, 255);
    break;
    case 5: setPixel(LED_TEMOIN, 0, 255, 0);
    break;
    case 6: setPixel(LED_TEMOIN, 0, 0, 255);
    break;
    case 7: setPixel(LED_TEMOIN, 255, 255, 255);
    break;
    case 8: setPixel(LED_TEMOIN, 255, 255, 255);
    break;
  }
}

/******** START SHOW --> effectue le programme ********/

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: dagueDombre(10,20,50);
            break;
    case 2: visageCauchemar(50);
            break;
    case 3: tenebre(50);
            break;
    case 4: manteauDombre();
            break; 
    case 5: amitieMortsVivants(50);
            break;
    case 6: desenchantement(50);
            break;
    case 7: desorientation(20);
            break;
    case 8: laMortPeutAttendre();
            break;
  }
}
/*
Effet 1
Affichage en led: 000
Nom du sort : Dague d’Ombre
Effet du sort : Permet d'infliger 2 points de dégâts au toucher à main nu, les dégâts traverse l'armure.
Vous devez avoir la main nu, ne pas porter de gant.
Ce sort ne peut être utilisé en combat, ne vous jetez pas sur un adversaire pour le toucher de votre main.
Description effet : 
Zone de violet tourne autour des interrupteurs
fonction d’allumage de leds défini, augmenter l'intensite rapidement et diminution doucement
*/
void dagueDombre(uint8_t led1, uint8_t led2, uint8_t wait){
    for(uint8_t j=0; j<255 ; j++){
        for(uint8_t i=led1; i<led2; i++) {
        strip.setPixelColor(i, j, 0, j);
        strip.show();
        }
    delay(wait);
    }
    for(uint8_t j=255; j>0 ; j--){
        for(uint8_t i=led1; i<led2; i++) {
        strip.setPixelColor(i, j, 0, j);
        strip.show();
        }
    delay(wait*4);
    }
}

/*
Effet 2
Affichage en led: 000
Nom du sort : Visage de cauchemar
Effet du sort :
Lors du lancement de ce sort, désignez -dans un cercle de 3 mètres de rayon autour de vous- autant de personnes que vous le souhaitez. Aux yeux de ces cibles, votre visage disparaît sous un masque d'ombre évoquant un néant insondable et elles sont sous l'effet d'une peur.
Description effet : 
Petits points violets et rouge qui montent doucement puis tête du bâton qui clignote en rouge et violet
*/



void visageCauchemar(uint8_t wait){
    for(uint8_t i=NUM_LEDS ; j>4 ; i=i-2){
        strip.setPixelColor(i, 255, 0, 255);
        strip.setPixelColor(i-1, 255, 0, 0);
        strip.setPixelColor(i+1, 0, 0, 0);
        strip.setPixelColor(i+2, 0, 0, 0);
        strip.show();
        delay(wait);
    }
    for(uint8_t i=0 ; i<20 ; i++){                                 //strob ON
        for(uint8_t j=0 ; j<10 ; i=i+2){
            strip.setPixelColor(i, 255, 0, 255);
            strip.setPixelColor(i-1, 255, 0, 0);
            strip.show();
        }
        delay(wait);
        for(uint8_t j=0 ; j<10 ; i++){                             //strobe OFF
            strip.setPixelColor(i, 0, 0, 0);
            strip.show();
        }
        delay(wait);
    }
}

/*
Effet 3
Affichage en led: 000
Nom du sort : Ténèbre
Effet du sort :
Ce sort crée une zone de ténèbres  impénétrable dans toute une pièce. Si vous connaissez ce sort, vous gagnez la capacité passive de voir dans les ténèbres. Si la zone de ténèbres est touchée par une lumière purificatrice, elle est dissipée.
Ce sort ne fonctionne pas en extérieur.
Description effet : 
Allume en violet le pied du bâton
effet très simple
*/


void tenebre(uint8_t wait){
    for(uint8_t i=NUM_LEDS ; i>30 ; i--){
        strip.setPixelColor(i, 255, 0, 255);
    }
    strip.show();
    delay(wait);
    for(uint8_t i=NUM_LEDS ; i>30 ; i--){
        strip.setPixelColor(i, 0, 0, 0);
    }
    strip.show();
}

/*
Effet 4
Affichage en led: 000
Nom du sort : Manteau d’ombre
Effet du sort :
Vous pouvez devenir invisible, vous drapant dans des ombres magiques.
Vous ne pouvez pas vous déplacer avec ce sort.
Vous pouvez le maintenir aussi longtemps que vous le souhaitez.
Description effet : 
Les leds brillent comme des étoiles en violet de façon disparate sur le bâton
→ code quentin?
*/


void manteauDombre(void){

}

/*
Effet 5
Affichage en led: 000
Nom du sort : Amitié morts vivants
Effet du sort :
En lançant ce sort sur un mort vivant, celui ci devient votre ami, il ne vous attaquera plus mais ne vous obéira pas forcément.
Description effet : 
Rayon violet qui part du bas jusqu’en haut et laisse allumé le haut
*/


void amitieMortsVivants(uint8_t wait){
 for(uint8_t i=NUM_LEDS ; j>0 ; i--){
        strip.setPixelColor(i, 255, 0, 255);
        strip.setPixelColor(i+10, 0, 0, 0);
        strip.show();
        delay(wait);
    }
    delay(wait*10);
}

/*
Effet 6
Affichage en led: 000
Nom du sort : Désenchantement
Effet du sort :
Vous êtes capable de libérer l'étincelle de vie enfermée dans un objet magique.
Cela détruit la magie de l'objet.
Description effet : 
Faire clignoter très doucement le haut du bâton, s’allume lentement, s’éteint lentement *5
*/


void desenchantement(uint8_t wait){
for(uint8_t k=0; k<5 ; k++){
    for(uint8_t j=0; j<255 ; j++){
        for(uint8_t i=0; i<10; i++) {
            strip.setPixelColor(i, j, 0, j);
            strip.show();
        }
        delay(wait);
    }
    for(uint8_t j=255; j>0 ; j--){
        for(uint8_t i=led1; i<led2; i++) {
            strip.setPixelColor(i, j, 0, j);
            strip.show();
        }
        delay(wait);
    }
}

/*
Effet 7
Affichage en led: 000
Nom du sort : Désorientation
Effet du sort :
vous désorientez votre cible qui est alors prise de vertige et doit poser un genou à terre, elle peut ensuite se relever.
Description effet : 
Stroboscope violet et blanc haut du bâton
*/


void desorientation(uint8_t wait){
    for(uint8_t i=0 ; i<20 ; i++){                                 //strob ON
        for(uint8_t j=0 ; j<10 ; i=i+2){
            strip.setPixelColor(i, 255, 0, 255);
            strip.setPixelColor(i-1, 255, 255, 255);
            strip.show();
        }
        delay(wait);
        for(uint8_t j=0 ; j<10 ; i++){                             //strobe OFF
            strip.setPixelColor(i, 0, 0, 0);
            strip.show();
        }
        delay(wait);
    }
}
    
/*
Effet 8
Affichage en led: 000
Nom du sort : La mort peut attendre
Effet du sort :
La cible n'agonisera pas la prochaine fois qu'elle tombera, il restera dans le coma à attendre. Le sort reste actif jusqu'à utilisation ou jusqu'au prochain repas. Le magicien peut lancer autant de fois ce sort qu'il le souhaite sur plusieurs personnes à la fois.
Description effet : 
lueure blanche en haut du bâton?

*/


void laMortPeutAttendre(uint8_t wait){

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
