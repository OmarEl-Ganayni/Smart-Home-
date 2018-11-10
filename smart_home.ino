#include <SoftwareSerial.h>
#include <Servo.h>
int pos = 0;
int tempPin = A0;   // select the input pin for temp sensor
int ldrPin = A1; // select the input pin for ldr sensor
int gasPin=A2; // select the input pin for gas sensor
int lamp = 8; // select the output pin for lamp NO(normal open)
int lamp2 = 9; //select the output pin for lamp using relay (normal closed)
int fan = 10; //select the output pin for fan cooling by relay (normal closed)
int kettle = 11; //select the output pin for kettle by relay (normal closed)
int buzzer = 12; // select the output for buzzer when gas sensor give alram 
int state = 0;
int flag = 0;
int sensorValue = 0; // variable to store the value coming from the sensor
int tempMin = 18;   // the temperature to start the fan
int tempMax = 30;   // the maximum temperature when fan is at 100%
void setup() {
Serial.begin(9600); //sets serial port for communication
pinMode(tempPin, INPUT);
pinMode(gasPin,INPUT);
pinMode(ldrPin,INPUT);
pinMode(lamp, OUTPUT);
digitalWrite(lamp, LOW);
pinMode(buzzer, OUTPUT);
digitalWrite(buzzer, LOW);
pinMode(lamp2, OUTPUT);
digitalWrite(lamp2, LOW);
pinMode(fan, OUTPUT);
digitalWrite(fan, LOW);
pinMode(kettle, OUTPUT);
digitalWrite(kettle, LOW);

}

 
void loop() { 
 if(Serial.available() > 0){
 state = Serial.read();
 flag=0;
 }

 if (state == '1') {
 digitalWrite(lamp2, HIGH);
 if(flag == 0){
 Serial.println("Relay: on");
 flag = 1;
 }
 }

 else if (state == '0') {
 digitalWrite(lamp2, LOW);
 if(flag == 0){
 Serial.println("Relay: OFF");
 flag = 1;
 }
 }
 
   if (state == '2') {
 digitalWrite(kettle, HIGH);
 if(flag == 0){
 Serial.println("Relay: on");
 flag = 1;
 }
 }

 else if (state == '3') {
 digitalWrite(kettle, LOW);
 if(flag == 0){
 Serial.println("Relay: OFF");
 flag = 1;
 }
 }
 sensorValue = analogRead(ldrPin); // read the value from the sensor
Serial.println(sensorValue); //prints the values coming from the sensor on the screen
 
 if(sensorValue > 90){ //setting a threshold value
  digitalWrite(lamp,HIGH); //turn relay ON
  delay (700);
 }
 else {digitalWrite(lamp,LOW); //turn relay OFF
   delay(700);}
    
    
    int gas;
  gas=analogRead(gasPin);
  if(gas>512)
  {
    Serial.println("dangerous!!");  
    digitalWrite(buzzer,HIGH);
    delay(500);
    digitalWrite(buzzer,LOW);
    delay(500);
   }
   else
   {
      Serial.println("No dangerous!"); 
      digitalWrite(buzzer,LOW);
      delay(1500);
   }
int rawvoltage= analogRead(tempPin);
float millivolts= (rawvoltage/1024.0) * 5000;
float celsius= millivolts/10;
Serial.print(celsius);
Serial.print(" degrees Celsius, ");

if(celsius>=tempMax) 
{ digitalWrite(fan, HIGH);
Serial.println("Relay: on");
}

else if (celsius<=tempMin) 
{digitalWrite(fan, LOW);
Serial.println("Relay: OFF");}
}




