# Proyecto de Puente Levadizo Automatizado con Arduino

## Descripción General
Este proyecto utiliza un microcontrolador Arduino para controlar un puente levadizo automatizado. El sistema es capaz de detectar la altura de los barcos que se acercan y ajustar la altura del puente en consecuencia. Además, puede detectar el peso en el puente y permitir o denegar el paso en función de este. Importante destacar que el sistema es energizado por una batería Power Bank Oarmio de 23000 mAh que se carga mediante un cargador de panel solar portátil CL-638WP de 6V, lo que lo hace sostenible y autónomo.

## Componentes

### Servos

- **SG90**: Estos servos controlan las barreras de tráfico. Cuando un barco se acerca, las barreras se bajan para detener el tráfico.
- **S3003 modificados para rotación continua**: Estos servos controlan el movimiento del puente, permitiéndole levantarse y bajarse.

### Sensores

- **Sensores infrarrojos OKY3127**: Estos sensores detectan la altura de los barcos que se acercan al puente. Dependiendo de cuántos sensores se activan, el puente se levanta a diferentes alturas para permitir que el barco pase.
- **Sensor de fuerza resistiva (FSR)**: Este sensor detecta el peso en el puente. Si el peso detectado supera un límite máximo, el sistema no levantará el puente y encenderá una luz roja para indicar que el paso no está permitido. Si el peso es adecuado, el sistema encenderá una luz verde y procederá a levantar el puente.
- **Sensores ultrasónicos HC-SR04**: Estos sensores detectan cuándo un barco comienza y termina de pasar por el puente.

### Energía

- **Batería Power Bank Oarmio 23000 mAh**: Proporciona la energía necesaria para el funcionamiento del sistema. Esta batería tiene una gran capacidad y cuenta con 3 puertos USB para conectar varios dispositivos, así como una linterna incorporada para emergencias.
- **Cargador Panel Solar Portátil CL-638WP 6V**: Se encarga de cargar la batería, permitiendo que el sistema sea autónomo y sostenible. Este cargador es portátil y puede generar energía incluso en condiciones de poca luz.


## Funcionamiento


### Detección de barcos
Cuando un barco se acerca al puente, los sensores infrarrojos OKY3127 detectan su altura. Estos sensores están ubicados a diferentes alturas en el puente, y dependiendo de cuántos sensores se activan, el sistema puede determinar la altura del barco.

### Levantamiento del puente
Una vez que se ha detectado la altura del barco, el sistema utiliza servos S3003 modificados para rotación continua para levantar el puente. La altura a la que se levanta el puente depende de la altura del barco detectada por los sensores infrarrojos.

### Control de las barreras de tráfico
Al mismo tiempo que el puente se levanta, el sistema utiliza servos SG90 para bajar las barreras de tráfico. Esto evita que los vehículos crucen el puente mientras está levantado.

### Detección del peso en el puente
Antes de que el barco pase por debajo del puente, el sistema utiliza un sensor de fuerza resistiva (FSR) para detectar el peso en el puente. Si el peso detectado supera un límite máximo, el sistema no levantará el puente y encenderá una luz roja para indicar que el paso no está permitido. Si el peso es adecuado, el sistema encenderá una luz verde y procederá a levantar el puente.

### Monitoreo del tránsito de los barcos
El sistema utiliza sensores ultrasónicos HC-SR04 para detectar cuándo un barco comienza y termina de pasar por el puente. Estos sensores pueden determinar la distancia entre ellos y el barco utilizando ondas ultrasónicas.
### Bajada del puente y levantamiento de las barreras

Una vez que el barco ha pasado, el sistema baja el puente utilizando los servos S3003. Luego, levanta las barreras de tráfico utilizando los servos SG90, permitiendo que los vehículos continúen su camino.


## Futuras Mejoras

### Interfaz de usuario
Podrían desarrollar una interfaz de usuario gráfica (GUI) para monitorear y controlar el sistema en tiempo real. Esto podría incluir la visualización de la altura del puente, el estado de las barreras de tráfico, y las lecturas de los sensores.

### Conectividad IoT
Podrían añadir funcionalidades de Internet de las Cosas (IoT) para permitir el control y monitoreo remoto del puente.

### Sistema de alertas
Podrían implementar un sistema de alertas que notifique a los usuarios cuando un barco se acerca o cuando el puente está levantado. Esto podría hacerse a través de correo electrónico, SMS, o notificaciones push en una aplicación móvil.

### Mejoras en la detección de barcos
Podrían explorar el uso de diferentes tipos de sensores para mejorar la detección de barcos. Por ejemplo, podrían usar sensores de radar o lidar para obtener una detección más precisa.

### Simulación y modelado
Podrían utilizar software de simulación y modelado para predecir el comportamiento del puente bajo diferentes condiciones y optimizar su rendimiento.


## Contribuciones

Las contribuciones a este proyecto son bienvenidas. Si tienes alguna idea para mejorar el sistema o si encuentras algún problema, no dudes en abrir un issue o enviar un pull request.

## Licencia

Este proyecto está licenciado bajo los términos de la licencia MIT.
