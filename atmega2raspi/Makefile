MCU = atmega328p
F_CPU = 16000000
CC = avr-gcc
CFLAGS= -O2 -Wall -std=gnu11 -mmcu=$(MCU)
CPPFLAGS=-DF_CPU=$(F_CPU)
OBJCOPY=avr-objcopy
CMD_FLASH=avrdude
MCU1 = ATMEGA328P
DEVPORT = /dev/ttyACM0 #puede que USB0 le salga error y debera cambiar a ACM0, o el numero de puerto asignado a su ATmega.
BAUDRATE=115200
.PHONY: default
default : EXE_FILE HEX_FILE flash
EXE_FILE: $(FNAME).c
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o $(FNAME)
HEX_FILE: $(FNAME)
	$(OBJCOPY) -O ihex $< $(FNAME).hex
flash : $(FNAME).hex
	$(CMD_FLASH) -F -V -c arduino -p $(MCU) -P $(DEVPORT) -b $(BAUDRATE) -U $@:w:$<
