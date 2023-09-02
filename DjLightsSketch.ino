#include <TM1637Display.h>


//looping buttons
const int doublePin = 5;
const int halfPin = 7;
const int normalPin = 6;


//rotary encoder
const int rotaryBtn = 2;
const int rotB = 3;
const int rotA = 4;
int rotAState = LOW;
int rotALastState = rotAState;
int lastRotBtnState;

//display 
const int dispDataPin = 10;
const int dispClockPin = 16;
uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
TM1637Display display(dispClockPin, dispDataPin);

//led output pin
const int ledPin = 14;

//variables
float currentBPM = 126;
float storedBPM = 126;
int millsBetweenFlash;
float multiplier = 1;
int flashDuration = 25;
bool multiplied = false;

unsigned long currentMillis;
unsigned long previousMillis;
unsigned long buttonMillis;






void setup() 
{
  pinMode(doublePin, INPUT_PULLUP);
  pinMode(halfPin, INPUT_PULLUP);
  pinMode(normalPin, INPUT_PULLUP);
  pinMode(rotaryBtn, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);

  pinMode(rotA,INPUT_PULLUP);
  pinMode(rotB,INPUT_PULLUP);
  rotAState = digitalRead(rotA);
  lastRotBtnState = digitalRead(rotaryBtn);

  millsBetweenFlash = round(60000/currentBPM) - round(flashDuration/2);
  currentMillis = millis();
  previousMillis = 0;

  display.setBrightness(0x0f);
  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);

  display.clear();
  display.showNumberDec(currentBPM, false);

  attachInterrupt(digitalPinToInterrupt(rotB),UpdateRotary,CHANGE);

  Serial.begin(9600);
}

void loop() 
{
  //start button
  int rotBtnState = digitalRead(rotaryBtn);
  if(rotBtnState == HIGH && lastRotBtnState == LOW) //is no longer pressed
  {
    FlashLeds();
    delay(20);
  }

  lastRotBtnState = digitalRead(rotaryBtn);

  CheckLoopingButtons();

  if(multiplier == 1)
  {
    multiplied = false;
    storedBPM = currentBPM;
    flashDuration = 100;
  }


  millsBetweenFlash = round(60000/currentBPM) - flashDuration;

  currentMillis = millis();
  if(currentMillis - previousMillis >= millsBetweenFlash)
  {
    if(rotBtnState != LOW)
      FlashLeds();
  }

  

}

void CheckLoopingButtons()
{
    int doubleButtonState = digitalRead(doublePin);
  int halfButtonState = digitalRead(halfPin);
  int normalButtonState = digitalRead(normalPin);

  if(doubleButtonState == HIGH)
  {
    Serial.println("DoubleButton Pressed");
    if(!multiplied)
    {
      storedBPM = currentBPM;
      multiplied = true;
    }
    multiplier *= 2;
    currentBPM *= 2;
    flashDuration /= 2;
    display.showNumberDec(currentBPM, false);
    delay(150);
  }
   if(halfButtonState == HIGH)
  {
    Serial.println("HalfButton Pressed");
     if(!multiplied)
    {
      storedBPM = currentBPM;
      multiplied = true;
    }
    multiplier /= 2;
    currentBPM /=2;
    display.showNumberDec(currentBPM, false);
    delay(150);
  }
   if(normalButtonState == HIGH)
  {
    Serial.println("NormalButton Pressed");
    currentBPM = storedBPM;
    multiplied = false;
    multiplier = 1;
    display.showNumberDec(currentBPM, false);
    delay(150);
  }
}

void UpdateRotary()
{
 rotAState = digitalRead(rotA);

 if((rotALastState == LOW) && (rotAState == HIGH))
 {
  if(digitalRead(rotB) == HIGH) 
  {
    currentBPM++;
    storedBPM = currentBPM;
  }else
  {
    currentBPM--;
    storedBPM = currentBPM;
  }
  display.showNumberDec(currentBPM, false);

 }

 rotALastState = rotAState;

}

void FlashLeds()
{
  digitalWrite(ledPin, HIGH);
  delay(flashDuration);
  digitalWrite(ledPin,LOW);
  previousMillis = millis();
}
