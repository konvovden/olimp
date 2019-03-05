
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

const int servo_pins[7] = {3, 4, 5, 6, 7, 8, 9};

Servo servo[7];

bool DEBUG = true;

void setup() {

  Serial.begin(9600);
  for(int i = 0; i < sizeof(servo); i++)
  {
    servo[i].attach(servo_pins[i]);
  }
  showNumber(0);
  servo[0].write(90);
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
    if(servo[i].read() != 90*numbers[n][i]) 
      servo[i].write(90 * numbers[n][i]);
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
      String pi = "14159265359";
      for(int i = 0; i < sizeof(pi); i++)
      {
        if(Serial.available() > 0)
        {
          Serial.readString();
          if(DEBUG) Serial.println("Stopped pi");
          break;
        }
        int num = pi[i]-'0';
        showNumber(num);
        delay(COUNT_DELAY);
      }
      showNumber(0);
      if(DEBUG) Serial.println("Finished pi");
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
