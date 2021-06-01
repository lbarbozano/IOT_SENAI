/*--------------------------------------------------------------------------------------------------
Faculdade de Tecnologia SENAI Mariano Ferraz
Curso Superior de Tecnologia em Automação Industrial

Disciplina: Internet das Coisas
Professor: Caio Vinícius
Alunos Leandro Barbozano dos Santos
       Rodrigo de Souza

Entregas:
Individual ou em dupla;
Proibido usar o sensor DHT11 ou DHT22;
Gráficos com pelo menos duas grandezas físicas, em tempo real;
Um gráfico gerado a partir do MATLAB Visualizations;
Um análise gerada a partir do MATLAB Analysis;
Na entrega da atividade, disponibilizar print dos gráficos e link da visualização pública com tag criada
Entregar os códigos em Matlab e NodeMCU
-----------------------------------------------------------------------------------------------------------*/

#include <ThingSpeak.h> 
#include <WiFiClient.h> 
#include <ESP8266WiFi.h>

//rede WiFi e senha
const char* ssid = "Familia Barbozano";
const char* password = "serfeliz";

//Configuração dos parâmetros do ThingSpeak
unsigned long channelID = 1403081;              //cada canal tem seu ID e chave de escrita 
const char * writeAPIKey = "0HUJ2GL5QPHZ10EA";           //cada canal tem seu ID e chave de escrita
const char * server = "api.thingspeak.com";    //comum

int Leandro = A0;
int Rodrigo = 0;
const int trigger = D5;
const int echo = D7;
long IOT;
float distanceCM;

WiFiClient client; //objeto usado para as conexões do nodeMCU como cliente

void wifiConnect(){

  Serial.println("Buscando a rede");
  Serial.println(String(ssid) + "...");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED){
    Serial.println("...");  
    delay(1000);
  }
  
  Serial.println("Conectado a rede");
  Serial.println(String(ssid));
  delay(1000);

  Serial.println("macAdress: ");
  Serial.println(String(WiFi.macAddress()));
  delay(1000);
}

void setup() { 
  Serial.begin(9600); // Inicio da comunicação serial
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  wifiConnect();

  ThingSpeak.begin(client);
}

void leitura(){
  
  //Leitura Análogica
  Rodrigo = analogRead(Leandro);
  Serial.print("Leitura Analógica:");
  Serial.println(Rodrigo);

  //Leitura sensor ultrassonico
  digitalWrite(trigger, LOW);
  delay(1);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigger, LOW);
  IOT = pulseIn(echo, HIGH);
  distanceCM = IOT * 0.034;
  distanceCM = distanceCM / 2;
}

void loop() {
  
  leitura();

  ThingSpeak.setField(1,distanceCM); 
  ThingSpeak.setField(2,Rodrigo); 
  ThingSpeak.writeFields(channelID, writeAPIKey);
  delay(1000);
  
  Serial.println("Distância: " + String(distanceCM)  + "cm");
  Serial.println("Leitura analogica: " + String(Rodrigo));
  Serial.println("......");
  delay(1000); 
}
