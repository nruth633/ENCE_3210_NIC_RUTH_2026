//y[n] = 2*x[n] - x[n-1]

const int button1Pin = 2; //button 1 on d2 

//global arrays
volatile int x[10] = {3,5,8,6,4,10,9,7,2,1};
volatile int y[10] = {0};

//this is a flag so loop knows isr finished
volatile bool filterDone = false;

//debounce
volatile unsigned long lastUs1 = 0;

void button1Isr()
{
  unsigned long now = micros();
  if(now - lastUs1 < 20000)return; //20ms
  lastUs1 = now;

  //when no x[-1]), it will just use x[0]
  y[0] = 2*x[0] - x[0];

  for(int n=1;n<10;n++)
  {
    y[n] = 2*x[n] - x[n-1];
  }

  filterDone = true;
}

void setup()
{
  Serial.begin(9600);

  pinMode(button1Pin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button1Pin),button1Isr,FALLING);

  Serial.println("press button 1 to run filter");
}

void loop()
{
  if(filterDone)
  {
    int xLocal[10];
    int yLocal[10];

    noInterrupts();
    for(int i=0;i<10;i++)
    {
      xLocal[i] = x[i];
      yLocal[i] = y[i];
    }
    filterDone = false;
    interrupts();

    Serial.println("x array:");
    for(int i=0;i<10;i++)
    {
      Serial.print("x[");
      Serial.print(i);
      Serial.print("]=");
      Serial.println(xLocal[i]);
    }

    Serial.println("y array:");
    for(int i=0;i<10;i++)
    {
      Serial.print("y[");
      Serial.print(i);
      Serial.print("]=");
      Serial.println(yLocal[i]);
    }

    Serial.println("done");
  }

  delay(10);
}