#include <IRremote.h>
#include <Servo.h>

#define pwmA A5
#define pwmB A3
#define bFront 10
#define bBack 9
#define aBack 6
#define aFront 5
#define RECV_PIN A0
#define servoPin 3
#define trigPin  12
#define echoPin 11
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


Servo servo;
IRrecv irrecv(RECV_PIN);
decode_results results;

int lastDir = -1;

unsigned int distance;
bool mode = 1; //0 for manual, 1 for automatic
unsigned int leftDist, rightDist;
unsigned int deg;

void stop() {
  analogWrite(pwmA, 0);
  analogWrite(pwmB, 0);
  return;
}


int ping() {
  long duration, distance; // start the scan
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // convert the distance to centimeters.
  return distance;
}


int precisePing(int count) {
  int suma = 0;
  for (int i = 0; i < count; i++)
    suma += ping();
  suma /= count;
  return suma;
}

void move(int lastDir) {
  /* move the motors depending on direction
            0
            ^
            |
      3 <------> 1
            |
            v
            2
  */
  switch (lastDir) {
    case 0: //forward
      analogWrite(pwmA, 255);
      analogWrite(pwmB, 255);
      digitalWrite(aFront, HIGH);
      digitalWrite(aBack, LOW);
      digitalWrite(bFront, HIGH);
      digitalWrite(bBack, LOW);
      break;
    case 2: //back
      analogWrite(pwmA, 200);
      analogWrite(pwmB, 200);
      digitalWrite(aFront, LOW);
      digitalWrite(aBack, HIGH);
      digitalWrite(bFront, LOW);
      digitalWrite(bBack, HIGH);
      break;
    case 1: //left
      analogWrite(pwmA, 200);
      analogWrite(pwmB, 0);
      digitalWrite(aFront, HIGH);
      digitalWrite(aBack, LOW);
      digitalWrite(bFront, LOW);
      digitalWrite(bBack, LOW);
      break;
    case 3: //right
      analogWrite(pwmA, 0);
      analogWrite(pwmB, 200);
      digitalWrite(aFront, LOW);
      digitalWrite(aBack, LOW);
      digitalWrite(bFront, HIGH);
      digitalWrite(bBack, LOW);
      break;
  }
  return;
}
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(aFront, OUTPUT);
  pinMode(aBack, OUTPUT);
  pinMode(bFront, OUTPUT);
  pinMode(bBack, OUTPUT);
  servo.attach(3);
  servo.write(133);
}

void loop() {
  //MANUAL MODE
  if (mode == 0) {
    while (irrecv.decode(&results)) {
      Serial.println(results.value);
      switch (results.value) {
        case 16730295: //forward
          move(0);
          lastDir = 0;
          break;
        case 16742535: //back
          move(2);
          lastDir = 2;
          break;
        case 16712445: //left
          move(3);
          lastDir = 3;
          break;
        case 16720095: //right
          move(1);
          lastDir = 1;
          break;
        case 4294967295: //default value when pressing
          move(lastDir);
          break;
      }
      irrecv.resume();
      delay(100);
    }
    stop();

  }
  //AUTOMATIC MODE
  else {
    //Serial.println(precisePing(10));
    if (precisePing(10) > 25) {
      move(0);
    }
    else {
      stop();
      move(2);
      delay(250);
      stop();
      servo.write(88);
      rightDist = precisePing(5);
      delay(250);
      Serial.print("Right dist : ");
      Serial.println(rightDist);
      servo.write(178);
      leftDist = precisePing(5);
      delay(250);
      Serial.print("Left dist : ");
      Serial.println(leftDist);
      servo.write(133);
      if (leftDist > rightDist) {
        move(3);
        delay(300);
        stop();
      }
      else {
        move(1);
        delay(300);
        stop();
      }
    }
  }
}
