#include <Arduino.h>
#include <TM1637Display.h>
#define CLK 26
#define DIO 27
TM1637Display display(CLK, DIO);
unsigned long startTime;
void setup() {
  Serial.begin(115200);
  display.setBrightness(0x0f); // Réglage de la luminosité de l'afficheur
  startTime = millis(); // Enregistrer le temps de démarrage
}
void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsedTime = currentTime - startTime;
  // Convertir le temps écoulé en minutes et secondes
  int seconds = (elapsedTime / 1000) % 60;
  int minutes = (elapsedTime / 60000) % 60;
  // Afficher le temps écoulé sur le TM1637
  int displayTime = (minutes * 100) + seconds;
  display.showNumberDecEx(displayTime, 0b01000000, true); // Afficher MM:SS avec deux-points
  delay(1000); // Mettre à jour toutes les secondes
}