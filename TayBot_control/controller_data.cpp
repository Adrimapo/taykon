#include "Arduino.h"
#include "controller_data.h"

ControllerData::ControllerData(int channel2Pin, int channel3Pin, int channel4Pin, int channel5Pin, int channel6Pin) {

  // Set up serial monitor
  Serial.begin(115200);

  // Set all pins as inputs
  CH2_pin = channel2Pin;
  CH3_pin = channel3Pin;
  CH4_pin = channel4Pin;
  CH5_pin = channel5Pin;
  CH6_pin = channel6Pin;

  pinMode(CH2_pin, INPUT);
  pinMode(CH3_pin, INPUT);
  pinMode(CH4_pin, INPUT);
  pinMode(CH5_pin, INPUT);
  pinMode(CH6_pin, INPUT);

  // Data init
  status_on_off = OFF;
  control_mode = 0;
  Rmotor_power = 0;
  Lmotor_power = 0;
  twist = 0;

  update_values();
}

int ControllerData::read_channel(int channelInput, int minLimit, int maxLimit, int defaultValue) {
  int ch = pulseIn(channelInput, HIGH, PULSE_TIMEOUT);
  if (ch < MIN_CHANNEL_VALUE) return defaultValue;
  return map(ch, CHANNEL_MIN_IN_VAL, CHANNEL_MAX_IN_VAL, minLimit, maxLimit);
}

bool ControllerData::read_switch(int channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = read_channel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}


void ControllerData::update_values(){

  // Raw Data
  channel2Value = read_channel(CH2_pin, CH2_MIN_RANGE, CH2_MAX_RANGE, CH2_DEF_VALUE);
  channel3Value = read_channel(CH3_pin, CH3_MIN_RANGE, CH3_MAX_RANGE, CH3_DEF_VALUE);
  channel4Value = read_channel(CH4_pin, CH4_MIN_RANGE, CH4_MAX_RANGE, CH4_DEF_VALUE);
  channel5Value = read_channel(CH5_pin, CH5_MIN_RANGE, CH5_MAX_RANGE, CH5_DEF_VALUE);
  channel6Value = read_switch(CH6_pin, CH6_DEF_VALUE);

  // Proccesed data
  status_on_off = channel6Value;
  control_mode = channel5Value;

  procces_movement_data();
}

int clampInt(int valor, int minimo, int maximo) {
    return max(minimo, min(valor, maximo));
}

void ControllerData::procces_movement_data(){

  if(status_on_off == OFF){
    Rmotor_power = 0;
    Lmotor_power = 0;
    twist = 0;
  }
  else{
    switch(control_mode) {
      case 0:
          Rmotor_power = map(channel3Value, 0, 100, MIN_MOTOR_POWER, MAX_MOTOR_POWER);
          Lmotor_power = map(channel3Value, 0, 100, MIN_MOTOR_POWER, MAX_MOTOR_POWER);
          twist = 0;
          break;

      case 1:
          int recived_power = channel3Value;
          int recived_twist = channel2Value ;
          
          int L_vel = recived_power - recived_twist;
          int R_vel = recived_power + recived_twist;

          // Limit between 0 and 100 and map value to motor speed
          L_vel = clampInt(L_vel, CH3_MIN_RANGE, CH3_MAX_RANGE);
          R_vel = clampInt(R_vel, CH3_MIN_RANGE, CH3_MAX_RANGE);

          Lmotor_power = map(L_vel, CH3_MIN_RANGE, CH3_MAX_RANGE, MIN_MOTOR_POWER, MAX_MOTOR_POWER);
          Rmotor_power = map(R_vel, CH3_MIN_RANGE, CH3_MAX_RANGE, MIN_MOTOR_POWER, MAX_MOTOR_POWER);
          twist = channel2Value;
          break;

      case 2:
          Rmotor_power = map(channel3Value, 0, 100, MIN_MOTOR_POWER, MAX_MOTOR_POWER);
          Lmotor_power = map(channel2Value, 0, 100, MIN_MOTOR_POWER, MAX_MOTOR_POWER);
          twist = 0;
          break;
    }
  }
}

void ControllerData::print_raw_values_table() {
  Serial.println("=======================================");
  Serial.println("\nActual Raw Values:");
  Serial.print("| CH2: ");
  Serial.print(channel2Value);
  Serial.print(" | CH3: ");
  Serial.print(channel3Value);
  Serial.print(" | CH4: ");
  Serial.print(channel4Value);
  Serial.print(" | CH5: ");
  Serial.print(channel5Value);
  Serial.print(" | CH6: ");
  Serial.println(channel6Value);
  Serial.println("=======================================");
}

void ControllerData::print_processed_values_table() {
  Serial.println("=======================================");
  Serial.println("\nActual Processed Values:");
  if(status_on_off == OFF){
    Serial.print("| Status: OFF");
  }
  else{
    Serial.print("| Status: ON");
  }

  switch(control_mode) {
      case 0:
          Serial.print(" | Control Mode: Simple");
          break;
      case 1:
          Serial.print(" | Control Mode: Twist Control");
          break;
      case 2:
          Serial.print(" | Control Mode: Testing mode");
          break;
  }
  Serial.print(" | R Motor Power: ");
  Serial.print(Rmotor_power);
  Serial.print(" | L Motor Power: ");
  Serial.print(Lmotor_power);
  Serial.print(" | Twist: ");
  Serial.println(twist);
  Serial.println("=======================================");
}





















