#include <Servo.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

#define proxi_ind 23
#define proxi_cap 25
#define infrared A7
#define led_green 41
#define led_red 45
#define buzzer  37
#define trig1 49
#define echo1 12
#define trig2 51
#define echo2 13

int indState;
int capState;
int infraState;

Servo servo1;
Servo servo2;

int pos = 0;
long duration1;
int distance1;
long duration2;
int distance2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(led_green, OUTPUT);
  pinMode(led_red, OUTPUT);
  pinMode(proxi_ind, INPUT_PULLUP);
  pinMode(proxi_cap, INPUT_PULLUP);
  pinMode(infrared, INPUT);
  pinMode(buzzer,  OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  
  servo1.attach(8);
  servo2.attach(9);
  servo1.write(170);
  servo2.write(119);

  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.setCursor(1, 0);         // move cursor to   (0, 0)
  lcd.print("Smart Trashbin");        // print message at (0, 0)
  digitalWrite(buzzer, HIGH);
  delay(2000);
  digitalWrite(buzzer,LOW);
  lcd.setCursor(0,1);
  lcd.print("by LSKI Students");
  delay(5000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd_displayNormal();
  hcsr1();
  hcsr2();
  infraState = digitalRead(infrared);
  indState = digitalRead(proxi_ind);
  capState = digitalRead(proxi_cap);
  delay(1000);
  if (indState == 0 && capState == 0 && infraState == 0){
    if(distance1 >= 6){
    lcd_anorganik();
    beep();
    servo1.write(70);
    digitalWrite(led_green, HIGH);
    delay(3000);
    servo1.write(170);
    digitalWrite(led_green, LOW);
    lcd.clear();
    }
    else{
      lcd_sampahPenuh();
      digitalWrite(led_green, HIGH);
      servo1.write(170);
      beep();
      delay(3000);
      digitalWrite(led_green, LOW);
      lcd.clear();
    }
  }

  if (indState == 1 && capState == 0 && infraState == 0){
    if (distance2>=6){
      lcd_organik();
      beep();
      servo2.write(19);
      digitalWrite(led_red, HIGH);
      delay(3000);
      digitalWrite(led_red, LOW);
      servo2.write(119);
      lcd.clear();  
    }
    else{
      lcd_sampahPenuh();
      servo2.write(119);
      digitalWrite(led_red, HIGH);
      beep();
      delay(3000);
      digitalWrite(led_red, LOW);
      lcd.clear();
    }
  }

  if (indState == 1 && capState == 1 && infraState == 0){
    if(distance1 >= 6){
      lcd_anorganik();
      beep();
      servo1.write(70);
      digitalWrite(led_green, HIGH);
      delay(3000);
      servo1.write(170);
      digitalWrite(led_green, LOW);
      lcd.clear();
    }
    else{
      lcd_sampahPenuh();
      digitalWrite(led_green, HIGH);
      servo1.write(170);
      beep();
      delay(3000);
      digitalWrite(led_green, LOW);
      lcd.clear();
    }
  }

  else {
    digitalWrite(led_green, LOW);
    digitalWrite(led_red, LOW);
  }
}

void lcd_displayNormal() {
  lcd.setCursor(1, 0);         // move cursor to   (0, 0)
  lcd.print("Silahkan Scan");        // print message at (0, 0)
  lcd.setCursor(2,1);
  lcd.print("Sampah Anda");
}

void lcd_anorganik(){
  lcd.clear();
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Buang di tempat");        // print message at (0, 0)
  lcd.setCursor(3,1);
  lcd.print("Anorganik");
}

void lcd_organik(){
  lcd.clear();
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Buang di tempat");        // print message at (0, 0)
  lcd.setCursor(5,1);
  lcd.print("Organik");
}

void lcd_sampahPenuh(){
  lcd.clear();
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Tempat Sampah");        // print message at (0, 0)
  lcd.setCursor(5,1);
  lcd.print("Penuh");
}

void beep (){
  digitalWrite(buzzer,HIGH);
  delay(50);
  digitalWrite(buzzer,LOW);
  delay(50);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
}

void hcsr1(){
  // Clear the trigPin by setting it LOW:
  digitalWrite(trig1, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);

  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration1 = pulseIn(echo1, HIGH);
  // Calculate the distance:
  distance1 = duration1 * 0.034 / 2;

  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  //Serial.print("Distance 1 = ");
  //Serial.print(distance1);
  //Serial.println(" cm");

  delay(50);
}

void hcsr2(){
  // Clear the trigPin by setting it LOW:
  digitalWrite(trig2, LOW);
  delayMicroseconds(5);

  // Trigger the sensor by setting the trigPin high for 10 microseconds:
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);

  // Read the echoPin, pulseIn() returns the duration (length of the pulse) in microseconds:
  duration2 = pulseIn(echo2, HIGH);
  // Calculate the distance:
  distance2 = duration2 * 0.034 / 2;

  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
  Serial.print("Distance 2 = ");
  Serial.print(distance2);
  Serial.println(" cm");

  delay(50);
}
