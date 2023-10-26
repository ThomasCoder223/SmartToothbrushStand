extern volatile unsigned long timer0_millis;

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>

bool morning = false;
bool evening = false;

float sensitivity = 50; //Edit the sensitivity here -----------------------------------------------------------
float eveningWait = 12; //Enter (evening time - morning time) here --------------------------------------------
Servo servo;

void setup()
{
  servo.attach(2);
  servo.write(0);
  Serial.begin(9600);
}

void loop()
{
  Serial.println(analogRead(A3));
  if(millis() >= 86400000)
  {
    morning = false;
    evening = false;
    servo.write(0);
    noInterrupts ();
    timer0_millis = 0;
    interrupts ();
  }

  if(millis()>= eveningWait * 3600000)
  {
    if(morning == false)
    {
      servo.write(180);
    }
    if(analogRead(A3) >= sensitivity)
    {
      servo.write(0);
      morning = true;
      Serial.println("light");
    }

  }

  if(millis()<= eveningWait * 3600000)
  {
    if(evening == false)
    {
      servo.write(180);
    }
    if(analogRead(A3) >= sensitivity)
    {
      servo.write(0);
      evening = true;
      Serial.println("light");
    }
  }
}
