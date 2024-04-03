// Definimos el pin al que está conectado el sensor
#define SENSOR_PIN 2

void setup() {
  // Iniciamos la comunicación serial
  Serial.begin(9600);

  // Configuramos el pin del sensor como entrada
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  // Leemos el valor del sensor
  int sensorValue = digitalRead(SENSOR_PIN);

  // Si el sensor detecta un objeto, el valor será HIGH
  if (sensorValue == LOW) {
    Serial.println("Objeto detectado!");
  }

  // Esperamos un poco antes de la próxima lectura
  delay(200);
}
