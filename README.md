**Smart Parking System using Ultrasonic Sensors**
This project presents a Smart Automated Parking System designed using Arduino Uno and simulated on Tinkercad/Wokwi. It detects the availability of parking spots using ultrasonic sensors, displays the status on an LCD screen, controls a servo motor gate, and uses a buzzer for alerts.

**Problem Statement**
Traditional parking systems are inefficient and time-consuming. Drivers often waste time looking for parking spots, leading to congestion. This project addresses the need for an innovative, automated system that can detect parking availability in real-time and control gate access accordingly.

** Objectives**
Automatically detect parking availability.

Visually indicate spot status using LEDs.

Display real-time parking status on a 16x2 LCD.

Control a servo motor gate for car entry.

Alert when parking is full using a buzzer.

**Components Used**
Arduino Uno

Ultrasonic Sensors × 4

Red LEDs × 3

Green LEDs × 3

Servo Motor × 1

Buzzer × 1

16x2 LCD Display with I2C Module


 **System Workflow**
Ultrasonic sensors measure the distance to detect if a parking spot is occupied.

Red/Green LEDs indicate whether each spot is occupied or available.

Gate Sensor checks for car presence at the entrance.

If spots are available, the servo motor opens the gate.

If full, and a car is detected, the buzzer beeps and the gate remains closed.

A 16x2 LCD shows the status of P1, P2, and P3 (OC/AV) and the overall space status (S: AVAIL/FULL).

**3d of our project**
click the link to view the 3d on Tinkercad
https://www.tinkercad.com/things/gTVLTXPVkVn-microp-project-work/edit?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=zp6yW-1iNs82SX-mvh7fa3QRHPzkHazjYNuayRDny78

**How to Run**
Click on the link to the simulation on Tinkercad
https://www.tinkercad.com/things/7KfTJpvJWCn-microprocessor-project-workgroup-3/editel?returnTo=https%3A%2F%2Fwww.tinkercad.com%2Fdashboard&sharecode=2-_Wi7KoNrW3TUWTM2wMqjLaOZicg9HVJh4RxxHhxGg


**Files Included**
smart_parking_system.ino – Source code

Smart_Parking_System_Presentation.pptx – Final project slides

Block_Diagram.png – System architecture

Flowchart.mmd – System logic in Mermaid format

3D_Design.png – Circuit layout and 3D view from simulation

README.md – Project documentation


**Future Improvements**
Add mobile app integration for remote monitoring.

Use RFID/NFC for automated vehicle identification.

Implement a database or cloud integration for logging.

Power the system using solar panels for sustainability.




