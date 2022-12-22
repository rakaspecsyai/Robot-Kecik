#include <PS2X_lib.h>

const int IN_1 = 29;
const int IN_2 = 27;
const int IN_3 = 25;
const int IN_4 = 23;
const int pwmA = 9;
const int pwmB = 10; 
const int sensorSharp = A0;

long sensorValue, distance;
int extSpeed;

#define PS2_DAT 44  //14
#define PS2_CMD 46  //15
#define PS2_SEL 48  //16
#define PS2_CLK 50  //17

#define pressures false
#define rumble false

PS2X controller;

int baseSpeed = 100;
int maxSpeed = 255;
int speedX = 90;
int speedSq = 150;
int speedTr = 120;
int speedCir = 180;

void setup() {
  // put your setup code here, to run once:
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  Serial.begin(57600);
  delay(300);

  controller.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  controller.readType();
}

void loop() {
  // put your main code here, to run repeatedly:
  controller.read_gamepad();
  
  //Mode
  if(controller.ButtonPressed(PSB_CROSS)){
    baseSpeed = speedX;
  }

  else if(controller.ButtonPressed(PSB_CIRCLE)){
    baseSpeed = speedCir;
  }

  else if(controller.ButtonPressed(PSB_SQUARE)){
    baseSpeed = speedSq;
  }

  else if(controller.ButtonPressed(PSB_TRIANGLE)){
    baseSpeed = speedTr;
  }


  
  if (controller.Analog(PSS_LY) == 255 && controller.Analog(PSS_RX) == 255) {
    serongKanan(baseSpeed);

  }

  else if(controller.Analog(PSS_RX) == 255){
    maju(baseSpeed);
    if(controller.Button(PSB_R1)){
      maju(maxSpeed);
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
