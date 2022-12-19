import I2C_LCD_driver
from time import *

I2C_LCD_driver.lcd_begin(0x27)
mylcd = I2C_LCD_driver.lcd()

mylcd.lcd_display_string("Hola mundo.", 1)
mylcd.lcd_display_string("Hola Embebidos", 2)
