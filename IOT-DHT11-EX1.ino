/*-------------------------------------
Faculdade de Tecnologia SENAI Mariano Ferraz
Curso Superior de Tecnologia em Automação Industrial

Disciplina: Internet das Coisas
Professor: Caio Vinícius

Código Exemplo
Objetivo: Realizar a leitura de temperatura/umidade (DHT11) e e enviar para a plataforma
      online ThingSpeak 

Estrutura do Código:

1- Inclusão de bibliotecas e variáveis
2- Conexão do nodeMCU com a internet
3- Leitura dos valores obtidos pelo sensor DHT11
4- Envio dos dados para a plataforma IoT Thingspeak

Configurações:
1) Na IDE Arduino, 
  a)ir em prefências e depois colar no campo de add board o link: 
  http://arduino.esp8266.com/stable/package_esp8266com_index.json

  b)baixar as bibliotecas DHTStable e 
 
2) Na plataforma Thingspeak

  a) Criar uma conta no site https://thingspeak.com/
    b) Adicionar um canal e configurar os gráficos
    c) Clicar em API Keys e copiar o Write API Key e o Channel ID
-----------------------------------------------------------------------------------*/
#include <ThingSpeak.h> 
#include <WiFiClient.h> 
#include <ESP8266WiFi.h>
#include <DHT.h>
  
//OLED
#include <Wire.h>
#include "SSD1306Wire.h"
SSD1306Wire display (0x3c, SDA, SCL);

#define DHT11_PIN A0 //define o pino de dados do sensor

//rede WiFi e senha
const char* ssid = "Familia Barbozano";
const char* password = "serfeliz"; 


//Configuração dos parâmetros do ThingSpeak
unsigned long channelID = 1392487;              //cada canal tem seu ID e chave de escrita 
const char * writeAPIKey = "40RD27XEZ07LVYWZ";            //cada canal tem seu ID e chave de escrita
const char * server = "api.thingspeak.com";    //comum

//Variáveis que recebem os dados do sensor
float temp, umid;
dht DHT; //objeto baseado na biblioteca do DHT 

WiFiClient client; //objeto usado para as conexões do nodeMCU como cliente

void wifiConnect(){
  
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(63, 0, "Buscando a rede");
  display.drawString(63, 15, String(ssid) + "...");
  display.display();
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED){  
    delay(100);
  }
  
  
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(63, 10, "Conectado a rede");
  display.drawString(63, 40, String(ssid));
  display.display();
  delay(1200);
  
  display.clear();
  delay(10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_10);
  display.drawString(63,10,"macAdress: ");
  display.setFont(ArialMT_Plain_10);
  display.drawString(63,36,String(WiFi.macAddress()));
  display.display();
  delay(2000);
}

void setup() {
  
  //protocolo I2C
    display.init();                     //inicia o display OLED
    display.flipScreenVertically();     //configura a orientacao
  
  wifiConnect();

  ThingSpeak.begin(client);

}

void leitura(){
  int c = DHT.read11(DHT11_PIN);
  
  if(c == DHTLIB_OK){
    temp = DHT.temperature;
    umid = DHT.humidity;
  }
}

void loop() { 
  
  leitura();
  
  ThingSpeak.setField(1,temp); 
  ThingSpeak.setField(2,umid); 
  ThingSpeak.writeFields(channelID, writeAPIKey);
  display.clear();
  delay(10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(60, 0, "Sala Prof. Caio:");
  display.drawString(60, 20, "Temp.: " + String(temp)  + "˚C");
  display.drawString(60, 40, "Umid.: " + String(umid) + "%"); //coluna, linha antes 0 e 30
  display.display();
  delay(5000);  
}
