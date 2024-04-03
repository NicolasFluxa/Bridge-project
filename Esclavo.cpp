#include <Wire.h>

// Pin del sensor de nivel de agua
#define SENSORAGUA1_PIN A0
#define SENSORAGUA2_PIN A1
// Nivel de agua para activar la bomba
#define NIVEL_AGUA 500.0 // Se debe configurar!!!!!!


#define NUM_PARES_SENSORES 3
#define NUM_ALTURAS 3
// Define los pines de los sensores
const int pinesSensores[NUM_PARES_SENSORES][2] = {{5, 8}, {6, 9}, {7, 10}};
// Define las alturas correspondientes a cada nivel
const int listaAltura[NUM_ALTURAS] = {30, 60, 90};
int altura = 0;// Inicializa la altura a 0



// Definimos el pin al que está conectado el sensor FSR
#define FSR_PIN A4


// Definimos los pines a los que están conectados los sensores Ultrasonid
#define TRIGGER1_PIN 0
#define TRIGGER2_PIN 2
#define ECHO1_PIN 1
#define ECHO2_PIN 3
// Velocidad del sonido en m/s
const float VELOCIDADSONIDO = 340.0;
int distancia1;
int distancia2;


void setup() {
  Wire.begin(4);  // Inicia el bus I2C como esclavo en la dirección 4
  Wire.onRequest(requestEvent);  // Registra la función que se llamará cuando el maestro solicite datos


  // Configuramos los pínes de los sensores de agua "Entrada"
  pinMode(SENSORAGUA1_PIN, INPUT);
  pinMode(SENSORAGUA2_PIN, INPUT);


  // Configura los pines de los sensores como entradas
  for (int i = 0; i < NUM_PARES_SENSORES; i++) {
    pinMode(pinesSensores[i][0], INPUT);
    pinMode(pinesSensores[i][1], INPUT);
  }


  // Configuramos los pínes de los sensores ultrasonido Entrada Echo, Salida Trigger
  pinMode(TRIGGER1_PIN, OUTPUT);
  pinMode(TRIGGER2_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);
  pinMode(ECHO2_PIN, INPUT);


}

void loop() {
  // Lee los sensores y determina la altura
  for (int i = 0; i < NUM_PARES_SENSORES; i++) {
    if (digitalRead(pinesSensores[i][0]) == LOW || digitalRead(pinesSensores[i][1]) == LOW) {
      altura = listaAltura[i];
    }
  }


  // Enviamos un Pulso de 10us a ambos TRIGGER
  digitalWrite(TRIGGER1_PIN, HIGH);
  digitalWrite(TRIGGER2_PIN, HIGH);
  delayMicroseconds(10); // Esperamos 10 microsegundos
  digitalWrite(TRIGGER1_PIN, LOW);
  digitalWrite(TRIGGER2_PIN, LOW);

  // Medimos el tiempo del pulso de respuesta
  unsigned long t1 = pulseIn(ECHO1_PIN, HIGH);
  unsigned long t2 = pulseIn(ECHO2_PIN, HIGH);
  // Calculamos la distancia en centímetros

  distancia1 = (t1 / 2.0) * (VELOCIDADSONIDO / 10000.0); // Distancia en cm
  distancia2 = (t2 / 2.0) * (VELOCIDADSONIDO / 10000.0); // Distancia en cm


}

void requestEvent() {
  int alturaEnviada = altura;
  int distancia1Enviada = distancia1;
  int distancia2Enviada = distancia2;
  int fsrValue = analogRead(FSR_PIN);
  // Medimos el nivel de agua, en caso de ser mayor al maximo aceptado activamos bombas
  int medidor1, medidor2 = analogRead(SENSORAGUA1_PIN), analogRead(SENSORAGUA2_PIN);


  Wire.write((char*)&alturaEnviada, sizeof(int));
  Wire.write((char*)&fsrValue, sizeof(int));
  Wire.write((char*)&distancia1Enviada, sizeof(int));
  Wire.write((char*)&distancia2Enviada, sizeof(int));
  Wire.write((char*)&medidor1, sizeof(int));
  Wire.write((char*)&medidor2, sizeof(int));

}
