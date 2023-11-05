#include <Servo.h>
Servo servo;


/*
 * 
 * 
 * 
 */
float sensitivity = 100;     //Enter the sensitivity here (~20-150)
/*
 * 
 * 
 * 
 */

const unsigned long halfDay = 5000;   
const unsigned long fullDay = 10000;

unsigned long previousTime1 = 0;
unsigned long previousTime2 = 0;

bool dayOrNight = 1;
bool halfDone = false;


void setup() {
  Serial.begin(9600);
  Serial.println("Startup");
  servo.attach(2);
  servo.write(180);
  delay(100);
  servo.write(0);
  delay(100);
  servo.write(180);
  delay(100);
  servo.write(0);
}

void loop() {
  
  unsigned long currentTime = millis();

  if(analogRead(A3) >= sensitivity)
  {
    Serial.println("BRUSHED !!!");
    servo.write(0);
  }
  
  if(currentTime - previousTime1 >= halfDay && halfDone == false)
  {
    
      Serial.println("Entered night time");
      halfDone = true;
      servo.write(180);

      dayOrNight = 0;
      previousTime1 = currentTime;  
  }

  
  if(currentTime - previousTime2 >= fullDay)
  {
      Serial.println("Entered day time");
      servo.write(180);
      
      dayOrNight = 1;
      halfDone = false;
      
      previousTime2 = currentTime;  
      previousTime1 = currentTime;  
  }
  
  
  
}
