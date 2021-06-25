#include <Stepper.h>
#define BLYNK_PRINT Serial
#include <LiquidCrystal.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Ultrasonic.h>
/*#define triger 06
#define echo 07*/
//ultrasonic
Ultrasonic ultrasonic(12, 13);
int distance,duration;
//stepper
int IN1=04;
int IN2=0;
int IN3=02;
int IN4=14;
int step = 100;
int delaytime=2;
//blynk
char auth[] = "bIvMjTTXfGTMHc97vIM8zO1cUN-d5D6v";
char ssid[] = "IoT_Jemuran";
char pass[] = "satusampetiga";
WidgetLCD lcd(V5);
WidgetLED led(V6);
BlynkTimer timer;
/*void BlynkNotify(){
if(distance<=5){
    Blynk.notify("Jemuran Sudak Masuk");
  } else {
    Blynk.notify("Jemuran Sedang DiLuar");
  }
}*/
void setup() {
pinMode(16, INPUT);
pinMode(05,INPUT);
Blynk.begin(auth, ssid, pass);
Serial.begin(115200);
lcd.clear();
lcd.print(0, 0, "Kondisi : ");
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
// timer.setTimer(long, BlynkNotify, long);
}

void loop() {
    Blynk.run();
    timer.run();
// Sensor hujan---------
  lcd.clear();  
  lcd.print(0, 0, "Cuaca : ");
int cahaya = digitalRead (05);
int hujan = digitalRead (16);
Serial.println(cahaya);
Serial.println(hujan);
if (hujan==1){
  Serial.println("Cerah");
  lcd.print(0,0,"Cuaca:Cerah");
} else {
    Serial.println("Hujan");
    lcd.print(0,0,"Cuaca:Hujan");
    Blynk.notify("Cuaca Sedang Hujan !");
}
if (cahaya==1){
    Serial.println("Mendung");
    lcd.print(0,1,"Kondisi:Mendung");
    Blynk.notify("Kondisi Sedang Mendung!");
  } else {
      Serial.println("Terang");
      lcd.print(0,1,"Kondisi:Terang");
  }
  //ultrasonik
distance = ultrasonic.read();
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
delay(1000);
// led
if(distance<=5){
    led.on();
  } else {
    led.off();
  }
}
BLYNK_WRITE(V1){
/* if (distance<=5){
  Serial.println("distance");
  step = 0;
  delaytime = 0;
} else {
  delaytime = 2; */  
  int i;
for(i=0; i <=1000; i++)
{
//step 4
step4();
delay(delaytime);

//step 3
step3();
delay(delaytime);

//step 2
step2();
delay(delaytime);

//step 1
step1();
delay(delaytime);
}
}
void step1(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,HIGH);
}

void step2(){
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
}

void step3(){
digitalWrite(IN1,HIGH);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
}

void step4(){
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
}
BLYNK_WRITE(V2){
/*if (distance<=5){
  Serial.println("distance");
  step = 0;
  delaytime = 0;
} else {
  delaytime = 2;*/
  int i;
for(i=0; i <=1000; i++)
{
//step 4
step1();
delay(delaytime);

//step 3
step2();
delay(delaytime);

//step 2
step3();
delay(delaytime);

//step 1
step4();
delay(delaytime);
}
}
