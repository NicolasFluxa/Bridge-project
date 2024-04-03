#define SENSOR_PIN A0 // Pin del sensor de nivel de agua
#define NIVEL_AGUA 500 // Nivel de agua para activar la bomba

void setup() {
  pinMode(SENSOR_PIN, INPUT);
}

void loop() {
  int nivel = analogRead(SENSOR_PIN); // Leemos el nivel de agua
  Serial.println(nivel == NIVEL_AGUA);
}
