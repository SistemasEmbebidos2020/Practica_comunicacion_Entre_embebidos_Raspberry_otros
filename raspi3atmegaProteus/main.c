#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>
#define MAX_STR 50
#define BAUD 9600
/******************************************************************************************************************************/
/*                                                Funciones privadas o internas de la libreria						*/
/******************************************************************************************************************************/
volatile unsigned char rx_buffer[MAX_STR] = {0};
volatile unsigned char current_size = 0;
bool isReady = false;

ISR(USART_RX_vect){
   unsigned char ch = UDR0;
   if( ch == '\r' || ch == '\n'){
     rx_buffer[current_size] = 0;
     isReady = true;
   }
   else if( ch == '\b' && current_size>0){
     rx_buffer[--current_size] = 0;
   }
   else{
     rx_buffer[current_size++] = ch;
   }
}



/******************************************************************************************************************************/
/*                                                               Funciones pÃºblicas de la libreria						*/
/******************************************************************************************************************************/
/////////////////////////////////////////////
//inicializaciÃ³n del mÃ³dulo USART AVR modo asÃ­ncrono
//en una funciÃ³n, a 8bits,a 9600 baudios, sin bit de paridad
//1 bit de parada
/////////////////////////////////////////////////////
void serial_begin(){
	cli();
	float valor_UBBR0 = 0;
	UCSR0A=0b00000010;	//el bit 1 (U2X0) se pone en uno para duplicar la velocidad y poder utilizar frecuencias desde 1MHz
	UCSR0B=0b10011000;	//habilitar interrupcion por recepcion / transmisiÃƒÂ³n y recepciÃƒÂ³n habilitados a 8 bits
	UCSR0C=0b00000110;	//asÃƒÂ­ncrono, sin bit de paridad, 1 bit de parada a 8 bits
	valor_UBBR0 = F_CPU/(16.0*BAUD);	//Definir la constante BAUD al inicio del cÃƒÂ³digo
        if(UCSR0A & (1<<U2X0)) valor_UBBR0 *= 2;
	UBRR0=valor_UBBR0 - 1;
        sei();
}
///////////////////////////////////////////////
//recepciÃ³n de datos del mÃ³dulo USART AVR modo asÃ­ncrono
////////////////////////////////////////////////////////////
unsigned char serial_read_char(){
	if(UCSR0A&(1<<7)){  //si el bit7 del registro UCSR0A se ha puesto a 1
		return UDR0;    //devuelve el dato almacenado en el registro UDR0
	}
	else//sino
	return 0;//retorna 0
}
///////////////////////////////////////////////
//transmisiÃ³n de datos del mÃ³dulo USART AVR modo asÃ­ncrono
///////////////////////////////////////////////
void serial_print_char(unsigned char caracter){
        if(caracter==0) return;
	while(!(UCSR0A&(1<<5)));    // mientras el registro UDR0 estÃ© lleno espera
	UDR0 = caracter;            //cuando el el registro UDR0 estÃ¡ vacio se envia el //caracter
}
//////////////////////////////////////////////
//transmisiÃ³n de cadenas de caracteres con el mÃ³dulo USART AVR modo asÃ­ncrono
///////////////////////////////////////////////
void serial_print_str(char *cadena){	//cadena de caracteres de tipo char
	while(*cadena !=0x00){			//mientras el Ãºltimo valor de la cadena sea diferente
							        //al caracter nulo
		serial_print_char(*cadena);	//transmite los caracteres de cadena
		cadena++;				//incrementa la ubicaciÃ³n de los caracteres en cadena
								//para enviar el siguiente caracter de cadena
	}
}

void serial_println_str(char *cadena){
	serial_print_str(cadena);
	serial_print_char('\r');
	serial_print_char('\n');
}

char* get_RX_buffer(){
   current_size = 0;
   isReady = false;
   return (char*)rx_buffer;
}

bool is_data_ready(){
   return isReady;
}

void recibir_encender_led()
{
 if(is_data_ready())
   {
	if (get_RX_buffer()[0]=='A' && get_RX_buffer()[1]==0)
	 {
	 serial_println_str("encendido led1");
	 PORTB |=  (1<<PB2);
	 }
	 else if (get_RX_buffer()[0]=='B' && get_RX_buffer()[1]==0)
	 {
	 serial_println_str("encendido led2");
	 PORTB |=  (1<<PB3);
         }
	 else if (get_RX_buffer()[0]=='C' && get_RX_buffer()[1]==0)
	 {
	 serial_println_str("encendido led3");
	 PORTB |=  (1<<PB4);
	 }
	 else if (get_RX_buffer()[0]=='X' && get_RX_buffer()[1]==0)
	 {
	 serial_println_str("apagado led1");
	 PORTB &=  ~(1<<PB2);
	 }
	 else if (get_RX_buffer()[0]=='Y' && get_RX_buffer()[1]==0)
	 {
	 serial_println_str("apagado led2");
	 PORTB &=  ~(1<<PB3);
	 }
	 else if (get_RX_buffer()[0]=='Z' && get_RX_buffer()[1]==0)
	 {
	 serial_println_str("apagado led3");
	 PORTB &=  ~(1<<PB4);
         }
   }
}

void enviar2raspi1(){
_delay_ms(1500);
serial_println_str("1");     //para el segundo codigo de python se coloca solo serial_println_str("1,2,3,4");
_delay_ms(1500);
serial_println_str("2");
_delay_ms(1500);
serial_println_str("3");
_delay_ms(1500);
serial_println_str("0");
_delay_ms(1500);
}

void enviar2raspi2(){
_delay_ms(1500);
serial_println_str("1,2,3,4");     
}

void init_pins(){
DDRB |= ((1 << DDB2)); //asignar a puerto b5 como salida//pin 13 de arduino 
DDRB |= ((1 << DDB3)); //asignar a puerto b3 como salida//pin 11 de arduino 
DDRB |= ((1 << DDB4)); //asignar a puerto b2 como salida//pin 10 de arduino 
}

char* mensaje = "";
int main()
 { 
serial_begin();
init_pins();


   while (1)
     {

recibir_encender_led();

}
   return 0;
}
