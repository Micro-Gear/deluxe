/*
*Program that simulates a theremin
*Changes the buzzer tone depending on the value read on the photoresistor.
*It has an initial 5 second calibration time.
*Inspired from Massimo Banzi:
* https://www.youtube.com/watch?v=57S3dylfw3I
 */

int ledPin = 13;
int sensorValue;
int sensorHigh = 0;
int sensorLow = 1024;

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  while(millis() < 5000){
    sensorValue = analogRead(A0);

    if(sensorValue>sensorHigh){
      sensorHigh = sensorValue;
    }

    if(sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }

  digitalWrite(ledPin, LOW);

}

void loop() {
  sensorValue = analogRead(A0);

  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);

  tone(8, pitch, 20);

  delay(10);
}
