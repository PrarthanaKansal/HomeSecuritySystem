#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10); //9=red //10=blue

int FlamePin = 2;
int Flame = HIGH;

int sensor=7;
int gas_value;

int fire_min = 0;
int fire_max = 270;

int gas_min= 0;
int gas_max= 180;

Servo fireservo;
Servo gasservo;

void setup() {

  mySerial.begin(9600);
  Serial.begin(9600); 
  
  pinMode(FlamePin, INPUT);
  pinMode(sensor,INPUT);
    
  fireservo.attach(3); 
  fireservo.write(fire_min);
  
  gasservo.attach(6);
  gasservo.write(gas_min);
}

void loop() {
  Flame = digitalRead(FlamePin);
  gas_value =digitalRead(sensor);
  if (Flame== HIGH)
  {
    FIRETEXT();
  }
  if(gas_value==LOW)
  {
    GASTEXT();
  }
}

void GASTEXT()
{
  gasservo.write(gas_max);
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+919599231650\"\r"); // change to the phone number you using 
  delay(1000);
  mySerial.println("EMERGENCY; GAS LEAKAGE!");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(1000);
  mySerial.println((char)26);//the message stopping character
  delay(1000);
}
void FIRETEXT()
{
  fireservo.write(fire_max);
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+919999366967\"\r"); // change to the phone number you using 
  delay(1000);
  mySerial.println("EMERGENCY; FIRE");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(1000);
  mySerial.println((char)26);//the message stopping character
  delay(1000);
}

