int relay = 2;

void setup() {
  // Configuración
  pinMode(relay, OUTPUT); // Configurar relay como salida o OUTPUT
  Serial.begin(9600); // Abrir el puerto serie a la velocidad de 9600bps para trasnmicion de datos.
}

void loop() {
  // Código principal donde ocurren en loop
  digitalWrite(relay, 0); // envia señal alta al relay
  Serial.println("Relay accionado");
  delay(1000);           // 1 segundo

  digitalWrite(relay, 1);  // envia señal baja al relay
  Serial.println("Relay no accionado");
  delay(1000);           // 1 segundo

}
