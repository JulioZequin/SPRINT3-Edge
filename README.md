<h1>Projeto IoT - Simulação de Corrida e Consumo de Bateria com Arduino e Node-RED</h1>

<h2>Integrantes</h2>
<ul>
    <li>Isadora de Morais Meneghetti (RM: 556326)</li>
    <li>Júlio César Ruiz Zequin (RM: 554676)</li>
    <li>Khadija do Rocio Vieira de Lima (RM: 558971)</li>
    <li>Mateus dos Santos da Silva (RM: 558436)</li>
    <li>Vinícius dos Santos Wince (RM: 557033)</li>
</ul>

<h2>Descrição do Projeto</h2>
<p>
    Este projeto consiste em uma simulação de um sistema de controle de velocidade e consumo de energia para um carro elétrico, utilizando um potenciômetro para ajustar a velocidade e medir o consumo de corrente elétrica (A) e o nível de bateria restante. Além disso, o sistema também mede a temperatura dos pneus, que varia conforme a aceleração (velocidade) do veículo.
</p>

<h2>Arquitetura Proposta</h2>
<p>
    O sistema proposto é uma solução IoT (Internet of Things) que integra componentes físicos com um back-end para processamento e um front-end para visualização dos dados. A arquitetura é descrita da seguinte forma:
</p>
    
<h3>Draft da Arquitetura IoT:</h3>
<ul>
    <li><strong>IoT Devices:</strong>
        <ul>
            <li>Arduino UNO ou compatível</li>
            <li>Potenciômetro (para ajuste de velocidade)</li>
            <li>Sensor DHT11 (para medição da temperatura dos pneus)</li>
        </ul>
    </li>
    <li><strong>Back-End:</strong> 
        <ul>
            <li>Node-RED para captura e processamento dos dados enviados via porta serial pelo Arduino.</li>
            <li>Interpretação dos dados JSON para análise de velocidade, consumo de corrente e temperatura.</li>
        </ul>
    </li>
    <li><strong>Front-End:</strong>
        <ul>
            <li>Dashboard em Node-RED exibindo gráficos e indicadores (gauge) para visualização em tempo real de:
                <ul>
                    <li>Velocidade do veículo(km/h)</li>
                    <li>Consumo de corrente (A)</li>
                    <li>Nível da bateria (%)</li>
                    <li>Temperatura dos pneus (°C)</li>
                </ul>
            </li>
        </ul>
    </li>
</ul>

<h3>Fluxo de Dados:</h3>
<ol>
    <li>O potenciômetro simula a aceleração do carro, ajustando a velocidade.</li>
    <li>O sensor DHT11 mede a temperatura dos pneus, que aumenta conforme a aceleração.</li>
    <li>Os dados de velocidade, temperatura, corrente consumida e nível de bateria são enviados do Arduino para o Node-RED via comunicação serial em formato JSON.</li>
    <li>No Node-RED, esses dados são processados e exibidos em gráficos e indicadores, permitindo a análise em tempo real do desempenho do "carro elétrico".</li>
</ol>

<h2>Recursos Necessários</h2>
<h3>Hardware</h3>
<ul>
    <li>Arduino UNO ou compatível</li>
    <li>Potenciômetro</li>
    <li>Sensor DHT11 para medição de temperatura</li>
    <li>Circuitos e cabos de conexão</li>
</ul>

<h3>Software</h3>
<ul>
    <li><strong>SimulIDE:</strong> Para simulação dos componentes Arduino e comunicação com o Node-RED.</li>
    <li><strong>Node-RED:</strong> Para receber e processar dados do Arduino, exibindo gráficos e indicadores em tempo real.</li>
    <li><strong>Bibliotecas Arduino:</strong>
        <ul>
            <li><code>ArduinoJson.h</code> - Para formatação e envio de dados em formato JSON via serial.</li>
            <li><code>DHT.h</code> - Para leitura do sensor de temperatura DHT11.</li>
        </ul>
    </li>
</ul>

<h2>Instruções de Uso</h2>
<ol>
    <li>Monte o circuito conforme descrito, conectando o potenciômetro ao pino A0 do Arduino e o sensor DHT11 ao pino digital 7.</li>
    <li>Carregue o código fornecido no Arduino.</li>
    <li>Abra o SimulIDE para simular o Arduino e enviar dados para o Node-RED via porta serial.</li>
    <li>Configure o Node-RED para ler os dados da porta serial e exibi-los em gráficos e indicadores de velocidade, consumo de corrente, nível de bateria e temperatura dos pneus.</li>
    <li>Ajuste o potenciômetro para controlar a velocidade e veja os dados mudarem em tempo real no Node-RED.</li>
</ol>

<h2>Código Arduino</h2>
<pre>
  <code>
    
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
        temperatura = map(valorPot, 0, 1023, 25, 90); // Temperatura de 25°C a 90°C

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
  </code>
</pre>

<h2>Recursos Utilizados no Node-RED</h2>
<p>
    No Node-RED, os seguintes recursos serão usados para exibir os dados:
</p>
<ul>
    <li><strong>Indicadores (Gauge):</strong> Para mostrar a velocidade, consumo de corrente , nível da bateria e a temperatura dos pneus em tempo real.</li>
</ul>



