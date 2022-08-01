#con main1.c
from serial import*
from time import*

atmega = Serial('/dev/ttyACM0',9600)
sleep(0.2)
try:
 atmega.flushInput()
 sleep(0.3)
 while 1:
  if atmega.in_waiting > 0:
   mens = atmega.readline().strip()
   sleep(0.3)
   print (mens.decode())

except(KeyboardInterrupt,SystemExit):
 print("")
 print("hasta la vista ")
 atmega.close()

