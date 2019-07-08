/*
 * main.c
 *
 *  Created on: 26 de jun de 2019
 *      Author: Tanaka
 */
#define  F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "avr_usart.h"
#include "modbus.h"
#include "DS1302.h"
#include "three_wire.h"


int main()
{
	uint16_t data;

	/* Inicializa hardware da USART */
	USART_Init(B9600);

	three_wire_init();
	pwm_init()

	sei();
	//write_minutes(0x04);
	//write_24hours(0x19);

	while(1)
	{
		data = get_minutes();
		data = converte_hex_dec(data);
		transmite_dado(data, 0x05);
		_delay_ms(250);
		
		data = get_24hours();
		data = converte_hex_dec(data);
		transmite_dado(data,0x06);
		_delay_ms(250);
	   
		data = le_dado(0x01);
		duty_cycle(data);
		_delay_ms(3000);
	}

	return 0;
}
