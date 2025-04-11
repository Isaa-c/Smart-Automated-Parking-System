#include <Servo.h>
#include <Adafruit_LiquidCrystal.h>

// Define LCD with I2C
Adafruit_LiquidCrystal lcd(0);

// Define distance threshold for detection
const int distanceThreshold = 30;

// Pack 1 Sensor and LEDs
const int trig1 = 5, echo1 = 4;
const int redLED1 = 11, greenLED1 = 10;

// Pack 2 Sensor and LEDs
const int trig2 = 3, echo2 = 2;
const int redLED2 = A2, greenLED2 = A3;

// Pack 3 Sensor and LEDs
const int trig3 = 9, echo3 = 8;
const int redLED3 = A1, greenLED3 = A0;

// Gate Sensor, Servo, and Buzzer
const int trigGate = 7, echoGate = 6;
const int buzzer = 13;
Servo gateServo;

// Gate State
bool gateOpen = false;
bool buzzerBeeped = false;

void setup() {
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();

  // Initialize Pins
  pinMode(trig1, OUTPUT); 
  pinMode(echo1, INPUT);
  pinMode(redLED1, OUTPUT); 
  pinMode(greenLED1, OUTPUT);

  pinMode(trig2, OUTPUT); 
  pinMode(echo2, INPUT);
  pinMode(redLED2, OUTPUT);
  pinMode(greenLED2, OUTPUT);

  pinMode(trig3, OUTPUT); 
  pinMode(echo3, INPUT);
  pinMode(redLED3, OUTPUT); 
  pinMode(greenLED3, OUTPUT);

  pinMode(trigGate, OUTPUT); 
  pinMode(echoGate, INPUT);
  pinMode(buzzer, OUTPUT);
  gateServo.attach(12);
  gateServo.write(0);  // Ensure gate is closed
  
  lcd.print("Parking System");
  delay(2000);
  lcd.clear();
}

// Function to get distance
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return (duration * 0.034 / 2);
}

// Function to beep buzzer for a specified duration
void beepBuzzer(int duration) {
  digitalWrite(buzzer, HIGH);
  delay(duration);
  digitalWrite(buzzer, LOW);
}

// Function to check if all spots are full
bool allSpotsFull() {
  return (getDistance(trig1, echo1) <= distanceThreshold &&
          getDistance(trig2, echo2) <= distanceThreshold &&
          getDistance(trig3, echo3) <= distanceThreshold);
}

// Function to control gate
void gateControl(bool open) {
  if (open && !gateOpen) {  // Open the gate
    gateServo.write(90);
    gateOpen = true;
    Serial.println("Gate Open");
  } 
  else if (!open && gateOpen) {  // Close the gate
    gateServo.write(0);
    gateOpen = false;
    Serial.println("Gate Closed");
  }
}

// Function to update LCD status
void updateLCD() {
  lcd.clear();

  // Check each parking spot status
  String p1 = getDistance(trig1, echo1) <= distanceThreshold ? "OC" : "AV";
  String p2 = getDistance(trig2, echo2) <= distanceThreshold ? "OC" : "AV";
  String p3 = getDistance(trig3, echo3) <= distanceThreshold ? "OC" : "AV";
  
  // Check overall status
  String status = allSpotsFull() ? "FULL" : "AVAIL";
  
  // Display on LCD
  lcd.setCursor(0, 0);
  lcd.print("P1:");
  lcd.print(p1);
  lcd.print(" P2:");
  lcd.print(p2);
  
  lcd.setCursor(0, 1);
  lcd.print("P3:");
  lcd.print(p3);
  lcd.print(" S:");
  lcd.print(status);
}

// Function to check parking spots and control LEDs
void checkParkingSpots() {
  // Check Pack 1
  if (getDistance(trig1, echo1) <= distanceThreshold) {
    digitalWrite(redLED1, HIGH);
    digitalWrite(greenLED1, LOW);
  } else {
    digitalWrite(redLED1, LOW);
    digitalWrite(greenLED1, HIGH);
  }

  // Check Pack 2
  if (getDistance(trig2, echo2) <= distanceThreshold) {
    digitalWrite(redLED2, HIGH);
    digitalWrite(greenLED2, LOW);
  } else {
    digitalWrite(redLED2, LOW);
    digitalWrite(greenLED2, HIGH);
  }

  // Check Pack 3
  if (getDistance(trig3, echo3) <= distanceThreshold) {
    digitalWrite(redLED3, HIGH);
    digitalWrite(greenLED3, LOW);
  } else {
    digitalWrite(redLED3, LOW);
    digitalWrite(greenLED3, HIGH);
  }
}

// Main loop function
void loop() {
  checkParkingSpots();  // Check parking distances
  updateLCD();          // Update LCD with parking status

  long gateDistance = getDistance(trigGate, echoGate);
  Serial.print("Gate Distance: ");
  Serial.print(gateDistance);
  Serial.println(" cm");

  // If a car is detected at the gate
  if (gateDistance <= distanceThreshold) {
    if (!allSpotsFull()) {  // If there is space
      gateControl(true);    // Open the gate
      buzzerBeeped = false; // Reset buzzer flag
    } else {  // If parking is full
      Serial.println("Parking Full! Gate remains closed.");
      
      // Beep for 5 seconds only once
      if (!buzzerBeeped) {  
        beepBuzzer(5000);
        buzzerBeeped = true;
      }
      gateServo.write(0);
    }
  } 
  // If no car is detected, close gate after 4 seconds
  else if (gateOpen) {
    Serial.println("No car detected. Closing gate in 4 seconds...");
    delay(4000);
    gateControl(false);
    buzzerBeeped = false;
  }
  
  delay(1000);
} 