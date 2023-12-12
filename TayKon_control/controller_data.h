#ifndef CONTROLLER_DATA_H
#define CONTROLLER_DATA_H

class ControllerData {
public:
  // Constructor
  ControllerData(int channel2Pin, int channel3Pin, int channel4Pin, int channel5Pin, int channel6Pin);

  void update_values();
  void print_raw_values_table();
  void print_processed_values_table();

  // Getters
  bool get_status_on_off(){ return status_on_off; }
  int get_control_mode(){ return control_mode; }
  int get_Rmotor_power(){ return Rmotor_power; }
  int get_Lmotor_power(){ return Lmotor_power; }
  int get_twist(){ return twist; }

  enum Status : bool{
    OFF = false,
    ON = true
  };

private:

  // Pins
  int CH2_pin;
  int CH3_pin;
  int CH4_pin;
  int CH5_pin;
  int CH6_pin;


  // Raw data
  int channel2Value;
  int channel3Value;
  int channel4Value;
  int channel5Value;
  bool channel6Value;

  // Processed data
  bool status_on_off; // off = false, on = true
  int control_mode;   // 0 = simple control(only straight), 1 = twist control 2 = not defined
  int Rmotor_power;
  int Lmotor_power;
  int twist;          // -100/100(left/right)

  // Private functions
  int read_channel(int channelInput, int minLimit, int maxLimit, int defaultValue);
  bool read_switch(int channelInput, bool defaultValue);
  void procces_movement_data();

  // Consts
  const int CH2_MIN_RANGE = -100;
  const int CH2_MAX_RANGE = 100;
  const int CH2_DEF_VALUE = 0;

  const int CH3_MIN_RANGE = 0;
  const int CH3_MAX_RANGE = 100;
  const int CH3_DEF_VALUE = 0;

  const int CH4_MIN_RANGE = -100;
  const int CH4_MAX_RANGE = 100;
  const int CH4_DEF_VALUE = 0;

  const int CH5_MIN_RANGE = 0;
  const int CH5_MAX_RANGE = 3;
  const int CH5_DEF_VALUE = 0;

  const bool CH6_DEF_VALUE = false;

  const int CHANNEL_MIN_IN_VAL = 1000;
  const int CHANNEL_MAX_IN_VAL = 2000;
  const int PULSE_TIMEOUT = 30000;
  const int MIN_CHANNEL_VALUE = 100;

  const int MIN_MOTOR_POWER = 0;
  const int MAX_MOTOR_POWER = 180;

};

#endif