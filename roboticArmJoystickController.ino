#include <Servo.h>

Servo Servo_X;
Servo Servo_Y;
Servo gripper;
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequency = 0;
int color = 0;
int mode = 0;

#define Joy_X A0
#define Joy_Y A1
#define btn 8
int Joy_Val = 0;

void setup()
{
  // joystick and servo connection
  Servo_X.attach(11);
  Servo_Y.attach(10);
  gripper.attach(12);

  //button on joystick
  digitalWrite(btn, HIGH);

  // color sensor pins
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // color sensor set to listen mode
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // moving the end effector of the arm and the base of the arm towards the
  // place where pens are kept
  gripper.write(90);
  delay(2000);
  Servo_x.write(0);
  delay(2000);

  Serial.begin(9600);
}

void loop()
{

  if (digitalRead(btn) == 0) mode++;

  // freehand movement using joystick mode
  if (mode % 2 != 0) {
    Serial.println("Freehand Drawing Mode");
    Joy_Val = analogRead(Joy_X);
    Joy_Val = map(Joy_Val, 0, 1023, 180, 0);
    Servo_X.write(Joy_Val);

    Joy_Val = analogRead(Joy_Y);
    Joy_Val = map(Joy_Val, 0, 1023, 0, 180);
    Servo_Y.write(Joy_Val);
    delay(15);
  }

  // color choosing mode, choosing a pen of a desired color
  else {
    Serial.println(" Choose the desired color:");
    Serial.println("1.Red");
    Serial.println("2.Green");
    Serial.println("3.Blue");
    int ch = Serial.read() - '0';
    color = readColor(ch);
    delay(10);

    if (color == 1) {  //RED

      gripper.write(90);   //open
      delay(2000);


      gripper.write(0);  //close
      delay(2000);

      base.write(35);
      delay(2000);

      gripper.write(90);   //open
      delay(2000);

      gripper.write(0);  //close
      delay(2000);

      base.write(0);
      delay(2000);

      gripper.write(90);   //open
      delay(2000);

    }
    else if (color == 2) { //GREEN

      gripper.write(90);   //open
      delay(2000);

      gripper.write(0);  //close
      delay(2000);

      base.write(65);
      delay(2000);

      gripper.write(90);   //open
      delay(2000);

      gripper.write(0);  //close
      delay(2000);

      base.write(0);
      delay(2000);

      gripper.write(90);   //open
      delay(2000);

    }
    else if (color == 3) {       //BLUE

      gripper.write(90);   //open
      delay(2000);

      gripper.write(0);  //close
      delay(2000);

      base.write(95);
      delay(2000);

      gripper.write(90);   //open
      delay(2000);

      gripper.write(0);  //close
      delay(2000);

      base.write(0);
      delay(2000);

      gripper.write(90);   //open
      delay(2000);
    }
    color = 0;
  }
}

// for sensing the surface and converting color sensor input to rgb color
int readColor()
{
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);

  int R = frequency;
  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);

  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);

  int G = frequency;
  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);

  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);

  int B = frequency;
  Serial.print("B= ");
  Serial.print(frequency);
  Serial.println("  ");
  delay(50);

  if ((R < 124 && R > 104) && (G < 181 && G > 161) && (B < 55 && B > 35)) {
    color = 1; // Red
  }
  if ((R < 140 && R > 120) && (G < 161 && G > 141) && (B < 55 && B > 35)) {
    color = 2; // Green
  }
  if ((R < 160 && R > 140) && (G < 176 && G > 156) && (B < 58 && B > 38)) {
    color = 3; // Blue
  }
  return color;
}
