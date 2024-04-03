#include <Servo.h>

// Creamos los objetos servo para las barreras
Servo servo1, servo2;
// Creamos los objetos servo para el puente
Servo s3003_1, s3003_2, s3003_3, s3003_4;
// Tiempo corresponde a valor de incio para servos
int tiempo = 0;


// Definimos los pines a los que están conectados los sensores Ultrasonid
#define TRIGGER1_PIN 0
#define TRIGGER2_PIN 2
#define ECHO1_PIN 1
#define ECHO2_PIN 3
// Velocidad del sonido en m/s
float VELOCIDADSONIDO = 340.0;


// Pin del sensor de nivel de agua
#define SENSORAGUA1_PIN A0
#define SENSORAGUA2_PIN A1
// Nivel de agua para activar la bomba
float NIVEL_AGUA = 500.0; // Se debe configurar!!!!!!
// Definimos los pines a los que está conectado el Rele
#define RELE 4


#define NUM_SENSORS 6
#define NUM_ALTURAS 3
// Define los pines de los sensores
const int pinesSensores[NUM_SENSORS] = {5, 6, 7, 8, 9, 10};
// Define las alturas correspondientes a cada nivel
const int listaAltura[NUM_ALTURAS] = {30, 60, 90};


// Definimos los pines a los que están conectadas las luces
#define RED_LIGHT_PIN_SHIP A2
#define GREEN_LIGHT_PIN_SHIP A3


// Definimos el pin al que está conectado el sensor FSR
#define FSR_PIN A4
// Definicion de peso promedio del puente para FSR
#define MAX_WEIGHT 1.0 // Se debe configurar !!!!!!!
#define MIN_WEIGHT 1.3 // Se debe configurar !!!!!!!


void setup() {
  // Iniciamos la comunicación serial
  Serial.begin(115200);

  // Configuramos los pínes de los sensores de agua "Entrada"
  pinMode(SENSORAGUA1_PIN, INPUT);
  pinMode(SENSORAGUA2_PIN, INPUT);


  // Conectamos los servos SG90 a los pines correspondientes
  servo1.attach(11);
  servo2.attach(12);
  // Conectamos los servos S3003 a los pines correspondientes
  s3003_1.attach(13);
  s3003_2.attach(14);


  // Configura los pines de los sensores como entradas
  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(pinesSensores[i], INPUT);
  }


  // Configuramos los pínes de los sensores ultrasonido Entrada Echo, Salida Trigger
  pinMode(TRIGGER1_PIN, OUTPUT);
  pinMode(TRIGGER2_PIN, OUTPUT);
  pinMode(ECHO1_PIN, INPUT);
  pinMode(ECHO2_PIN, INPUT);


  // Configuramos los pines de las luces para el barco como salida
  pinMode(RED_LIGHT_PIN_SHIP, OUTPUT);
  pinMode(GREEN_LIGHT_PIN_SHIP, OUTPUT);


  // Configuramos rele como salida
  pinMode(RELE, OUTPUT);

}

void loop() {  
  int altura = 0;

  // Lee los sensores y determina la altura
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (digitalRead(pinesSensores[i]) == LOW) {
      altura = listaAltura[i % NUM_ALTURAS];
    }
  }
  Serial.println(altura);
  delay(500);
  if (altura != 0){
    for(tiempo = 90; tiempo >= 0; tiempo--){          
          servo1.write(tiempo); // Mueve los servos SG90 a la posición 90 grados (barreras arriba)
          servo2.write(tiempo);
          delay(100);
        }


    // Leemos el valor del sensor FSR
    int fsrValue = analogRead(FSR_PIN);
    Serial.println(fsrValue);


    // Comprobamos si el peso detectado por el sensor FSR es mayor que el peso máximo permitido
    if (MIN_WEIGHT > fsrValue > MAX_WEIGHT) {
      // Si el peso es adecuado, encendemos la luz verde y procedemos a levantar el puente
      digitalWrite(RED_LIGHT_PIN_SHIP, LOW);
      digitalWrite(GREEN_LIGHT_PIN_SHIP, HIGH);

      // Mueve los servos S3003 a la posición correspondiente (puente arriba)
      for(int i  = 0;  i <= altura; i++){ // Se debe Configurar!!!!
          s3003_1.write(90 + i);  // Ajusta la velocidad y la dirección de la rotación
          s3003_2.write(90 + i);
          delay(100);
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
      float distancia1 = (t1 / 2.0) * (VELOCIDADSONIDO / 10000.0); // Distancia en cm
      float distancia2 = (t2 / 2.0) * (VELOCIDADSONIDO / 10000.0); // Distancia en cm

      if (distancia1 >= 24.0 && distancia2 >= 24.0){ // Se debe Configurar!!!!
        for(tiempo = 0; tiempo >= 90; tiempo++){
          // Mueve los servos SG90 a la posición 0 grados (barreras arriba)
          servo1.write(tiempo);
          servo2.write(tiempo);
          delay(100);
        }

        for(int i = altura; i >= 0; i--){
          s3003_1.write(90 + i);  // Buscar la opcion que segun el !!!!
          s3003_2.write(90 + i);  // valor de altua baje el puente !!!!
          delay(100);
        }
      }
    }
    else {
      // Si el peso es demasiado alto, encendemos la luz roja y no levantamos el puente
      digitalWrite(RED_LIGHT_PIN_SHIP, HIGH);
      digitalWrite(GREEN_LIGHT_PIN_SHIP, LOW);
    }
  }

  // Medimos el nivel de agua, en caso de ser mayor al maximo aceptado activamos bombas
  float medidor1, medidor2 = analogRead(SENSORAGUA1_PIN), analogRead(SENSORAGUA2_PIN);
  if (NIVEL_AGUA < medidor1 || NIVEL_AGUA < medidor2){
    // Enviamos la instruccion al rele para inciar con el drenado de agua
    digitalWrite(RELE, 0);
  }
}
