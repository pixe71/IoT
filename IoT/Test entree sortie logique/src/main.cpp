#include <Arduino.h>


void setup() {
  Serial.begin(115200); // déclaration échanges USB
  /* programme permettant d'allumer la led bleu le 20/06/2024 */
  /* déclaration de la broche de la led bleu en sortie */
  pinMode(2, OUTPUT);

  /* activation de la sortie de la led bleu*/


  Serial.println("fin de programme");
}

void loop() {

  digitalWrite(2, 1);
  delay(1000);
  digitalWrite(2, 0);
  delay(1000);
  
}
