//sets our constants

const int button1Pin = 2;
const int button2Pin = 3;
const int redPin   = 5;
const int greenPin = 4;

volatile long button1Count = 0;
volatile long button2Count = 0;
volatile long diffCount = 0;
volatile unsigned long lastUs1 = 0;
volatile unsigned long lastUs2 = 0;

void setLeds(int r, int g)
{
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
}

void button1Isr()
{
  unsigned long now = micros();
  if (now - lastUs1 > 20000) //trying to use debounce used gpt to help
  {
    button1Count++;
    lastUs1 = now;
  }
}

void button2Isr()
{
  unsigned long now = micros();
  if (now - lastUs2 > 20000) // same
  {
    button2Count++;
    lastUs2 = now;
  }
}

void setup()
{
  //setup part setting pins
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  setLeds(LOW, LOW);

  attachInterrupt(digitalPinToInterrupt(button1Pin), button1Isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2Pin), button2Isr, FALLING);
}

void loop()
{
  long b1, b2, d;

  noInterrupts();
  b1 = button1Count;
  b2 = button2Count;
  interrupts();

  d = b1 - b2;

  noInterrupts();
  diffCount = d;   
  interrupts();

  if (d > 0)
  {
    // button1 more than button2
    setLeds(HIGH, LOW);   //red on green off
  }
  else if (d < 0)
  {
    // button2 more than button1
    setLeds(LOW, HIGH);   // red off g on
  }
  else
  {
    // blue is both on
    setLeds(HIGH, HIGH);  // both on
  }

  delay(10);
}