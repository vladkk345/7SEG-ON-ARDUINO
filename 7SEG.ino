#include <GyverTimers.h>
// Definiton digits
#define DIGIT1  0
#define DIGIT2  5
#define DIGIT3  7
#define DIGIT4  2
//----------------------------------------------------
int decToBcd(int val); // prototype function
//----------------------------------------------------

// Declaration variables
int pwm;
int data = 3;
int latch = 5;
int clk = 4;

byte reg;
// Setting value return from function in variables
byte first_digit = decToBcd(DIGIT1); 
byte second_digit = decToBcd(DIGIT2);
byte third_digit = decToBcd(DIGIT3);
byte fourth_digit = decToBcd(DIGIT4);

void setup() 
{
  // Settings pins
  pinMode(data, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(latch, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Timer2.setPeriod(2500); // Setting period
  Timer2.enableISR(); // Handler interrupt at timer
}

void loop() 
{
  // Setting brightness with potentiometer
  pwm = map(analogRead(0), 0, 1023, 0, 255); 
  pwm = constrain(pwm, 0, 255); // constain values
  analogWrite(11, pwm);
  delay(1);
  
  decToBcd(DIGIT1); // call function converter from decimal to bcd
  decToBcd(DIGIT2);
  decToBcd(DIGIT3);
  decToBcd(DIGIT4);
}

//-----------------------------------------------------------
// Function converter from decimal to bcd
int decToBcd(int val)
{
  // Show digits from 0 to 9
  switch(val)
  {
    case 0:
        reg = 0b11111100; // show 0
        break;
    case 1:
        reg = 0b01100000; // show 1
        break;
    case 2:
        reg = 0b11011010; // show 2
        break;
    case 3:
        reg = 0b11110010; // show 3
        break;
    case 4:
        reg = 0b01100110; // show 4
        break;
    case 5:
        reg = 0b10110110; // show 5
        break;
    case 6:
        reg = 0b10111110; // show 6
        break;
    case 7:
        reg = 0b11100000; // show 7
        break;
    case 8:
        reg = 0b11111110; // show 8
        break;
    case 9:
        reg = 0b11110110; // show 9
        break;
  }
  return reg;
}
ISR(TIMER2_A) 
{
  // Setting values on pins
  digitalWrite(7, LOW);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, first_digit); // setting value on led driver
  
  digitalWrite(7, HIGH);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, first_digit);
  digitalWrite(latch, HIGH);

  digitalWrite(8, LOW);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, second_digit);
  
  digitalWrite(8, HIGH);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, second_digit);
  digitalWrite(latch, HIGH);
  
  digitalWrite(9, LOW);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, third_digit);
 
  digitalWrite(9, HIGH);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, third_digit);
  digitalWrite(latch, HIGH);
  
  digitalWrite(10, 0);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, fourth_digit);
 
  digitalWrite(10, 1);
  digitalWrite(latch, LOW);
  shiftOut(data, clk, LSBFIRST, fourth_digit);
  digitalWrite(latch, HIGH); 
}
