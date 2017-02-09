/*Demo program for the BYJ-48 stepper motor.
*Can also work for other similar stepper motors.
*Function step(x) causes motor to move x*4 steps.
*One revolution = 2048 steps, so for a revolution,
*call step(512). use negative x for reverse direction
*
 */

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

bool sequence[][4] = { {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,1,1,0},
                      {0,0,1,0}, {0,0,1,1}, {0,0,0,1}, {1,0,0,1} };
                      
void setup() {
  Serial.begin(115200);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  step(256);
  step(-256);
  Serial.println(60/(millis()/1000));
}

void loop() {
  step(1);
}

void step(int x){
  for(int i=0; i<abs(x); i++)
    for(int j=0; j<8; j++)
      if( x > 0 ){
        digitalWrite(IN1, sequence[j][0]);
        digitalWrite(IN2, sequence[j][1]);
        digitalWrite(IN3, sequence[j][2]);
        digitalWrite(IN4, sequence[j][3]);
        delay(1);
      }
     else{
      digitalWrite(IN1, sequence[8-j][0]);
      digitalWrite(IN2, sequence[8-j][1]);
      digitalWrite(IN3, sequence[8-j][2]);
      digitalWrite(IN4, sequence[8-j][3]);
      delay(1);
    }
}


