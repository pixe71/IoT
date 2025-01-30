#include "Arduino.h"
// biliothèques pour le serveur web
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Adafruit_AHTX0.h>

#define LED_BLEUE 2 // Broche de la LED bleue

// Identifiants du réseau WiFi
const char* ssid = "Wifi_Iot215";
const char* password = "CIEL1234#+";

// Nom du serveur
const char* hostname = "IoT-ESP32 Luc";

// Configuration de l'IP fixe
IPAddress local_IP(192, 168, 1, 184); // Adresse IP fixe
IPAddress gateway(192, 168, 1, 1);    // Passerelle
IPAddress subnet(255, 255, 255, 0);   // Masque de sous-réseau
IPAddress primaryDNS(8, 8, 8, 8);     // DNS primaire
IPAddress secondaryDNS(8, 8, 4, 4);   // DNS secondaire

// Création du serveur web asynchrone sur le port 80
AsyncWebServer server(80);

// Variables pour les valeurs à afficher sur la page web
String mesureHTML;
String texteHTML;
String tempHTML;
String humidityHTML;

// Page HTML à afficher
const char page_index[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="refresh" content="3"> <!-- Rafraîchit la page toutes les 3 secondes -->
    <title>Capteur IOT </title>
    <style>
        /* Réinitialisation des marges et padding */
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }

        /* Fond général de la page */
        body {
            font-family: 'Arial', sans-serif;
            background-color: #f4f4f9;
            color: #333;
            margin: 40px auto;
            max-width: 800px;
        }

        /* Titre principal */
        h1 {
            color: #504658;
            text-align: center;
            font-size: 2.5em;
            margin-bottom: 20px;
        }

        /* Titre secondaire */
        h2 {
            color: #b84a01;
            text-align: center;
            font-size: 1.5em;
            margin: 20px 0;
        }

        /* Section contenant les informations du capteur */
        .donneecapteur {
            background-color: #fff;
            padding: 15px;
            border-radius: 8px;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
            margin-bottom: 20px;
        }

        /* Label des données */
        .donneecapteur label {
            font-weight: bold;
            display: inline-block;
            width: 120px;
            color: #555;
        }

        /* Valeur des données */
        .donneecapteur span {
            font-weight: normal;
            display: inline-block;
            color: #333;
        }

        /* Ajouter une marge pour le nom */
        .nom {
            color: #70037a;
            text-align: center;
            font-size: 1.5em;
            margin-top: 30px;
            font-weight: 600;
        }

        /* Div contenant l'adresse IP */
        div {
            text-align: left;
        }
        
        /* Stylisation des différentes données (Température, Humidité, etc.) */
        .donneecapteur span#temperature {
            color: #d9534f;
        }

        .donneecapteur span#humidite {
            color: #5bc0de;
        }

        .donneecapteur span#distance {
            color: #f0ad4e;
        }

        .donneecapteur span#ip {
            color: #5cb85c;
        }
    </style>
</head>
<body>
    <h1>Capteur IOT</h1>
    <div class="donneecapteur">
        <label for="temperature">Température:</label>
        <span id="temperature">%MESURE%</span> °C
    </div>
    <div class="donneecapteur">
        <label for="humidite">Humidité:</label>
        <span id="humidite">%HUMIDITY%</span> 
    </div>
    <div class="donneecapteur">
        <label for="distance">Message:</label>
        <span id="distance">%MESSAGE%</span>
    </div>
    <h2>Adresse IP</h2>
    <div class="donneecapteur">
        <label for="ip">IP:</label>
        <span id="ip">--</span>
    </div>
    <h1 class="nom">Tournié</h1>
</body>
</html>

)rawliteral";

const char page_404[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Erreur 404</title>
  <meta charset="UTF-8">
</head>
<body style="display: flex; justify-content: center; align-items: center; height: 100vh; text-align: center;">
  <div>
    <h1>Erreur 404</h1>
    <p>Page inconnue</p>
  </div>
</body>
</html>
)rawliteral";

// Fonction pour remplacer les variables dans la page HTML signalées par %VAR%
String fctVariablesPageHTML(const String& var) {
  if (var == "MESURE") {
    return mesureHTML;
  }
  else if (var == "MESSAGE") {
    return texteHTML;
  }
  return String();

  if (var == "HUMIDITY") {
    return humidityHTML;
  }
  else if (var == "MESSAGE") {
    return texteHTML;
  }
  return String();
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_BLEUE, OUTPUT); 
  // Configuration de l'IP fixe si nécessaire (décommenter les lignes ci-dessous)
  /*
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Erreur de configuration de l'IP fixe");
  }
  */

  WiFi.begin(ssid, password); // Connexion au réseau WiFi
  // Attente de la connexion
  Serial.println("Connexion au WiFi...");
  while (WiFi.status() != WL_CONNECTED) { 
    digitalWrite(LED_BLEUE, LOW); 
    delay(100);
    digitalWrite(LED_BLEUE, HIGH); 
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connecté au WiFi");
  
  // Affichage des informations réseau
  String ipAddress = WiFi.localIP().toString();
  Serial.println("Adresse IP : "+ipAddress);
  String macAddress = WiFi.macAddress();
  Serial.println("Adresse MAC : "+macAddress);
  int rssiDBm = WiFi.RSSI(); // Niveau de réception en dBm (Received Signal Strength Indicator)
  Serial.println("Niveau de réception (RSSI) : "+String(rssiDBm)+" dBm");
  float rssiWatts = pow(10.0, (float (rssiDBm) - 30.0) / 10.0); // conversion du RSSI en mW
  Serial.println("Puissance du signal : "+String(rssiWatts*1000,10)+" mW");

  // Configuration du nom d'hôte
  WiFi.setHostname(hostname);
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){ // Gestion de la requête HTTP GET sur la racine du serveur
    request->send_P(200, "text/html", page_index, fctVariablesPageHTML); // Envoi de la page HTML page_index 
                                                                         // et utilisant la fonction fctVariablesPageHTML
  });
    // Gestion de la requête 404
  server.onNotFound([](AsyncWebServerRequest *request){
    request->send_P(404, "text/html", page_404);
  });
  server.begin(); // Démarrage du serveur web
  Serial.println("Serveur actif");
}

void loop() {
  // Lire la mesure du capteur
  int valMesure = random(0, 100);
  mesureHTML = String(valMesure);
  // déterminer le texte à afficher
  if (valMesure < 34) {
    texteHTML = "Valeur faible";
  } else if (valMesure < 75) {
    texteHTML = "Valeur normale";
  } else {
    texteHTML = "Valeur élevée";
  }
  // Attendre 2 secondes avant de renouvler les variables
  delay(2000);
}

