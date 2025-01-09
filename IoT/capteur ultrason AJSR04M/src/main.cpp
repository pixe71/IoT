// Luc Tournié

#include <Arduino.h>

const int trigPin = 5;
const int echoPin = 18;

// définir la vitesse du son en cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceM;
float distanceInch;
float volumeL;


void setup() {
  Serial.begin(115200); // Démarre la communication série
  pinMode(trigPin, OUTPUT); // Définit le trigPin comme une sortie
  pinMode(echoPin, INPUT); // Définit le echoPin comme une entrée
}

void loop() {
  
  // Met le trigPin à LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Met le trigPin à l'état HIGH pendant 10 microsecondes
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Lit le echoPin, retourne le temps de trajet de l'onde sonore en microsecondes
  duration = pulseIn(echoPin, HIGH);

  // Calcule la distance
  distanceM = duration * SOUND_SPEED / 2/100;
  
  // Calcule le volume en Litres

  volumeL = distanceM * 3.14 * 2.15 * 2.15 / 4 * 1000;

  // Affiche la distance dans le moniteur série
  Serial.print("Distance (M) : ");
  Serial.println(distanceM);

  // Afficher le volume dans le moniteur série

  Serial.print("Volume (L) : ");
  Serial.println(volumeL);

  delay(1000);
}