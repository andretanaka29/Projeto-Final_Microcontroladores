/*
 * three_wire.c
 *
 * Created: 16/06/2019 14:13:10
 *  Author: mikae
 */
#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "bits.h"
#include "avr_gpio.h"
#include "avr_timer.h"
#include "three_wire.h"

volatile uint8_t n = 0;

void three_wire_init(void)
{
	TIMER_0->TCCRA = SET(COM0A0) | SET(WGM01); // Toggle OC0A on compare match, TOP on OCRA
	TIMER_0->TCCRB = SET(CS01); // Presc. 8
	TIMER_0->OCRA = 200; // Freq. 10kHz
	
	TIMER_IRQS->TC0.BITS.OCIEA = 1; // Interruption on compare match enable
	
	THREE_WIRE_CONTROL->DDR |= SET(SCLK) | SET(CE);
}

void send_data(uint8_t data)
{
	uint8_t i;
	
	SET_BIT(THREE_WIRE_CONTROL->DDR,DATA);
	SET_BIT(THREE_WIRE_CONTROL->PORT,CE);
	
	#ifdef MSB
		i = 7;
		do 
		{
			if(TST_BIT(data,i))
				SET_BIT(THREE_WIRE_CONTROL->PORT,DATA);
			else
				CLR_BIT(THREE_WIRE_CONTROL->PORT,DATA);
			i++;
		} while (i);
	#endif
	
	#ifdef LSB
		i = 0;
		while(i < 8)
		{
			if(TST_BIT(data,i))
				SET_BIT(THREE_WIRE_CONTROL->PORT,DATA);
			else
				CLR_BIT(THREE_WIRE_CONTROL->PORT,DATA);
			i++;
		}
	#endif
	
	CLR_BIT(THREE_WIRE_CONTROL->PORT,CE); // Reset enable
}

uint8_t get_data(uint8_t adress)
{
	uint8_t i, data = {0};
	
	send_data(adress);
	CLR_BIT(THREE_WIRE_CONTROL->DDR,DATA); // The data pin is set to receive
	SET_BIT(THREE_WIRE_CONTROL->PORT,CE); 
	SET_BIT(THREE_WIRE_CONTROL->PORT,DATA); // Reset disable, Data pin in pull-up
	
	#ifdef MSB
		i=7;
		do 
		{
			if(TST_BIT(THREE_WIRE_CONTROL->PIN, DATA))
				SET_BIT(data,i);
			else
				CLR_BIT(data,i);
			i--;
		} while (i);
	#endif
	
	#ifdef LSB
		i=0;
		while(i<8)
		{
			if(TST_BIT(THREE_WIRE_CONTROL->PIN, DATA))
				SET_BIT(data,i);
			else
				CLR_BIT(data,i);
			i--;
		}
	#endif
	
	CLR_BIT(THREE_WIRE_CONTROL->PORT,CE); // Reset enable
	
	return data;
}

void write_data(uint8_t adress, uint8_t data)
{
	send_data(adress);
	send_data(data);
}

ISR(TIMER0_COMPA_vect)
{
	
}