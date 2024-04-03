const int Trigger = 2; // Pin digital 2 para el Trigger del sensor
const int Echo = 3;   // Pin digital 3 para el Echo del sensor

void setup() {
  Serial.begin(9600); // Inicializamos la comunicación serial
  pinMode(Trigger, OUTPUT); // Configuramos el pin como salida
  pinMode(Echo, INPUT);    // Configuramos el pin como entrada
  digitalWrite(Trigger, LOW); // Inicializamos el pin con 0
}

void loop() {
  digitalWrite(Trigger, HIGH); // Enviamos un pulso de 10us al Trigger del sensor
  delayMicroseconds(10);       // Esperamos 10 microsegundos
  digitalWrite(Trigger, LOW);

  unsigned long t = pulseIn(Echo, HIGH); // Medimos el tiempo del pulso de respuesta

  // Calculamos la distancia en centímetros
  float velocidadSonido = 340.0; // Velocidad del sonido en m/s
  float distancia = (t / 2.0) * (velocidadSonido / 10000.0); // Distancia en cm

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(1000); // Esperamos 1 segundo antes de la siguiente medición
}
