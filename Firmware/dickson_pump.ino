#include <SPI.h>
#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>


char ssid[] = "";
char pass[] = "";


#define FIREBASE_HOST ""
#define FIREBASE_AUTH ""


FirebaseData firebaseData;


const int pinCK = 2;
const int pinCK_INV = 3;
const int pinSensore = A0;


unsigned long previousMicros = 0;
long halfPeriod = 500; 
bool clockState = false;


unsigned long previousMillis = 0;
const long intervalFirebase = 1500;

void setup() {
  Serial.begin(115200);
  
  pinMode(pinCK, OUTPUT);
  pinMode(pinCK_INV, OUTPUT);
  
  digitalWrite(pinCK, LOW);
  digitalWrite(pinCK_INV, HIGH);

  Serial.print("Connessione al Wi-Fi...");
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nConnesso al Wi-Fi!");
  analogReadResolution(12);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH, ssid, pass);
  Firebase.reconnectWiFi(true);
  Serial.println("Connesso a Firebase!");
}

void loop() {
  
  unsigned long currentMicros = micros();
  if (currentMicros - previousMicros >= halfPeriod) {
    previousMicros = currentMicros;
    clockState = !clockState;
    
    digitalWrite(pinCK, clockState);
    digitalWrite(pinCK_INV, !clockState);
  }

  
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalFirebase) {
    previousMillis = currentMillis;

    int valoreADC = analogRead(pinSensore);

    float tensionePin = (valoreADC * 3.3) / 4095.0;
    Serial.print("ADC = ");
    Serial.println(valoreADC);
    
    float tensionePompa = tensionePin * 7.666;

    Serial.print("Tensione misurata: ");
    Serial.print(tensionePompa);
    Serial.println(" V");


    if (Firebase.setFloat(firebaseData, "/dickson/voltage", tensionePompa)) {      
    } else {
      Serial.print("Errore invio Firebase: ");
      Serial.println(firebaseData.errorReason());
    }
    if (Firebase.getInt(firebaseData, "/dickson/halfPeriod")) {
      long nuovoHalfPeriod = firebaseData.intData();
      
      if (nuovoHalfPeriod >= 100 && nuovoHalfPeriod <= 5000) {
        if (halfPeriod != nuovoHalfPeriod) {
          halfPeriod = nuovoHalfPeriod;
          Serial.print("Nuovo Semi-Periodo impostato da Web App: ");
          Serial.println(halfPeriod);
        }
      }
    } else {
      Serial.print("Errore lettura frequenza: ");
      Serial.println(firebaseData.errorReason());
    }
  }
}