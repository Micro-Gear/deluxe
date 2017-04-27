
int sensorPin = A0;    // select the input pin for the potentiometer
int rp = 9;      // select the pin for the LED
int gp = 10;      // select the pin for the LED
int bp = 11;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(rp, OUTPUT);
  pinMode(gp, OUTPUT);
  pinMode(bp, OUTPUT);
}

void setBRG(int rv, int gv, int bv){
  analogWrite(rp, rv);
  analogWrite(gp, gv);
  analogWrite(bp, bv);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  setBRG(sensorValue / 4, 0, 0);
  delay(100);
}
