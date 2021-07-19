#include "uart.h"


char* mensajes = "";
int main()
 { 
serial_begin();


   while (1)
     {

_delay_ms(1500);
serial_println_str("1");     //para el segundo c'odigo de python se coloca solo serial_println_str("1,2,3,4");
_delay_ms(1500);
serial_println_str("2");
_delay_ms(1500);
serial_println_str("3");
_delay_ms(1500);
serial_println_str("0");
_delay_ms(1500);
//_delay_ms(2000);

}
   return 0;
}
