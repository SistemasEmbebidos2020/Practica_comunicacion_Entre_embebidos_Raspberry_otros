from serial import*
from time import*

atmega = Serial('/dev/ttyACM0',9600)
sleep(2)
try:
 while 1:
  comando =  raw_input("intro ")
  atmega.write(comando.encode())
  atmega.write('\r'.encode())
  atmega.flushInput()
  print ("enviado")
  sleep(3)
  try:
   print ("recibiendo datos: ")
   while not( atmega.in_waiting > 0):
    print ("datos recibidos")
    sleep (1.5)
    pass
   print ()
   mens = atmega.readline().strip()
   print (mens)
  except:
   print("no data recive")

except(KeyboardInterrupt,SystemExit):
 print("")
 print("hasta la vista ")
 atmega.close()

