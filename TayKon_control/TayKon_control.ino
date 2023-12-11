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
#define R_MOTOR_PIN 9
#define L_MOTOR_PIN 10

const bool DEBUG = false;

// ESC values
Servo R_ESC;
Servo L_ESC;
int esc_val;

// Controller
ControllerData TayKon_controller(CH2, CH3, CH4, CH5, CH6);


void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // ESC control
  R_ESC.attach(R_MOTOR_PIN,1000,2000);
  L_ESC.attach(L_MOTOR_PIN,1000,2000);
}
 

void loop() {

  //-- Update the controller values
  TayKon_controller.update_values();

  //-- Debug info
  if(DEBUG){
    TayKon_controller.print_raw_values_table();
    TayKon_controller.print_processed_values_table();
  }

  //-- Write controller data into ESCs
  R_ESC.write(TayKon_controller.get_Rmotor_power());
  L_ESC.write(TayKon_controller.get_Lmotor_power());

  if(DEBUG){
    delay(500);
  }
}

