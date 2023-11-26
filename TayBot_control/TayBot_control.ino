/*
  Arduino brushless motor control with rc controller
    by TayROS for URJC 
*/
 
#include <Servo.h>
#include <Thread.h>
#include <StaticThreadController.h>
#include <ThreadController.h>
#include "controller_data.h"

// Define Input Connections
#define CH2 20
#define CH3 19
#define CH4 18
#define CH5 2
#define CH6 3
#define MOTOR_PIN 9

// ESC values
Servo ESC;
int esc_val;

// Controller
ControllerData TayBot_controller(CH2, CH3, CH4, CH5, CH6);


void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // ESC control
  ESC.attach(9,1000,2000);
}
 

void loop() {

  TayBot_controller.update_values();
  TayBot_controller.print_raw_values_table();
  TayBot_controller.print_processed_values_table();

  delay(500);
}

