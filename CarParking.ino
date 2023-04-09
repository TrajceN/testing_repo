#include <Servo.h>

//Analog pins
#define PHOTORES1  PIN_A0
#define PHOTORES2  PIN_A1
#define PHOTORES3  PIN_A2
#define PHOTORES4  PIN_A3
#define PHOTORES5  PIN_A4
#define PHOTORES6  PIN_A5

//Digital LED pins
#define RGB_LED1   PIN2
#define RGB_LED2   PIN3
#define RGB_LED3   PIN4
#define RGB_LED4   PIN5
#define RGB_LED5   PIN6
#define RGB_LED6   PIN7

//Digital IR (infra-red) sensor pins
//Note: IR_INx pins are used to open the ramp when car is getting INTO the parking garage
//Note: IR_OUTx pins are used to open the ramp when car is getting OUT of the parking garage
#define IR_IN1     8
#define IR_OUT1    9
#define IR_IN2     10
#define IR_OUT2    11

//Servo control pins
#define SERVO1_CTRL  12
#define SERVO2_CTRL  13

#define SERVO_NULLPOS 0

//Variables
Servo myservo;  // create servo object to control a servo
uint16_t servo1_pos = 0;    // variable to store the servo position
uint16_t servo2_pos = 0;    // variable to store the servo position

const int photores_pins[6] = {PHOTORES1, PHOTORES2, PHOTORES3, PHOTORES4, PHOTORES5, PHOTORES6};
const int rgb_leds[6] = {RGB_LED1, RGB_LED2, RGB_LED3, RGB_LED4, RGB_LED5, RGB_LED6};

void setup() {
  // put your setup code here, to run once:
  uint8_t i;
  for (i = 0; i < 6; i++) {
    pinMode(photores_pins[i], INPUT);
    pinMode(rgb_leds[i], OUTPUT);
  }

  pinMode(IR_IN1, INPUT);

  //Setting servo to its initial position
  ServoInit();

}

void loop() {
  // put your main code here, to run repeatedly:

  ParkingSpotSignalization();

  if (!digitalRead(IR_IN1) && servo1_pos == 0) {

    myservo.attach(SERVO1_CTRL);
    for (servo1_pos = 0; servo1_pos <= 90; servo1_pos++) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(servo1_pos);              // tell servo to go to position in variable 'servo1_pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    myservo.detach();
  }
  

  if (digitalRead(IR_IN1) && servo1_pos >= 90) {
    
    myservo.attach(SERVO1_CTRL);
    for (servo1_pos = 90; servo1_pos > 0; servo1_pos--) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(servo1_pos);              // tell servo to go to position in variable 'servo1_pos'
      delay(10);                       // waits 15 ms for the servo to reach the position
    }
    delay(150);
    myservo.detach();
  }

}

void ServoInit(void)
{
  myservo.attach(SERVO1_CTRL);
  myservo.write(SERVO_NULLPOS);              // tell servo to go to position so called 'NULL position'
  delay(700);
  myservo.detach();  
}

void ParkingSpotSignalization(void)
{
  uint16_t  photores_val[6] = {0};
  uint8_t i;  
  for (i = 0; i < 6; i++) {
    photores_val[i] = analogRead(photores_pins[i]);

    if (photores_val[i] < 35) {
      digitalWrite(rgb_leds[i], HIGH);
    }else{
      digitalWrite(rgb_leds[i], LOW);
    }
    delay(4);
  }

}

