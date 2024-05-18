#include <Servo.h>  // Include the Servo library for controlling servo motors

Servo Myservo;  // Create a Servo object called Myservo

#define trigPin 9    // Define the Trig Pin number for the ultrasonic sensor
#define echoPin 8    // Define the Echo Pin number for the ultrasonic sensor
#define MLa 3        // Define the pin number for the 1st pin of the left motor
#define MLb 5        // Define the pin number for the 2nd pin of the left motor
#define MRa 6        // Define the pin number for the 1st pin of the right motor
#define MRb 11        // Define the pin number for the 2nd pin of the right motor

long duration, distance;  // Declare variables to store duration and distance

int motorSpeed = 150;  // Set the initial motor speed to 150 (adjust as needed)

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  pinMode(MLa, OUTPUT);  // Set the pin for the 1st pin of the left motor as output
  pinMode(MLb, OUTPUT);  // Set the pin for the 2nd pin of the left motor as output
  pinMode(MRa, OUTPUT);  // Set the pin for the 1st pin of the right motor as output
  pinMode(MRb, OUTPUT);  // Set the pin for the 2nd pin of the right motor as output
  pinMode(trigPin, OUTPUT);  // Set the Trig pin as output to transmit waves
  pinMode(echoPin, INPUT);   // Set the Echo pin as input to receive reflected waves
  Myservo.attach(10);  // Attach the servo motor to pin 10
}

void loop() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate
  digitalWrite(trigPin, LOW);  // Set Trig pin low
  delayMicroseconds(2);  // Wait for 2 microseconds
  digitalWrite(trigPin, HIGH);  // Set Trig pin high to transmit waves for 10 microseconds
  delayMicroseconds(10);  // Wait for 10 microseconds
  duration = pulseIn(echoPin, HIGH);  // Measure the duration of the pulse from Echo pin
  distance = duration / 58.2;  // Convert duration to distance in centimeters
  Serial.println(distance);  // Print the distance measured
  delay(10);  // Delay for 10 milliseconds

  if (distance > 15) {  // If there's no obstacle within 15cm
    Myservo.write(90);  // Set servo motor to 90 degrees
    analogWrite(MRb, motorSpeed);  // Move forward: set right motor speed
    digitalWrite(MRa, LOW);  // Set right motor pin 1 low
    analogWrite(MLb, motorSpeed);  // Move forward: set left motor speed
    digitalWrite(MLa, LOW);  // Set left motor pin 1 low
  } else if ((distance < 10) && (distance > 0)) {  // If obstacle is detected within 10cm
    // Stop all motors
    digitalWrite(MRb, LOW);
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(100);

    // Sweep servo motor
    Myservo.write(0);
    delay(500);
    Myservo.write(180);
    delay(500);
    Myservo.write(90);
    delay(500);

    // Move backward
    digitalWrite(MRb, LOW);
    digitalWrite(MRa, HIGH);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, HIGH);
    delay(500);
    
    // Stop all motors
    digitalWrite(MRb, LOW);
    digitalWrite(MRa, LOW);
    digitalWrite(MLb, LOW);
    digitalWrite(MLa, LOW);
    delay(100);
    
    // Move left
    digitalWrite(MRb, HIGH);
    digitalWrite(MRa, LOW);
    digitalWrite(MLa, LOW);
    digitalWrite(MLb, LOW);
    delay(500);
  }
}