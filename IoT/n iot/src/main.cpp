/* Programme de test sortie Led 27/09/2024 */

#include <Arduino.h>

int brocheLed = 23; // variable global

int temps = 71;

int brocheBouton = 14;

bool etatBouton = false;


void setup() {
  Serial.begin(115200);   // initialisation de la communication USB a la vitesse de 115200 bauds
  pinMode(brocheLed, OUTPUT);   // la broche de la led est déclarée comme une sortie
  pinMode(brocheBouton, INPUT_PULLUP);

}

void loop() {
  etatBouton=digitalRead(brocheBouton);
  digitalWrite(brocheLed, !etatBouton);

if (etatBouton==LOW)
{
  digitalWrite(brocheLed, HIGH);
  Serial.println("La led est allumé");
  delay(temps);
  digitalWrite(brocheLed, LOW);
  Serial.println("la led est éteinte");
  delay(temps);
}
 
}