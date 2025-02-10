#include <Servo.h>

// Create servo objects for the left and right ears
Servo leftEar;
Servo rightEar;

// Define the pins for the servos
const int leftEarPin = 9;
const int rightEarPin = 10;

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);
  
  // Attach the servos to their respective pins
  leftEar.attach(leftEarPin);
  rightEar.attach(rightEarPin);

  // Set both ears to neutral (upright) position
  leftEar.write(90);
  rightEar.write(90);
  delay(2000);  // Give time for the servos to settle
}

void loop() {
  // Check if data is available on the serial port
  if (Serial.available() > 0) {
    // Read the incoming string until newline and trim whitespace
    String emotion = Serial.readStringUntil('\n');
    emotion.trim();
    
    // Debug: Print the received emotion to the Serial Monitor
    Serial.print("Received emotion: ");
    Serial.println(emotion);
    
    // Process the received emotion command
    if (emotion.equalsIgnoreCase("happy")) {
      // Happy expression: Quick movement so that the ears face forward in opposite directions.
      leftEar.write(45);    // Left ear quickly moves to 45° (facing forward/tilted)
      rightEar.write(135);  // Right ear quickly moves to 135° (facing forward/tilted opposite)
      delay(1000);          // Hold for 1 second
      
      // Return both ears to neutral position
      leftEar.write(90);
      rightEar.write(90);
      delay(1000);
    }
    else if (emotion.equalsIgnoreCase("sad")) {
      // Sad expression: Slowly move the ears in opposite directions.
      // Left ear moves gradually from neutral (90°) to fully backward (180°)
      for (int pos = 90; pos <= 180; pos++) {
        leftEar.write(pos);
        delay(20); // Adjust delay for slower movement
      }
      // Right ear moves gradually from neutral (90°) to fully forward (0°)
      for (int pos = 90; pos >= 0; pos--) {
        rightEar.write(pos);
        delay(20);
      }
      delay(3000); // Hold the "sad" position for 3 seconds
      
      // Return both ears to neutral position
      leftEar.write(90);
      rightEar.write(90);
      delay(1000);
    }
    else {
      // If an unrecognized command is received, default both ears to neutral
      leftEar.write(90);
      rightEar.write(90);
      delay(1000);
    }
  }
}

