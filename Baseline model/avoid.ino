#include <NewPing.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200

#define MOTOR_PIN1  2  // Motor control pin 1
#define MOTOR_PIN2  3  // Motor control pin 2
#define MOTOR_SPEED 100 // Motor speed

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned long startTime = 0;
unsigned int turnCount = 0;

void setup() {
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  
  Serial.begin(9600);
}

void moveForward() {
  digitalWrite(MOTOR_PIN1, HIGH);
  digitalWrite(MOTOR_PIN2, LOW);
}

void stopMoving() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, LOW);
}

void turnLeft() {
  digitalWrite(MOTOR_PIN1, LOW);
  digitalWrite(MOTOR_PIN2, HIGH);
}

void detectObstacles() {
  unsigned int distance = sonar.ping_cm();
  
  if (distance > 0 && distance <= 20) {
    // Obstacle detected, turn left
    turnLeft();
    delay(500); // Delay for turn (adjust as needed)
    
    // Count the number of turns
    turnCount++;
  } else {
    // No obstacle, move forward
    moveForward();
  }
  
  // Display distance information
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void checkStoppingCondition() {
  // Check stopping condition (e.g., after 5 seconds or 10 turns)
  if (millis() - startTime >= 5000 || turnCount >= 10) {
    stopMoving();
    
    // Display the stopping condition
    Serial.print("Stopping condition met: ");
    if (millis() - startTime >= 5000) {
      Serial.println("Reached 5 seconds");
    } else {
      Serial.print("Made ");
      Serial.print(turnCount);
      Serial.println(" turns");
    }
    
    while (1) {} // Stop further execution
  }
}

void loop() {
  detectObstacles();
  checkStoppingCondition();
  
  delay(50); // Delay between measurements
}
