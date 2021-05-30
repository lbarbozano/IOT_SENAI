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
unsigned long channelID = 1403602;              //cada canal tem seu ID e chave de escrita 
const char * writeAPIKey = "1403602";           //cada canal tem seu ID e chave de escrita
const char * server = "api.thingspeak.com";    //comum

int Leandro = A0;
int Rodrigo = 0;
const int trigger = 16;
const int echo = 5;
long IOT;
float distanciaCM;

WiFiClient client; //objeto usado para as conexões do nodeMCU como clie

void wifiConnect(){

  Serial.println("Buscando a rede");
  Serial.println(String(ssid) + "...");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED){
    Serial.println("...");  
    delay(100);
  }
  
  Serial.println("Conectado a rede");
  Serial.println(String(ssid));
  delay(1200);

  Serial.println("macAdress: ");
  Serial.println(String(WiFi.macAddress()));
  delay(2000);
}

void setup() { 
  Serial.begin(115200); // Inicio da comunicação serial
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
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  IOT = pulseIn(echo, HIGH);
  distanciaCM = IOT * 0.034;
  distanciaCM = distanciaCM / 2;
}

void loop() {
  
  leitura();

  ThingSpeak.setField(1,distanciaCM); 
  ThingSpeak.setField(2,Rodrigo); 
  ThingSpeak.writeFields(channelID, writeAPIKey);
  delay(10);
  
  Serial.println("Distância: " + String(distanciaCM)  + "cm");
  Serial.println("Leitura analogica: " + String(Rodrigo));
  Serial.println("......");
  delay(5000); 
}
