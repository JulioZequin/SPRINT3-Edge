
  <h1>Projeto IoT: Simulação de Acelerador com Arduino</h1>

  <h2>Integrantes</h2>
  <ul>
        <li>Isadora de Morais Meneghetti (RM: 556326)</li>
        <li>Júlio César Ruiz Zequin (RM: 554676)</li>
        <li>Khadija do Rocio Vieira de Lima (RM: 558971)</li>
        <li>Mateus dos Santos da Silva (RM: 558436)</li>
        <li>Vinícius dos Santos Wince (RM: 557033)</li>
        
          
  </ul>
  
    
  <h2>Descrição do Projeto</h2>
  <p>Este projeto simula um sistema de controle de aceleração utilizando um Arduino, um potenciômetro e um ambiente de visualização de dados no Node-RED. Os dados de velocidade, consumo de corrente e nível de bateria são enviados em formato JSON e exibidos em gráficos.</p>
    
   <h2>Arquitetura Proposta</h2>
    <p>A solução IoT é composta pelos seguintes componentes:</p>
    <ul>
        <li><strong>IoT Devices:</strong> Arduino com potenciômetro para simular o acelerador.</li>
        <li><strong>Back-end:</strong> Node-RED para processar e visualizar os dados recebidos do Arduino.</li>
        <li><strong>Front-end:</strong> Interface gráfica em Node-RED para exibir gráficos de velocidade, consumo de corrente e nível de bateria.</li>
    </ul>

   <h3>Draft da Arquitetura</h3>
    <pre>
       <code>
    +-------------------+
    |    IoT Devices    |
    |   (Arduino + Pot) |
    +-------------------+
             |
             | Serial Communication
             |
    +-------------------+
    |      Back-end     |
    |      (Node-RED)   |
    +-------------------+
             |
             | Web Interface
             |
    +-------------------+
    |     Front-end     |
    |  (Dashboards e Gráficos) |
    +-------------------+
       </code>
    </pre>

  <h2>Recursos Necessários</h2>
    <h3>Hardware</h3>
    <ul>
        <li>Arduino Uno ou compatível</li>
        <li>Potenciômetro</li>
        <li>Fonte de alimentação</li>
    </ul>

  <h3>Software</h3>
    <ul>
        <li>SimulIDE (para simulação do Arduino)</li>
        <li>Node-RED (para visualização dos dados)</li>
        <li>Biblioteca ArduinoJson (para manipulação de JSON)</li>
    </ul>

   <h2>Instruções de Uso</h2>
    <ol>
        <li>Conectar o potenciômetro ao pino A0 do Arduino.</li>
        <li>Iniciar a simulação no SimulIDE.</li>
        <li>Executar o código do Arduino (ver seção de Código abaixo).</li>
        <li>Iniciar o Node-RED e configurar os nós para receber dados da porta serial (COM).</li>
        <li>Visualizar os dados em tempo real nos gráficos do Node-RED.</li>
    </ol>

  <h2>Requisitos</h2>
    <ul>
        <li>Arduino IDE instalado para carregar o código no Arduino.</li>
        <li>SimulIDE instalado para simular o ambiente.</li>
        <li>Node-RED instalado e configurado.</li>
    </ul>

  <h2>Código Desenvolvido</h2>
    <h3>Código do Arduino</h3>
      <pre>
        <code>

#include <ArduinoJson.h>
// Definição dos pinos
const int potPin = A0; // Pino do potenciômetro (acelerador)

// Variáveis
int valorPot = 0; // Valor do potenciômetro
int velocidade = 0; // Velocidade simulada
float nivelBateria = 100.0; // Percentual de carga da bateria
float correnteMaxima = 400.0; // Corrente máxima em amperes

void setup() {
    Serial.begin(9600); // Inicia comunicação serial
}

void loop() {
    StaticJsonDocument<100> json;

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

  // Reduz a bateria (ajuste conforme necessário)
  nivelBateria -= (corrente / 500.0); // Ajuste conforme a duração de cada ciclo

  // Evita que a carga da bateria vá abaixo de 0
  if (nivelBateria < 0) {
      nivelBateria = 0;
  }

  // Formato de escrita JSON
  json["velocidade"] = velocidade;
  json["consumoCorrente"] = corrente;
  json["bateria"] = nivelBateria;

  serializeJson(json, Serial);
  Serial.println();
  }

  // Aguarda um segundo antes do próximo ciclo
  delay(1000);
}
        </code>
      </pre>
    
  <h3>Configuração do Node-RED</h3>
    <p>Utilize nós para configurar a leitura da porta serial e visualização dos dados JSON.</p>

  <h2>Dependências</h2>
    <ul>
        <li>Biblioteca ArduinoJson instalada na IDE do Arduino.</li>
        <li>Node-RED deve estar configurado com os nós adequados para ler a porta serial.</li>
    </ul>

  <h2>Informações Relevantes</h2>
  <p>Certifique-se de que as portas seriais estejam configuradas corretamente e que não haja conflitos entre os dispositivos conectados.</p>

  <h2>Conclusão</h2>
  <p>Este projeto demonstra a integração entre hardware e software para criar um sistema de simulação e visualização em tempo real, proporcionando uma experiência de aprendizado em IoT.</p>


