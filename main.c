#define F_CPU 8000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <avr/iom128.h>
#include <util/delay.h>
#include "lcd.h"


void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );


int main(){
    _delay_ms(500);
    _delay_ms(500);
    _delay_ms(500);
    _delay_ms(500);
    LCD_init();
    USART_Init ( MYUBRR );

    while(1){

        USART_Transmit(USART_Receive());
    }


    return 0;
}



void USART_Init( unsigned int ubrr )
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN)|(1<<TXEN);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS)|(3<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
LCD_data(data);
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE)) )
;
/* Put data into buffer, sends the data */
UDR0 = data;
}

unsigned char USART_Receive( void )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC)) )
;
/* Get and return received data from buffer */
return UDR0;
}
