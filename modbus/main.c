/*
 * main.c
 *
 *  Created on: 26 de jun de 2019
 *      Author: Tanaka
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "lib/avr_usart.h"
#include "modbus.h"
#include "DS1302.h"
#include "three_wire.h"


int main(){
	uint16_t data = 0;


	/* Inicializa hardware da USART */
	USART_Init(B9600);

	three_wire_init();

	sei();
	write_minutes(21);
	//write_24hours(0x16);

	while(1)
	{
	   //data = 55;
		data = get_seconds();

	   _delay_ms(250);
	   transmite_dado(data, 0x05);
	   data = get_minutes();
	   _delay_ms(250);


	   transmite_dado(data,0x06);
	   _delay_ms(3000);

	}


	return 0;
}
