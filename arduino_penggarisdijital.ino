/*
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#include <LiquidCrystal.h>


// dari rs (LCD pin 4) ke Arduino pin 12
// dari rw (LCD pin 5) ke Arduino pin 11
// dari enable (LCD pin 6) ke Arduino pin 10
// dari LCD pin 15 ke Arduino pin 13
// dari LCD pins d4, d5, d6, d7 to Arduino pins 5, 4, 3, 2
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

int backLight = 13;    // untuk ngatur backlight LCD

#define trigPin 9
#define echoPin 8
#define led 7
#define led2 6

void setup() {
  Serial.begin (9600);
  

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  
  
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // nyalakan backlight LCD
  lcd.begin(16,2);              // kolom dan baris dari 16x2
  lcd.clear();                  // mulai dengan layar kosong



}

void loop() {

  if(digitalRead(pirPin)==HIGH)  {
    lcd.setCursor(0,0);
    lcd.print('terdeteksi!');
    if (lockLow) {
      lockLow = false;
  }
  }
  
  if(digitalRead(pirPin) == LOW){       
       lcd.setCursor(0,0);
        lcd.print('aman');

       if(takeLowTime){
        lowIn = millis();
        takeLowTime = false;
        }

       if(!lockLow && millis() - lowIn > pause){  
           
           lockLow = true;                        
           
           delay(50);
           }
       }
  
  
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  

    
  if (distance < 10) { 
    digitalWrite(led,HIGH);
    digitalWrite(led2,LOW);
  

  
}
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  if (distance >= 200 || distance <= 0){
    //Serial.println("Out of range");

     //LCD configuration
    lcd.clear();    
//    lcd.setCursor(0,0);      
//    lcd.print("Jarak : ");   
    lcd.setCursor(0,1);        
    lcd.print("lebih dari 200cm ");
  }
  else {
//    Serial.print(distance);
//    Serial.println(" cm");

     //LCD configuration
    lcd.clear();                 
    lcd.setCursor(0,1);          
    lcd.print(distance);
    lcd.setCursor(4,1);          
    lcd.print("cm");
  }
  delay(500);
}

