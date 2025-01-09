#include <Arduino.h>

int P1=14;
int P2=13;
int clav=33;
int clef=26;
int sirene=23;
bool etatP1, etatP2, etatsirene, etatclef, etatclav;


void setup() {
  Serial.begin(115200);
  pinMode(P1, INPUT_PULLUP);
  pinMode(P2, INPUT_PULLUP);
  pinMode(clav, INPUT_PULLUP);
  pinMode(clef, INPUT_PULLUP);
  pinMode(sirene, OUTPUT);

}

void loop() {
  etatP1=!digitalRead(P1); 
  etatP2=!digitalRead(P2);
  etatclav=!digitalRead(clav);
  etatclef=!digitalRead(clef);

  etatsirene=etatclav&&etatclef&&(etatP1||etatP2);
  digitalWrite(sirene, etatsirene);

}
