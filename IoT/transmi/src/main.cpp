#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_NEO_PIXEL 5  // La broche GPIO16 de l'ESP32 connectée au NeoPixel
#define NUM_PIXELS 8     // Le nombre de LED (pixels) sur la bande LED NeoPixel

Adafruit_NeoPixel NeoPixel(NUM_PIXELS, PIN_NEO_PIXEL, NEO_GRB + NEO_KHZ800);

void setup() {
  NeoPixel.begin();  // Initialiser l'objet bande NeoPixel (OBLIGATOIRE)
}

void loop() {
  NeoPixel.clear();  // Éteindre toutes les LED.

  // Allumer les pixels en vert un par un avec un délai entre chaque pixel
  
for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(255, 0, 0));
    NeoPixel.show(); // Mettre à jour la bande LED NeoPixel

    delay(1000);  // Pause de 1000ms entre chaque pixel
  }

  // Allumer tous les pixels en rouge en même temps pendant deux secondes
  
for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    NeoPixel.setPixelColor(pixel, NeoPixel.Color(0, 255, 0));
  }
  NeoPixel.show();  
  delay(1000);

  // Éteindre tous les pixels pendant une seconde
  
  NeoPixel.clear();
  NeoPixel.show();  
  delay(1000);      
}
