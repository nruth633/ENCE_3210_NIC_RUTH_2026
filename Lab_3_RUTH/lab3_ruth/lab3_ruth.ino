//nic ruth lab 3

#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>


const int buttonPin = 2;
const int redPin = 5;
const int greenPin = 4;

//stuff that shows in all so volatile
volatile unsigned long secCount = 0;
volatile bool greenState = false;
volatile unsigned int t2Div = 0;

//task1 isr 1hz
ISR(TIMER1_COMPA_vect)
{
  greenState = !greenState;
  digitalWrite(greenPin, greenState ? HIGH : LOW);
  secCount++;
}

//task2 isr
ISR(TIMER2_COMPA_vect)
{
  t2Div++;
  if(t2Div >= 100)
  {
    t2Div = 0;

    int b = digitalRead(buttonPin);

    //pressed with pullup is low
    if(b == LOW) digitalWrite(redPin, HIGH);
    else digitalWrite(redPin, LOW);
  }
}

void setupTimer1_1hz()
{
  //timer1 ctc at 1hz and
  //16mhz/1024 = 15625 ticks per sec
  noInterrupts();

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = 15624;

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
}

void setupTimer2_1khz()
{
  //timer2 ctc at 1000hz, then divide by 100 to get 10hz
  //16mhz/64 = 250khz, ocr2a=249 gives 1000hz
  noInterrupts();

  TCCR2A = 0;
  TCCR2B = 0;
  TCNT2 = 0;

  TCCR2A |= (1 << WGM21);
  OCR2A = 249;

  TCCR2B |= (1 << CS22);
  TIMSK2 |= (1 << OCIE2A);

  interrupts();
}

void setup()
{
  Serial.begin(9600);
//on off
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(greenPin, LOW);
  digitalWrite(redPin, LOW);

  setupTimer1_1hz();
  setupTimer2_1khz();

  Serial.println("started");
}

void loop()
{
  static unsigned long lastPrint = 0;
  unsigned long nowSec;

  noInterrupts();
  nowSec = secCount;
  interrupts();

  if(nowSec - lastPrint >= 3)
  {
    lastPrint = nowSec;
    Serial.println("Hello! (every 3 sec)");
  }

  delay(10);
}