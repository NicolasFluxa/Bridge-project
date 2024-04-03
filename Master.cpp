#include <Wire.h>
#include <Servo.h>
#include <Stepper.h>

const int SLAVE_ADDRESS = 4;  // Dirección del esclavo
const int NUM_SENSORS = 6;  // Número de sensores
int data[NUM_SENSORS];
// altura
// fsrValue
// distancia1
// distancia2
// medidor 1
// medidor 2

// Número de pasos por revolución para este motor
const int stepsPerRevolution = 2048;

// Inicializa la biblioteca Stepper en los pines 1 a 4:
Stepper myStepperLeft(stepsPerRevolution, 1, 3, 2, 4);
// Inicializa la biblioteca Stepper en los pines 5 a 8:
Stepper myStepperRight(stepsPerRevolution, 5, 7, 6, 8);


// Definicion de peso promedio del puente para FSR
const float MAX_WEIGHT = 1.0; // Se debe configurar !!!!!!!
const float MIN_WEIGHT = 1.3; // Se debe configurar !!!!!!!



// Nivel de agua para activar la bomba
#define NIVEL_AGUA 500.0 // Se debe configurar!!!!!!


// Creamos los objetos servo para las barreras
Servo servo1, servo2;
// Tiempo corresponde a valor de incio para servos
int tiempo = 0;


// Definimos los pines a los que están conectadas las luces
#define RED_LIGHT_PIN_SHIP A0
#define GREEN_LIGHT_PIN_SHIP A1
#define RED_LIGHT_PIN_BRIDGE A2
#define WHITE_LIGHT_PIN_BRIDGE A3
#define BLINK_INTERVAL 500 // tiempo en milisegundos
unsigned long previousMillis = 0;


// Definimos los pines a los que está conectado el Rele
#define RELE 4

void setup() {

  Wire.begin();  // Inicia el bus I2C como maestro
  Serial.begin(115200); // Iniciamos la comunicación serial

  // Establece la velocidad motores paso a paso a 15 rpm :
  myStepperLeft.setSpeed(15);
  myStepperRight.setSpeed(15);

  // Conectamos los servos SG90 a los pines correspondientes
  servo1.attach(9);
  servo2.attach(10);

  // Configuramos los pines de las luces para el barco como salida
  pinMode(RED_LIGHT_PIN_SHIP, OUTPUT);
  pinMode(GREEN_LIGHT_PIN_SHIP, OUTPUT);
  // Configuramos los pines de las luces para el puente como salida
  pinMode(RED_LIGHT_PIN_BRIDGE, OUTPUT);
  pinMode(WHITE_LIGHT_PIN_BRIDGE, OUTPUT);

  // Configuramos rele como salida
  pinMode(RELE, OUTPUT);

}

void loop() {

  Wire.requestFrom(SLAVE_ADDRESS, NUM_SENSORS * sizeof(int));  // Solicita los datos de los sensores al esclavo
  // Leo los datos y los voy ingresando uno a uno a la lista
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (Wire.available()) {  // Si hay datos disponibles
      Wire.readBytes((char*)&data[i], sizeof(int));  // Lee los datos
    }
  }

  if (data[0] != 0){ // altura != 0

    unsigned long currentMillis = millis(); // alerta durante 20 segundo con luces blanca y roja
    if (currentMillis - previousMillis >= BLINK_INTERVAL) {
      previousMillis = currentMillis;
      if (digitalRead(RED_LIGHT_PIN_BRIDGE) == HIGH) {
        digitalWrite(RED_LIGHT_PIN_BRIDGE, LOW);
        digitalWrite(WHITE_LIGHT_PIN_BRIDGE, HIGH);
      }
      else {
        digitalWrite(RED_LIGHT_PIN_BRIDGE, HIGH);
        digitalWrite(WHITE_LIGHT_PIN_BRIDGE, LOW);
      }
    }
    if (currentMillis >= 20000) { // detener después de 20 segundos
      digitalWrite(RED_LIGHT_PIN_BRIDGE, LOW);
      digitalWrite(WHITE_LIGHT_PIN_BRIDGE, LOW);
    }


    for(tiempo = 90; tiempo >= 0; tiempo--){
          servo1.write(tiempo); // Mueve los servos SG90 a la posición 90 grados (barreras arriba)
          servo2.write(tiempo);
          delay(100);
    }


    if (MIN_WEIGHT > data[1] > MAX_WEIGHT) {
      // Si el peso es adecuado, encendemos la luz verde y procedemos a levantar el puente
      digitalWrite(RED_LIGHT_PIN_SHIP, LOW);
      digitalWrite(GREEN_LIGHT_PIN_SHIP, HIGH);

      // Mueve los motores paso a paso a la posición correspondiente (puente arriba)
      myStepperLeft.step(-stepsPerRevolution * data[0]);
      myStepperRight.step(stepsPerRevolution * data[0]);

      if (data[2] >= 24 && data[3] >= 24){
        // Mueve los motores paso a paso a la posición correspondiente (puente abajo)
        myStepperLeft.step(stepsPerRevolution * data[0]);
        myStepperRight.step(-stepsPerRevolution * data[0]);


        for(tiempo = 0; tiempo >= 90; tiempo++){
          // Mueve los servos SG90 a la posición 0 grados (barreras arriba)
          servo1.write(tiempo);
          servo2.write(tiempo);
          delay(100);
        }
      }
    }
  }
  else {
      // Si el peso es demasiado alto, encendemos la luz roja y no levantamos el puente
      digitalWrite(RED_LIGHT_PIN_SHIP, HIGH);
      digitalWrite(GREEN_LIGHT_PIN_SHIP, LOW);
    }

  if (NIVEL_AGUA > data[4] || NIVEL_AGUA > data[5]){
    // Enviamos la instruccion al rele para inciar con el drenado de agua
    digitalWrite(RELE, 0);
  }
}

