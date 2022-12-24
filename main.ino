#include <PS2X_lib.h>

const int IN_1 = 29; //motor kiri
const int IN_2 = 27; //motor kiri
const int IN_3 = 25; //motor kanan
const int IN_4 = 23; //motor kanan
const int pwmA = 9;  //pwm motor kiri
const int pwmB = 10; //pwm motor kanan
const int sensorSharp = A0;

long sensorValue, distance; //sensor sharp
int extSpeed;

#define PS2_DAT 44 //data
#define PS2_CMD 46 //command
#define PS2_SEL 48 //attention
#define PS2_CLK 50 //clock

#define pressures false
#define rumble false

PS2X controller;


int baseSpeed;
int maxSpeed = 255;
int speedX = 90;
int speedSq = 150;
int speedTr = 120;
int speedCir = 100; //default speed
int x;

void setup() {
  // put your setup code here, to run once:
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  Serial.begin(57600);
  delay(300);

  controller.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble); //configure controller gamepad
  controller.readType();
}

void loop() {
  // put your main code here, to run repeatedly:
  controller.read_gamepad(); //reading input
  
  //Mode
  if(controller.ButtonPressed(PSB_CROSS)){
    baseSpeed = speedX;
  }

  else if(controller.ButtonPressed(PSB_CIRCLE)){
    baseSpeed = speedCir; //default speed
  }

  else if(controller.ButtonPressed(PSB_SQUARE)){
    baseSpeed = speedSq;
  }

  else if(controller.ButtonPressed(PSB_TRIANGLE)){
    baseSpeed = speedTr;
  }

  Serial.println(baseSpeed);
  delay(50);

  x = 1;


  if(controller.Analog(PSS_RX) == 255){
    maju(baseSpeed);
    if(controller.Button(PSB_R1)){
      maju(maxSpeed);
    }
    
    while(controller.Analog(PSS_RX) == 255){
      drift(baseSpeed);
      x++;
      
    }
  }

  else if(controller.Analog(PSS_LY) == 255){
    mundur(baseSpeed);
    if(controller.Button(PSB_R1)){
      mundur(maxSpeed);
    }
  }

  else if(controller.Analog(PSS_RX) == 255){
    belokKanan(baseSpeed);
  }

  else if(controller.Analog(PSS_RX) == 0){
    belokKiri(baseSpeed);
  }
  
  else if(controller.Button(PSB_R3)){
    muterKanan(baseSpeed);
  }
  
  else {
    maju(0);
  }
  
  delay(50);
}
