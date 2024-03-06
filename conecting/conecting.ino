#include <WiFi.h>

#define LED 2
#define SPEAKER 23
#define CONNECTION_TIMEOUT 10

const char* ssid = "The_one_to_rule_them_all";
const char* password = "abcde1234";

void setup(){
    pinMode(LED,OUTPUT);
    pinMode(SPEAKER, OUTPUT);

    Serial.begin(115200);
    delay(1000);

    WiFi.mode(WIFI_STA); //Optional
    WiFi.begin(ssid, password);
    Serial.println("\nConnecting");
    int timeout_counter = 0;

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(". | ");
        delay(100);
        digitalWrite(LED,HIGH);
        digitalWrite(SPEAKER, HIGH);
        delay(100);
        digitalWrite(LED,LOW);
        digitalWrite(SPEAKER, LOW);
        timeout_counter++;
        if(timeout_counter >= CONNECTION_TIMEOUT*5){
          ESP.restart();
        }
    }
    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop(){
  if(WiFi.RSSI() <= -75){
    digitalWrite(LED,HIGH);
    digitalWrite(SPEAKER, HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    digitalWrite(SPEAKER, LOW);
    delay(100);
  }
  else if(WiFi.RSSI() <= -65 && WiFi.RSSI() > -75 ){
    digitalWrite(LED,HIGH);
    digitalWrite(SPEAKER, HIGH);
    delay(500);
    digitalWrite(LED,LOW);
    digitalWrite(SPEAKER, LOW);
    delay(500);
  }
  else if(WiFi.RSSI() > -65 ){
    digitalWrite(LED,LOW);
    digitalWrite(SPEAKER, LOW);
  }
 delay(100);
}