#include <Stepper.h>

// Número de pasos por revolución para este motor
const int stepsPerRevolution = 2048;

// Inicializa la biblioteca Stepper en los pines 8 a 11:
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Establece la velocidad a 5 rpm:
  myStepper.setSpeed(15);
}

void loop() {
  // Da una vuelta completa en sentido horario:
  myStepper.step(stepsPerRevolution*2);
  delay(1000);

  // Da una vuelta completa en sentido antihorario:
  myStepper.step(-stepsPerRevolution*2);
  delay(1000);
}
