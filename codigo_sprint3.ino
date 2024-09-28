#include <ArduinoJson.h>
#include <DHT.h>

// Definição dos pinos
const int potPin = A0; // Pino do potenciômetro (acelerador)
#define DHTPIN 7 // Pino do DHT 
#define DHTTYPE DHT11 // Tipo do sensor DHT11 

DHT dht(DHTPIN, DHTTYPE);

// Variáveis
int valorPot = 0; // Valor do potenciômetro
int velocidade = 0; // Velocidade simulada
float nivelBateria = 100.0; // Percentual de carga da bateria
float correnteMaxima = 400.0; // Corrente máxima em amperes
float temperatura = 0.0; // Temperatura simulada

void setup() {
  Serial.begin(9600); // Inicia comunicação serial
  dht.begin(); // Inicia o sensor DHT
}

void loop() {
  StaticJsonDocument<200> json;

  // Lê o valor do potenciômetro (0 a 1023)
  valorPot = analogRead(potPin);

  // Verifica se a leitura está correta
  if (valorPot < 0 || valorPot > 1023) {
    Serial.println("Erro na leitura do potenciômetro!");
  } else {
    // Calcula a velocidade com base no valor do potenciômetro
    velocidade = map(valorPot, 0, 1023, 0, 320); // Simula velocidade de 0 a 320 km/h

    // Simula o consumo de corrente diretamente
    float corrente = (velocidade / 320.0) * correnteMaxima;

    // Ajuste mais agressivo para a redução do nível da bateria
    nivelBateria -= (corrente / 500.0); // Reduzindo mais rápido com base na corrente

    // Evita que a carga da bateria vá abaixo de 0
    if (nivelBateria < 0) {
      nivelBateria = 0;
    }

    // Simulação da temperatura (0 a 90°C) baseada no valor do potenciômetro
    temperatura = map(valorPot, 0, 1023, 25, 90); // Temperatura de 25 °C a 90°C

    // Formato de escrita JSON
    json["velocidade"] = velocidade;
    json["consumoCorrente"] = corrente;
    json["bateria"] = nivelBateria;
    json["temperatura"] = temperatura;

    serializeJson(json, Serial);
    Serial.println();
  }

  // Aguarda um segundo antes do próximo ciclo
  delay(1000);
}
