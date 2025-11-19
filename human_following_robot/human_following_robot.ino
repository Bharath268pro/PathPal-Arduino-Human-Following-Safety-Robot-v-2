#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>

// IR Sensors
#define RIGHT A3
#define LEFT  A2

// Ultrasonic Sensor
#define TRIGGER_PIN A1
#define ECHO_PIN A0
#define MAX_DISTANCE 200

// MQ-2 Gas/Smoke Sensor
#define MQ2_SENSOR A5

// Passive Buzzer - NOT USED
#define BUZZER A4

unsigned int distance = 0;
unsigned int Right_Value = 0;
unsigned int Left_Value = 0;
int MQ2_Value = 0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor Motor1(1, MOTOR12_1KHZ);
AF_DCMotor Motor2(2, MOTOR12_1KHZ);
AF_DCMotor Motor3(3, MOTOR34_1KHZ);
AF_DCMotor Motor4(4, MOTOR34_1KHZ);

Servo myservo;
int pos = 0;

void setup() {
  Serial.begin(9600);
  
  myservo.attach(10);
  
  // Servo initialization sweep
  for (pos = 90; pos <= 180; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 0; pos <= 90; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(MQ2_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
  
  // NO TONE AT ALL - just countdown
  Serial.println("🔥 MQ-2 Sensor warming up...");
  Serial.println("Please wait 20 seconds for accurate readings");
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  
  for (int i = 20; i > 0; i--) {
    Serial.print(i);
    Serial.println(" seconds...");
    delay(1000);
  }
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(100);

  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);  
  Serial.println("✅ MQ-2 Ready! Robot Active.");
}

void stopAllMotors() {
  Motor1.setSpeed(0);
  Motor1.run(RELEASE);
  Motor2.setSpeed(0);
  Motor2.run(RELEASE);
  Motor3.setSpeed(0);
  Motor3.run(RELEASE);
  Motor4.setSpeed(0);
  Motor4.run(RELEASE);
}

void moveForward() {
  Motor1.setSpeed(130);
  Motor1.run(FORWARD);
  Motor2.setSpeed(130);
  Motor2.run(FORWARD);
  Motor3.setSpeed(130);
  Motor3.run(FORWARD);
  Motor4.setSpeed(130);
  Motor4.run(FORWARD);
}

void turnRight() {
  Motor1.setSpeed(150);
  Motor1.run(BACKWARD);
  Motor2.setSpeed(150);
  Motor2.run(BACKWARD);
  Motor3.setSpeed(150);
  Motor3.run(FORWARD);
  Motor4.setSpeed(150);
  Motor4.run(FORWARD);
  delay(150);
}

void turnLeft() {
  Motor1.setSpeed(150);
  Motor1.run(FORWARD);
  Motor2.setSpeed(150);
  Motor2.run(FORWARD);
  Motor3.setSpeed(150);
  Motor3.run(BACKWARD);
  Motor4.setSpeed(150);
  Motor4.run(BACKWARD);
  delay(150);
}

void loop() { 
  delay(100);
  
  // Read all sensors
  distance = sonar.ping_cm();
  Right_Value = digitalRead(RIGHT);
  Left_Value = digitalRead(LEFT);
  MQ2_Value = analogRead(MQ2_SENSOR);
  
  // Display sensor readings
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | RIGHT: ");
  Serial.print(Right_Value);
  Serial.print(" | LEFT: ");
  Serial.print(Left_Value);
  Serial.print(" | MQ2: ");
  Serial.print(MQ2_Value);
  
  // 🚨 Gas and Smoke detection - NO ALARMS, just stop
  if (MQ2_Value >= 100) {
    Serial.println("  <-- 🚨 SMOKE DETECTED!");
    stopAllMotors();
    digitalWrite(BUZZER, HIGH);  // Just turn on buzzer, no tone()
    return;
  } 
  else if (MQ2_Value >= 70) {
    Serial.println("  <-- ⚠ GAS DETECTED!");
    stopAllMotors();
    digitalWrite(BUZZER, HIGH);  // Just turn on buzzer, no tone()
    return;
  } 
  else {
    Serial.println(" (Normal)");
    digitalWrite(BUZZER, LOW);
  }
  
  // 🚘 Human-following operation
  if ((distance > 1) && (distance < 15)) {
    Serial.println("🚗 Following target");
    moveForward();
  } 
  else if ((Right_Value == 0) && (Left_Value == 1)) {
    Serial.println("↪ Turning Right");
    turnRight();
  } 
  else if ((Right_Value == 1) && (Left_Value == 0)) {
    Serial.println("↩ Turning Left");
    turnLeft();
  } 
  else if (distance > 15) {
    Serial.println("🛑 Target lost - Stopped");
    stopAllMotors();
  }
}
