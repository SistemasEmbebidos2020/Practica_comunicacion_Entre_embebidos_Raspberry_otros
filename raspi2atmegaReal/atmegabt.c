#include <Arduino.h>
#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  

SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
String lect;

uint8_t led1 =4;
uint8_t led2 =5;

void setup()
{
  DDRD |= (1<<led1) | (1<<led2);
  BT.begin(9600);       // Inicializamos el puerto serie BT que hemos creado
  Serial.begin(9600);   // Inicializamos  el puerto serie  
}
 
void loop()
{
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    lect = BT.readStringUntil('\n');
  }
  Serial.println(lect);
  if (lect == "on1") PORTD |= (1<<led1);
  else if (lect == "off1") PORTD &= ~(1<<led1);
  else if (lect == "on2") PORTD |= (1<<led2);
  else if (lect == "off2") PORTD &= ~(1<<led2);
  else if (lect == "offall")  for (int i=4;i<=5;i++) PORTD &= ~(1<<i);
  else if (lect == "onall")   for (int i=4;i<=5;i++) PORTD |= (1<<i);

}
