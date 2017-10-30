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
case 1: setPixel(LED_TEMOIN, 255, 0, 255);
    break;

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


Effet 3
Affichage en led: 000
Nom du sort : Ténèbre
Effet du sort :
Ce sort crée une zone de ténèbres  impénétrable dans toute une pièce. Si vous connaissez ce sort, vous gagnez la capacité passive de voir dans les ténèbres. Si la zone de ténèbres est touchée par une lumière purificatrice, elle est dissipée.
Ce sort ne fonctionne pas en extérieur.
Description effet : 
Allume en violet le pied du bâton
effet très simple

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

Effet 5
Affichage en led: 000
Nom du sort : Amitié morts vivants
Effet du sort :
En lançant ce sort sur un mort vivant, celui ci devient votre ami, il ne vous attaquera plus mais ne vous obéira pas forcément.
Description effet : 
Rayon violet qui part du bas jusqu’en haut et laisse allumé le haut

Effet 6
Affichage en led: 000
Nom du sort : Désenchantement
Effet du sort :
Vous êtes capable de libérer l'étincelle de vie enfermée dans un objet magique.
Cela détruit la magie de l'objet.
Description effet : 
Faire clignoter très doucement le haut du bâton, s’allume lentement, s’éteint lentement *5

Effet 7
Affichage en led: 000
Nom du sort : Désorientation
Effet du sort :
vous désorientez votre cible qui est alors prise de vertige et doit poser un genou à terre, elle peut ensuite se relever.
Description effet : 
Stroboscope violet et blanc haut du bâton


Effet 8
Affichage en led: 000
Nom du sort : La mort peut attendre
Effet du sort :
La cible n'agonisera pas la prochaine fois qu'elle tombera, il restera dans le coma à attendre. Le sort reste actif jusqu'à utilisation ou jusqu'au prochain repas. Le magicien peut lancer autant de fois ce sort qu'il le souhaite sur plusieurs personnes à la fois.
Description effet : 
lueure blanche en haut du bâton?

