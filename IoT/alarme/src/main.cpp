/* Programme d'alarme 04/10/2024 */

#include <Arduino.h>

int brocheBP1=14;
int brocheBP2=13;
int brocheLed=23;
bool etatAlarme, etatBP1, etatBP2;


void setup() {
  Serial.begin(115200);   // initialisation de la communication USB a la vitesse de 115200 bauds  
  pinMode(brocheBP1, INPUT_PULLUP);
  pinMode(brocheBP2, INPUT_PULLUP);
  pinMode(brocheLed, OUTPUT);   // la broche de la led est déclarée comme une sortie

}

void loop() {
  etatBP1=digitalRead(brocheBP1);   // inverse car l'entrée est en PULL-UP
  etatBP2=digitalRead(brocheBP2);
  etatAlarme=etatBP1||etatBP2;    // l'alarme s'active si un des deux boutons est activé, fonction "OU"
  digitalWrite(brocheLed,etatAlarme);
 
}
