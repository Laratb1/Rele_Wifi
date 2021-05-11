# Rele_Wifi

UNIVERSIDADE FEDERAL DO ESPÍRITO SANTO – CAMPUS GOIABEIRAS
CURSO ENGENHARIA DE COMPUTAÇÃO

Projeto Integrado de Computação  I

Criado por JOSÉ VITOR ZORZAL, LARA TAGARRO, MILLA PEREIRA


## OBJETIVO

Tendo em vista esse cenário recente e claramente promissor de automatização residencial, nosso grupo decidiu realizar como projeto um dispositivo que possa auxiliar nessa automatização e ser controlado via Wifi, se baseando no conceito de Internet das Coisas. Sendo assim, temos como objetivo o desenvolvimento de um módulo relé, que com o auxílio de uma placa nodeMCU possa ser controlado via Wifi atráves de um aplicativo Mobile desenvolvido na plataforma App Inventor. Com isso, para demonstrar o funcionamento do módulo relé, Wifi vamos apresentá-lo controlando uma lâmpada, ligando-a e desligando-a através do aplicativo Mobile.


## MATERIAIS

Para a realização desse projeto, serão necessários os seguintes componentes:
* 1 nodeMCU
* 1 módulo relé 1 canal 5V
* Jumpers macho-macho

## ESQUEMÁTICO

![WhatsApp Image 2021-05-10 at 10 40 15](https://user-images.githubusercontent.com/74369384/117688086-d7dd2980-b18e-11eb-8501-8ae6145b9e46.jpeg)
![WhatsApp Image 2021-05-10 at 10 40 10](https://user-images.githubusercontent.com/74369384/117688221-f4796180-b18e-11eb-9bee-18cf42813d3b.jpeg)

## IMPLEMENTAÇÃO
### CÓDIGO

'''
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
'''

### APLICATIVO
