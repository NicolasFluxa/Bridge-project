# Arduino Automated Drawbridge Project

## General Description
This project uses an Arduino microcontroller to control an automated drawbridge. The system is able to detect the height of approaching boats and adjust the height of the bridge accordingly. In addition, it can detect the weight on the bridge and allow or deny passage accordingly. Importantly, the system is powered by a 23000 mAh Oarmio Power Bank battery that is charged by a CL-638WP 6V portable solar panel charger, making it sustainable and autonomous.

## Components

### Servos

- **SG90**: These servos control the traffic barriers. When a ship approaches, the barriers are lowered to stop traffic.
- **S3003 modificados para rotación continua**: These servos control the movement of the bridge, allowing it to be raised and lowered.

### Sensors

- **OKY3127 infrared sensors**: These sensors detect the height of ships approaching the bridge. Depending on how many sensors are activated, the bridge is raised to different heights to allow the ship to pass.
- **Resistive force sensor (FSR)**: This sensor detects the weight on the bridge. If the detected weight exceeds a maximum limit, the system will not raise the bridge and will illuminate a red light to indicate that passage is not permitted. If the weight is adequate, the system will turn on a green light and proceed to lift the bridge.
- **HC-SR04 Ultrasonic Sensors**: These sensors detect when a vessel begins and ends its passage over the bridge.

### Power

- **Oarmio Power Bank 23000 mAh**: Provides the power required to operate the system. This battery has a large capacity and features 3 USB ports for connecting various devices, as well as a built-in torch for emergencies.
- **Portable Solar Panel Charger CL-638WP 6V**: Charges the battery, allowing the system to be autonomous and sustainable. This charger is portable and can generate power even in low light conditions.


## Operation


### Ship detection
When a ship approaches the bridge, the OKY3127 infrared sensors detect its height. These sensors are located at different heights on the bridge, and depending on how many sensors are activated, the system can determine the height of the ship.

### Raising the bridge
Once the height of the ship has been detected, the system uses S3003 servos modified for continuous rotation to lift the bridge. The height to which the bridge is raised depends on the height of the ship detected by the infrared sensors.

### Traffic barrier control
At the same time as the bridge is raised, the system uses SG90 servos to lower the traffic barriers. This prevents vehicles from crossing the bridge while it is raised.

### Weight detection on the bridge
Before the ship passes under the bridge, the system uses a resistive force sensor (FSR) to detect the weight on the bridge. If the detected weight exceeds a maximum limit, the system will not lift the bridge and will illuminate a red light to indicate that passage is not permitted. If the weight is adequate, the system will turn on a green light and proceed to lift the bridge.

### Vessel Traffic Monitoring
The system uses HC-SR04 ultrasonic sensors to detect when a vessel begins and ends its passage over the bridge. These sensors can determine the distance between them and the ship using ultrasonic waves.

### Lowering the bridge and raising the barriers
Once the ship has passed, the system lowers the bridge using the S3003 servos. It then raises the traffic barriers using the SG90 servos, allowing the vehicles to continue on their way.


## Future Enhancements

### User interface
A graphical user interface (GUI) could be developed to monitor and control the system in real time. This could include displaying bridge height, traffic barrier status, and sensor readings.

### IoT connectivity
Internet of Things (IoT) functionalities could be added to enable remote control and monitoring of the bridge.

### Alerting system
They could implement an alert system that notifies users when a ship is approaching or when the bridge is raised. This could be done via email, SMS, or push notifications on a mobile app.

### Improvements in ship detection
They could explore the use of different types of sensors to improve ship detection. For example, they could use radar or lidar sensors for more accurate detection.

### Simulation and modelling
They could use simulation and modelling software to predict the behaviour of the bridge under different conditions and optimise its performance.

## Contributions

Contributions to this project are welcome. If you have any ideas to improve the system or if you encounter any problems, feel free to open an issue or send a pull request.

## Licensing

This project is licensed under the terms of the MIT license.
