#define echoPin 7
#define trigPin 8

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


void setup(){
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop(){
  Serial.println(precisePing(10));
  delay(10);
}
