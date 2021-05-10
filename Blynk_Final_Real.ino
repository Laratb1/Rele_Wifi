#include <ESP8266WiFi.h>
#include <DNSServer.h> 
#include <ESP8266WebServer.h> 
#include <WiFiManager.h> 

WiFiServer server(80);

int GPIO = 0;

WiFiManager wifiManager; 
 
void setup() {
  Serial.begin(115200); //Default Baud Rate for NodeMCU
  delay(10);
 
  pinMode(GPIO, OUTPUT);  // Connect Relay to NodeMCU's D4 Pin
  digitalWrite(GPIO, 0);

  wifiManager.autoConnect("Rele Wifi");

  server.begin();
  Serial.println("Server started");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else if (req.indexOf("/wifi") != -1){
    wifiManager.resetSettings();
    ESP.restart();
  }
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }
 
  // Set GPIO2 according to the request
  digitalWrite(GPIO, val);
  
  client.flush();
 
  String s;
  if (val == 0){
    s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  }
  else{
   s = "HTTP/1.1 300 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  }
  s += (val)?"high":"low";
  s += "</html>";
  client.print(s);

  // Send the response to the client
  
  delay(1);
  Serial.println("Client disonnected");
}
