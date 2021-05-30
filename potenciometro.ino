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
unsigned long channelID = 1403602;                //cada canal tem seu ID e chave de escrita 
const char * writeAPIKey = "FTD3SLZGGRWHH3PW";    //cada canal tem seu ID e chave de escrita
const char * server = "api.thingspeak.com";       //comum

int LEANDRO = A0;
int RODRIGO = 0;


WiFiClient client; //objeto usado para as conexões do nodeMCU como cliente

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
  
  wifiConnect();

  ThingSpeak.begin(client);
}

void leitura(){
  
  //Leitura Análogica
  RODRIGO = analogRead(LEANDRO);
  Serial.print("Leitura Analógica:");
  Serial.println(RODRIGO);

}

void loop(){
  
  leitura();

  ThingSpeak.setField(1,LEANDRO); 
  ThingSpeak.setField(2,RODRIGO); 
  ThingSpeak.writeFields(channelID, writeAPIKey);
  delay(10);
  
  Serial.println("VALOR: " + String(LEANDRO)  + "VOLTS");
  Serial.println("Leitura do Potenciometro: " + String(RODRIGO));
  Serial.println("......");
  delay(5000); 
}
