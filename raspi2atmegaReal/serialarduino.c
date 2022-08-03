#include <Arduino.h>

String lect;

uint8_t led1 =4;
uint8_t led2 =5;

void setup()
{
  DDRD |= (1<<led1) | (1<<led2);
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  delay(5000);
}
 
void loop()
{
  lect = "";
  if(Serial.available()>0)    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    lect = Serial.readStringUntil('\r');
  }
  
  

  if (lect == "on1") {PORTD |= (1<<led1); Serial.println("led1 encendido") ;}
  else if (lect == "off1") {PORTD &= ~(1<<led1);  Serial.println("led1 apagado") ;}
  else if (lect == "on2") {PORTD |= (1<<led2); Serial.println("led2 encendido") ;}
  else if (lect == "off2") {PORTD &= ~(1<<led2);  Serial.println("led2 apagado") ;}
  else if (lect == "offall") { for (int i=4;i<=5;i++) PORTD &= ~(1<<i);  Serial.println("leds apagados") ;}
  else if (lect == "onall")  { for (int i=4;i<=5;i++) PORTD |= (1<<i);  Serial.println("leds encendidos") ;}
  delay(250);
}
