// give your pin a nice label
#define x A5
#define y A4
#define btn 2
void setup() {
  // set your pin as input
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  pinMode(btn, INPUT);
  // initialise console
  Serial.begin(9600);
}
// initialise light value
int xv = 0;
int yv = 0;
int btnv = 0;
void loop() {
  // read from your pin
  xv = analogRead(x);
  yv = analogRead(y);
  btnv = digitalRead(btn);
  // display it into the console
  Serial.print("Joystick in: X: ");
  Serial.print(xv);
  Serial.print("   Y: ");
  Serial.print(yv);
  Serial.print("   btn: ");
  Serial.print(btnv);
  Serial.println();
  delay(20);
}
