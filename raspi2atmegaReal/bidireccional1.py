from serial import*
from time import*

arduino = Serial('/dev/ttyACM0',9600)
sleep(2)
try:
 while 1:
  comando =  raw_input("intro ")
  arduino.write(comando.encode())
  arduino.write('\r'.encode())
  arduino.flushInput()
  print ("enviado")
  sleep(3)
  try:
   print ("recibiendo datos: ")
   while not( arduino.in_waiting > 0):
    print ("datos recibidos")
    sleep (1.5)
    pass
   mens = arduino.readline().strip()
   print (mens)
  except:
   print("no data recive")

except(KeyboardInterrupt,SystemExit):
 print("")
 print("hasta la vista ")
 arduino.close()

