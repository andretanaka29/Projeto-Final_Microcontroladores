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

#include "bits.h"
#include "avr_gpio.h"
#include "avr_timer.h"

int main(void)
{
	FILE *debug = get_usart_stream();
	
	USART_Init(B9600);
	
	three_wire_init();
	
	sei();
	uint8_t h, m, s;
	write_24hours(0x08);
	write_minutes(0x33);
    while (1) 
    {
		h = get_24hours();
		_delay_ms(100);
		m = get_minutes();
		_delay_ms(100);
		s = get_seconds();
		_delay_ms(100);
		fprintf(debug, "hours: %0X, minutes: %0X, seconds: %0X\r", h, m, s);
		
		_delay_ms(500);
    }
	
	return 0;
}

