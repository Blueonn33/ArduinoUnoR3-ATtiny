#include <SoftwareSerial.h>
const uint8_t APIN2 = 0;
const uint8_t APIN3 = 1;
const uint8_t led = 3;
const uint8_t TPB = 2;
bool click = false;
SoftwareSerial UARTOut(APIN2, APIN3);

void setup(){  
  pinMode(TPB, INPUT);
  pinMode(led, OUTPUT);
  UARTOut.begin(4800);
  delay(100);
  UARTOut.print("Initiated ");
}

void loop()
{ 
  if(digitalRead(TPB)&& !click) {
    UARTOut.print(millis()); 
    digitalWrite(led, HIGH);
    click = true;
  }
  if(!digitalRead(TPB)){
    digitalWrite(led, LOW);
    click = false;
  }
  delay(5);     
}