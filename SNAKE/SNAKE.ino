#include <MemoryFree.h>
#include <LedControl.h>
#define x A0
#define y A1
#define buzzerPin 6

//sarpele este reprezentat printr-un queue (implementat cu lista inlantuita)
struct point
{
  char i;
  char j;
};

struct node
{
  point data;
  node* next;
};

node * rear = new node;
node * front = new node;
point dirs[] = { { -1, 0}, {0, 1}, {1, 0}, {0, -1} }; //cum se schimba indicele in functie de directie
bool snakePos[8][8];
char lastDir = 1; //ultima directie
LedControl leds(12, 11, 10, 1);
point fruit;

void push(point a) //works
{
  node *p = new node;
  p->data = a;
  p->next = NULL;
  rear->data = a;

  node* cur = front;
  leds.setLed(0, rear->data.i, rear->data.j, 1);
  snakePos[rear->data.i][rear->data.j] = 1;
  while (cur)
  {
    if (cur->next == NULL)
    {
      cur->next = p;
      return;
    }
    cur = cur->next;
  }
  
}

void pop() //works
{ node * temp = front;
  leds.setLed(0, front->data.i, front->data.j, 0);
  snakePos[front->data.i][front->data.j] = 0;
  front = front->next;
  delete temp;
  return;
}

void generateFruits()
{
  fruit.i = random(0, 8);
  fruit.j = random(0, 8);
  if (snakePos[fruit.i][fruit.j] == 1)
    generateFruits();
  else
    leds.setLed(0, fruit.i, fruit.j, 1);
  return;

}


void changeDir() {
  if (analogRead(x) > 600 && lastDir != 3) {
    lastDir = 1;
    return;
  }
  if (analogRead(x) < 400 && lastDir != 1) {
    lastDir = 3;
    return;
  }
  if (analogRead(y) > 600 && lastDir != 0) {
    lastDir = 2;
    return;
  }
  if (analogRead(y) < 400 && lastDir != 2) {
    lastDir = 0;
    return;
  }
}
void moveSnake() {
  push({(rear->data.i + dirs[lastDir].i + 8) % 8, (rear->data.j + dirs[lastDir].j + 8) % 8});
  pop();
  return;
}

bool stillAlive()
{
  if(snakePos[(rear->data.i + dirs[lastDir].i + 8) % 8][(rear->data.j + dirs[lastDir].j + 8) % 8]==0)
    return 0;
  return 1;
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  leds.shutdown(0, 0);
  leds.setIntensity(0, 8);
  pinMode(buzzerPin, OUTPUT);
  front->next = NULL;
  front->data.i = 0;
  front->data.j = 0;
  rear->next = NULL;
  //push(front->data);
  generateFruits();
  //pop();

}

void loop() {
  changeDir();
//  if(!stillAlive)
//    for(;;);
  moveSnake();

  if ( rear->data.i == fruit.i && rear->data.j == fruit.j ) {
    push({fruit.i, fruit.j});
    tone(buzzerPin, 500, 20);
    generateFruits();
  }

  Serial.print("Free memory: ");
  Serial.println(freeMemory());
  for(int a=0; a<8; a++)
    {for(int b=0; b<8; b++)
      Serial.print(snakePos[a][b]);
     Serial.println();
    }
  Serial.print("\n\n\n");
      

  delay(200);

}
