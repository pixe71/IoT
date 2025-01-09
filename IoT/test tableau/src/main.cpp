#include <Arduino.h>

float tabNotes[10];
int nbNotes;
float noteSaisies, somme;

void setup() {
  Serial.begin(115200);

}

void loop() {

  if(Serial.available()){
    nbNotes++;
    noteSaisies=Serial.parseFloat();
    tabNotes[nbNotes]=noteSaisies;
  }

  float tabNotes[10]; 
  tabNotes [0] = 16.25;
  tabNotes [1] = 4.5; 
  tabNotes [2] = 40.0; 
  tabNotes[3] = 0.0; 
  tabNotes [4] = 15.75;
  tabNotes [5] = 5; 
  tabNotes [6] = 20.0; 
  tabNotes [7] = 10.0; 
  tabNotes [8] = 12.5; 
  tabNotes [9] = 7.5; 

   for (int i = 0; i < 10; i++) { 
    Serial.print("tabNotes["); 
    Serial.print(i); 
    Serial.print("] = "); 
    Serial.println(tabNotes[i]); 
  } 
  float somme = 0; 
  for (int i = 0; i < 10; i++) { 
    somme = somme + tabNotes[i];
  }
  float moyenne = somme / 10; 
  Serial.print("La moyenne des notes est : "); 
  Serial.println(moyenne);

  float min = tabNotes[0]; 
  int minIndex = 0; 
  for (int i = 1; i < 10; i++) { 
    if (tabNotes[i] < min) { 
      min = tabNotes[i]; 
      minIndex = i; 
    }
  }
  Serial.print("La note minimale est : "); 
  Serial.println(min); 
  Serial.print("(MIN) Elle se trouve à la ligne : "); 
  Serial.println(minIndex); 

  float max = tabNotes[0]; 
  int maxIndex = 0; 
  for (int i = 1; i < 10; i++) { 
    if (tabNotes[i] > max) { 
      max = tabNotes[i]; 
      maxIndex = i; 
    }
  
  Serial.print("La note maximale est : "); 
  Serial.println(max); 
  Serial.print("(MAX) Elle se trouve à la ligne : "); 
  Serial.println(maxIndex); 
  nbNotes++;

  }

}