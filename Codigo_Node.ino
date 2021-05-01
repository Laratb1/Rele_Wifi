#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h> 
 
char auth[] = "AUTENTICACAO DO APP BLYNK"; 

char ssid[] = "NOME DA REDE WIFI";
char pass[] = "SENHA DO WIFI"; 
 
const int GPIO_2 = 2;
 
void setup(){
  pinMode(GPIO_2, OUTPUT); 
  digitalWrite(GPIO_2, HIGH); 
  Blynk.begin(auth, ssid, pass); 
}
 
void loop(){
  Blynk.run(); 
}
