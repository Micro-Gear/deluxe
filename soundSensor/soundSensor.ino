int minim = 1023;
int maxim = 0;
int num;
int sum;

int leds[] = {7, 8, 9, 10, 11};

void setup() {
  Serial.begin(9600);
  while (millis() < 5000) {
    num = analogRead(A0);
    if (num > maxim)
      maxim = num;
    if (num < minim)
      minim = num;
  }
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sum = 0;
  for(int i=0; i< 32; i++)
    sum += analogRead(A0);
  sum >>= 5;
  
  num = map(sum, minim, maxim, 0, 5);
  Serial.println(sum);
  for(int i=0; i<5; i++)
    if(i >= num)
      digitalWrite(leds[i], LOW);
    else
      digitalWrite(leds[i], HIGH);

}
