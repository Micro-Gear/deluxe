// give your pin a nice label
#define photoPin A5

void setup() {
  // set your pin as input
  pinMode(photoPin, INPUT);
  // initialise console
  Serial.begin(9600);
}
// initialise light value
int light = 0;
void loop() {
  // read from your pin
  light = analogRead(photoPin);
  // display it into the console
  Serial.println(light);
  delay(20);
}
