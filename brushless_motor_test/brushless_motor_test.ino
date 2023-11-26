/*
  Arduino Brushless Motor Control Testing
    by TayROS for URJC 
*/

#include <Servo.h>

// Consts
const int POT_PIN = A0;

// Global vars
Servo ESC;
int pot_val;
int esc_val;

void setup() {
  Serial.begin(115200);
  ESC.attach(9,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
}

void loop() {
  // Reads te potenciometer value and map it to valid values
  pot_val = analogRead(A0);
  esc_val = map(pot_val, 0, 1023, 0, 180); 

  Serial.print("Motor speed: ");
  Serial.println(esc_val);

  ESC.write(esc_val);
  delay(100);
}