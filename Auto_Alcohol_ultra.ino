#include <LiquidCrystal.h>
const int rs = 5, en = 6, d4 = 7, d5 = 8, d6 = 9, d7 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include<Servo.h>
Servo myservo;
int count = -1;
int const ledpin = 0;
int const trigPin1 = 1;
int const echoPin1 = 2;
int const trigPin2 = 3;
int const echoPin2 = 4;
int timer = 0;
void setup(){
  Serial.begin(115200);
  lcd.begin(16,2);
  myservo.attach(13);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ledpin, OUTPUT);
  delay(200);
  }

void loop(){
  if (count == -1){
    lcd.setCursor(0,0);
    lcd.print("Ohayo! >_<                 ");
    lcd.setCursor(0,1);
    lcd.print("Alcohol fill -->           ");}
  
    
  int duration1, distance1; //Ultrasonic 1
  digitalWrite(trigPin1, HIGH);
  delay(1);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1 /2) / 29.1;
  Serial.print("Distance1 : ");Serial.println(distance1);

  int duration2, distance2; //Ultrasonic 2
  digitalWrite(trigPin2, HIGH);
  delay(1);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = (duration2 /2) / 29.1;
  Serial.print("Distance2 : ");Serial.println(distance2);

  if (distance1 <= 2 && distance1 >= 0){ //Ultrasonic 1(Timer)
    count = count + 1;
    Serial.print("Count = ");Serial.println(count);}
  if (distance2 <= 10 && distance2 >= 0){
    if(timer == 0){ //Timer Off
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Status :");
        digitalWrite(ledpin, HIGH);
        Serial.println("Object detected");
        lcd.setCursor(0,1);
        lcd.print("Processing..");
        
        myservo.write(0);
        delay(1000);
        myservo.write(90);
        delay(1000);
        myservo.write(180);
        delay(1000);
        
        lcd.setCursor(0,0);
        lcd.print("Status :        ");
        lcd.setCursor(0,1);
        lcd.print("Done!             ");
        delay(1500);}
    else if (timer == 1){ //Timer On!
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Status :");
        digitalWrite(ledpin, HIGH);
        Serial.println("Object detected");
        lcd.setCursor(0,1);
        lcd.print("Processing..");
        
        myservo.write(0);
        delay(1000);
        myservo.write(90);
        delay(1000);
        myservo.write(180);
        delay(1000);
        
        for (int i = 15; i>0 ; i--){ //Timer
        lcd.setCursor(0,0);
        lcd.print("Wash hand... 15sec      ");
        lcd.setCursor(0,1);
        lcd.print("Time left: ");
        lcd.print(i);
        lcd.print(" ");
        
        
        lcd.setCursor(0,0);
        lcd.print("Status :        ");
        lcd.setCursor(0,1);
        lcd.print("Done!             ");
        delay(1500);
        }
      
      }  
    else{
      digitalWrite(ledpin, LOW);
      Serial.println("No object detect!");}

  }}
