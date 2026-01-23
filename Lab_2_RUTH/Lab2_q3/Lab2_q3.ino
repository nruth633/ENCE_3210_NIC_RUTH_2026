const int button1Pin = 2;  
const int button2Pin = 3;   
const int redPin   = 5;
const int greenPin = 4;

volatile long button1Count = 0;   
volatile long button2Count = 0;   
volatile unsigned long lastUs1 = 0;
volatile unsigned long lastUs2 = 0;

//arrays 
int arr1[10] = { 1,2,3,4, 5, 6,7,8,9,10 };
int arr2[10] = { 10,9,8,7,6,5,4,3,2,1 };
int arr3[10]; // results go here

//set leds
void setLeds(int r, int g)
{
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
}

// button1 interrupt
void button1Isr()
{
  unsigned long now = micros();
  if (now - lastUs1 > 20000) 
  {
    button1Count++;
    lastUs1 = now;
  }
}

// button2
void button2Isr()
{
  unsigned long now = micros();
  if (now - lastUs2 > 20000) //20ms debounce
  {
    button2Count++;
    lastUs2 = now;
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  setLeds(LOW, LOW);

  attachInterrupt(digitalPinToInterrupt(button1Pin), button1Isr, FALLING);
  attachInterrupt(digitalPinToInterrupt(button2Pin), button2Isr, FALLING);

  Serial.println("calculator ready:");
  Serial.println("button1: press 1/2/3 times to pick add/sub/mul");
  Serial.println("button2: press once to run the operation");
}

void loop()
{
  static long lastB2 = 0;     //supposed to detected new press
  long b1, b2;

//counts
  noInterrupts();
  b1 = button1Count;
  b2 = button2Count;
  interrupts();
//1,2,3 based on mod 3 on button 1
  int op = (int)(b1 % 3);

  //show selected op with leds
  //both on is blu
  if (op == 1)
  {
    //add
    setLeds(HIGH, LOW);   // red
  }
  else if (op == 2)
  {
    // sub
    setLeds(LOW, HIGH);   //green
  }
  else
  {
    // mul (op == 0)
    setLeds(HIGH, HIGH);  // blue
  }

  if (b2 != lastB2)
  {
    lastB2 = b2;

    setLeds(LOW, LOW);

=    for (int i = 0; i < 10; i++)
    {
      if (op == 1)        arr3[i] = arr1[i] + arr2[i];  // add
      else if (op == 2)   arr3[i] = arr1[i] - arr2[i];  // sub
      else                arr3[i] = arr1[i] * arr2[i];  // mul
    }

    // printing is weird idk how to fix it, the buttons will change op but the results are all wrong
    Serial.println("arr3 results:");
    for (int i = 0; i < 10; i++)
    {
      Serial.print("arr3[");
      Serial.print(i);
      Serial.print("] = ");
      Serial.println(arr3[i]);
    }

    
    setLeds(HIGH, HIGH);

    delay(500); 
  }

  delay(10); 
}