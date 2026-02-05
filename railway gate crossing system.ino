#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 7
#define SERVO_PIN 6

Servo servo;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  servo.attach(SERVO_PIN);
  servo.write(0);  // Start position at 0 degrees
}

void loop() {
  long duration, distance;
  
  // Trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.034) / 2;  // Calculate distance in cm

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 0 && distance < 10) {  // Trigger distance threshold (10 cm)
    servo.write(90);  // Rotate servo to 90 degrees
    digitalWrite(BUZZER_PIN, HIGH);  // Buzzer ON
  } else {
    servo.write(0);  // Reset servo to 0 degrees
    digitalWrite(BUZZER_PIN, LOW);  // Buzzer OFF
  }

  delay(200);  // Adjust delay as needed
}
