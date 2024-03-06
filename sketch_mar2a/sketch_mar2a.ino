#include <WiFi.h>

const char* ssid = "The_one_to_rule_them_all";
const char* password = "abcde1234";

IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

void setup(){
  Serial.begin(115200);
  Serial.println();

  Serial.print("Setting soft-AP configuration :) . . .");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed :( ");
  // WiFi.softAP (ssid);
  // WiFi.softAP (ssid, passphrase, channel, ssdi_hidden, max_connection);

  Serial.print("Setting soft-AP . . . ");
  Serial.println(WiFi.softAP(ssid,password) ? "Ready" : "Failed");
}

void loop(){
Serial.print("Server Connected");
Serial.println(WiFi.softAPIP());

delay (500);

}