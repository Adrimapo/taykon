/*
  Arduino brushless motor control with rc controller
    by TayROS for URJC 
*/
 
#include <Servo.h>
#include <Thread.h>
#include <StaticThreadController.h>
#include <ThreadController.h>

// Define Input Connections
#define CH1 21
#define CH2 20
#define CH3 19
#define CH4 18
#define CH5 2
#define CH6 3
#define MOTOR_PIN 9

// Consts
const int CH1_MIN_RANGE = -100;
const int CH1_MAX_RANGE = 100;
const int CH1_DEF_VALUE = 0;

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


// Channels values
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 
int ch5Value;
bool ch6Value;

// ESC values
Servo ESC;
int esc_val;

// Threading
ThreadController rc_channels_controller = ThreadController();
ThreadController escs_controller = ThreadController();

Thread ChannelsThread = Thread();
Thread EscThread = Thread();


int read_channel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 30000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}
 
bool read_switch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = read_channel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
}

void print_channels_values(){
  Serial.print("Ch1: ");
  Serial.print(ch1Value);
  Serial.print(" | Ch2: ");
  Serial.print(ch2Value);
  Serial.print(" | Ch3: ");
  Serial.print(ch3Value);
  Serial.print(" | Ch4: ");
  Serial.print(ch4Value);
  Serial.print(" | Ch5: ");
  Serial.print(ch5Value);
  Serial.print(" | Ch6: ");
  Serial.println(ch6Value);
}

void read_all_channels(){
  ch1Value = read_channel(CH1, CH1_MIN_RANGE, CH1_MAX_RANGE, CH1_DEF_VALUE);
  ch2Value = read_channel(CH2, CH2_MIN_RANGE, CH2_MAX_RANGE, CH2_DEF_VALUE);
  ch3Value = read_channel(CH3, CH3_MIN_RANGE, CH3_MAX_RANGE, CH3_DEF_VALUE);
  ch4Value = read_channel(CH4, CH4_MIN_RANGE, CH4_MAX_RANGE, CH4_DEF_VALUE);
  ch5Value = read_channel(CH5, CH5_MIN_RANGE, CH5_MAX_RANGE, CH5_DEF_VALUE);
  ch6Value = read_switch(CH6, CH6_DEF_VALUE);
}

void channel_callback(){

  read_all_channels();
  print_channels_values();
}

void esc_callback(){

  esc_val = map(ch3Value, CH3_MIN_RANGE, CH3_MAX_RANGE, 0, 180); 

  Serial.print("Motor speed: ");
  Serial.println(esc_val);

  ESC.write(esc_val);
}


void setup(){
  // Set up serial monitor
  Serial.begin(115200);
  
  // Set all pins as inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  // ESC control
  ESC.attach(9,1000,2000);

  // Threading
  ChannelsThread.enabled = true;
  ChannelsThread.setInterval(10);
  ChannelsThread.onRun(channel_callback);
  rc_channels_controller.add(&ChannelsThread);

  EscThread.enabled = true;
  EscThread.setInterval(10);
  EscThread.onRun(esc_callback);
  escs_controller.add(&EscThread);
}
 

void loop() {

  rc_channels_controller.run();
  escs_controller.run();
}



