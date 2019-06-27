/*
 * RTC DS1302.c
 *
 * Created: 15/06/2019 20:21:20
 * Author : mikae
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "DS1302.h"
#include "avr_usart.h"
#include "three_wire.h"

int main(void)
{
	FILE *debug = get_usart_stream();
	
	USART_Init(B9600);
	
	three_wire_init();
	
	sei();

    while (1) 
    {
		fprintf(debug, "day: %0X\r", get_days());
		
		_delay_ms(500);
    }
	
	return 0;
}

