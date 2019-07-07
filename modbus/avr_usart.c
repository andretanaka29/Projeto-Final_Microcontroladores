/*
 * avr_usart.c
 *
 *  Created on: Mar 27, 2018
 *      Author: Renan Augusto Starke
 *      Instituto Federal de Santa Catarina
 */

#include <stdio.h>
#include <avr/interrupt.h>
#include "avr_usart.h"
#include "bits.h"

volatile uint8_t i=0, n=0, j=0, k=0, receive[SIZE_BUFFER], buffer[SIZE_BUFFER];
static int usart_putchar(char c, FILE *fp);

/* Stream init for printf  */
FILE usart_str = FDEV_SETUP_STREAM(usart_putchar, NULL, _FDEV_SETUP_WRITE);

/* Return stream pointer  */
FILE * get_usart_stream(){
	return &usart_str;
}

void USART_Init(uint16_t bauds){

	USART_0->UBRR_H = (uint8_t) (bauds >> 8);
	USART_0->UBRR_L = bauds;

	/* Disable double speed  */
	USART_0->UCSR_A = 0;
	
	/* Enable TX and RX */ // Data empty and RX interruption enable
	USART_0->UCSR_B = SET(RXEN0) | SET(TXEN0) | SET(UDRIE0) | SET(RXCIE0);
	/* Asynchronous mode:
	 * - 8 data bits
	 * - 1 stop bit
	 * - no parity 	 */
	USART_0->UCSR_C = SET(UCSZ01) | SET(UCSZ00);
}

void USART_tx(uint8_t data)
{
	buffer[i++] = data;
	
	if(i >= SIZE_BUFFER)
		i=0;
}

uint8_t USART_rx(void)
{	
	if(k > j)
		k = j;
	
	receive[k-1] = 0;	// Clean the buffer8
	
	return receive[k++];
}

static int usart_putchar(char c, FILE *fp)
{
	USART_tx(c);

	return 0;
}

ISR(USART_RX_vect)
{
	if(j >= SIZE_BUFFER)
		j = 0;
	
	receive[j++] = USART_0->UDR_;
}
/*
ISR(USART_TX_vect)
{
	
}
*/

ISR(USART_UDRE_vect)
{
	USART_0->UDR_ = buffer[n];
	buffer[n++] = 0;
	if(n >= SIZE_BUFFER)
		n = 0;
}