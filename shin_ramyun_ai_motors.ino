#include <AccelStepper.h>
#define HALFSTEP 4

// Motor pin definitions
#define motorPin1  2     // IN1 on the ULN2003 driver 1
#define motorPin2  3     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  5     // IN4 on the ULN2003 driver 1

#define NUM_COLUMNS 7
#define NUM_DISPENSERS 2
#define MAX_SPEED 10000
#define ACCELARATION 300
#define SPEED 300

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48

AccelStepper column1(HALFSTEP, 22, 24, 23, 25);
AccelStepper column2(HALFSTEP, 26, 28, 27, 29);
AccelStepper column3(HALFSTEP, 30, 32, 31, 33);
AccelStepper column4(HALFSTEP, 34, 36, 35, 37);
AccelStepper column5(HALFSTEP, 38, 40, 39, 41);
AccelStepper column6(HALFSTEP, 42, 44, 42, 45);
AccelStepper column7(HALFSTEP, 46, 48, 47, 49);
AccelStepper dispenser1(HALFSTEP, 2, 4, 3, 5);
AccelStepper dispenser2(HALFSTEP, 8, 10, 9, 11);

AccelStepper *columns[7] = {
  &column1,
  &column2,
  &column3,
  &column4,
  &column5,
  &column6,
  &column7
};

AccelStepper *dispensers[2] = {
  &dispenser1,
  &dispenser2
};


void initSteppers() {
  for(byte col = 0; col < 7; col++){
    columns[col]->setSpeed(SPEED);
    columns[col]->setMaxSpeed(MAX_SPEED);
    columns[col]->setAcceleration(ACCELARATION);
  }
  for(byte disp = 0; disp < 7; disp++){
    dispensers[disp]->setSpeed(SPEED);
    dispensers[disp]->setMaxSpeed(MAX_SPEED);
    dispensers[disp]->setAcceleration(ACCELARATION);
  }
}

void openColumn(AccelStepper *s) {
  s->move(512);
  s->runToPosition();
  delay(3000);
  s->move(-512);
  s->runToPosition();
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Shin Ramyun AI Motors ...");
  initSteppers();
}

void loop() {
  while(!Serial.available()) {}
  char input;
  input = Serial.read();
  Serial.println(input);
  if (input >= 'a' && input <= 'g') openColumn(columns[input - 'a']);
}