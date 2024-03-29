
#include <Servo.h>  

#define COUNT_DELAY 1500


const int numbers[10][7] = 
{
  {1, 1, 1, 0, 1, 1, 1}, // 0
  {0, 0, 0, 0, 0, 1, 1}, // 1
  {0, 1, 1, 1, 1, 1, 0}, // 2 
  {0, 0, 1, 1, 1, 1, 1}, // 3
  {1, 0, 0, 1, 0, 1, 1}, // 4
  {1, 0, 1, 1, 1, 0, 1}, // 5
  {1, 1, 1, 1, 1, 0, 1}, // 6
  {0, 0, 1, 0, 0, 1, 1}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 0, 1, 1, 1, 1, 1} // 9
};

const int servo_pins[7] = {2, 3, 4, 5, 6, 7, 8};

const int servo_angles[7] = {90, 90, 90, -90, 90, -90, -90};

Servo servo[7];

const bool DEBUG = true;

void setup() {

  Serial.begin(9600);
  for(int i = 0; i < sizeof(servo); i++)
  {
    servo[i].attach(servo_pins[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  consoleCheck();
}


void showNumber(int n)
{
  if(DEBUG) Serial.println("Showed: " + String(n));
  for(int i = 0; i < 7; i++)
  {
    if(servo[i].read() != servo_angles[i]*numbers[n][i]) 
      servo[i].write(servo_angles[i] * numbers[n][i]);
  }
}

void consoleCheck()
{
  if(Serial.available() > 0)
  {
    String string = Serial.readString();
    if(string.startsWith("pi"))
    {
      if(DEBUG) Serial.println("Started pi");
      String pi = "141592653589793238462643383279";
      for(while Serial.available() == 0)
      {
        if(i >= sizeof(pi)) 
          i = 0;
        int num = pi[i]-'0';
        showNumber(num);
        delay(COUNT_DELAY);
        i++;
      }
      showNumber(0);
      Serial.readString();
      if(DEBUG) Serial.println("Stopped pi");
    }
    else if(string.startsWith("count"))
    {
      if(DEBUG) Serial.println("Started count");
      for(int i = 9; i >= 0; i--)
      {
        showNumber(i);
        delay(COUNT_DELAY);
      }
      if(DEBUG) Serial.println("Finished count");
    }
    else if(string.startsWith("upn"))
    {
      string.remove(0, 3);
      int num = string.toInt();
      if(num < 0 || num >= sizeof(servo)) 
        return true;
      if(DEBUG) Serial.println(String(num) + " up");
      servo[num].write(servo_angles[num]);
    }
    else if(string.startsWith("dnn"))
    {
      string.remove(0, 3);
      int num = string.toInt();
      if(num < 0 || num >= sizeof(servo)) 
        return true;
      if(DEBUG) Serial.println(String(num) + " down");
      servo[num].write(0);
    }
    else if(string.startsWith("up"))
    {
      if(DEBUG) Serial.println("All up");
      for(int i = 0; i < sizeof(servo); i++) 
      {
        servo[i].write(servo_angles[i]);
        delay(100);
      }
    }
    else if(string.startsWith("down"))
    {
      if(DEBUG) Serial.println("All down");
      for(int i = 0; i < sizeof(servo); i++) 
      {
        servo[i].write(0);
        delay(100);
      }
    }
    else
    {
      int num = string.toInt();
      if(num < 0 || num > 9) 
        return true;
      if(DEBUG) Serial.println("To show " + String(num));
      showNumber(num);
    }
  }
}
