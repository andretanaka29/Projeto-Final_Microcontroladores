/*
 * three_wire.c
 *
 * Created: 16/06/2019 14:13:10
 *  Author: Mikael Ferraz Aldebrand
 */

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lib/bits.h"
#include "lib/avr_gpio.h"
#include "lib/avr_timer.h"
#include "three_wire.h"

#ifdef MSB
	volatile uint8_t rise = 8, fall=8;
#endif

#ifdef LSB
	volatile uint8_t rise = 0, fall=0;
#endif
	

void three_wire_init(void)
{
	TIMER_0->TCCRB = SET(CS01); // Presc. 8
	THREE_WIRE_CONTROL->DDR |= SET(SCLK) | SET(CE);
}

void send_data(uint8_t data)
{
	#ifdef MSB
		rise = 8;
		do 
		{
			if(TST_BIT(data,rise))
				SET_BIT(THREE_WIRE_CONTROL->PORT,DATA);
			else
				CLR_BIT(THREE_WIRE_CONTROL->PORT,DATA);
		}while(rise);
	#endif
	
	#ifdef LSB
		rise = 0;
		do
		{
			if(TST_BIT(data,rise))
				SET_BIT(THREE_WIRE_CONTROL->PORT,DATA);
			else
				CLR_BIT(THREE_WIRE_CONTROL->PORT,DATA);
		}while(rise < 8);
	#endif
}

uint8_t get_data(uint8_t adress)
{
	uint8_t data = {0};
		
	SET_BIT(THREE_WIRE_CONTROL->DDR,DATA);
	SET_BIT(THREE_WIRE_CONTROL->PORT,CE); // Reset Disable
	
	TIMER_IRQS->TC0.BITS.TOIE=1; // Overflow interruption enable
	
	send_data(adress);
	
	CLR_BIT(THREE_WIRE_CONTROL->PORT,DATA); // Puts to zero the pin Data
	CLR_BIT(THREE_WIRE_CONTROL->DDR,DATA); // The data pin is set to receive
	
	#ifdef MSB
		fall = 0;
		do 
		{
			if(TST_BIT(THREE_WIRE_CONTROL->PIN, DATA))
				SET_BIT(data,fall);
			else
				CLR_BIT(data,fall);
		}while(fall < 8);
	#endif
	
	#ifdef LSB
		fall = 0;
		do
		{
			if(TST_BIT(THREE_WIRE_CONTROL->PIN, DATA))
				SET_BIT(data,fall);
			else
				CLR_BIT(data,fall);
		} while(fall < 7);
	#endif
	
	CLR_BIT(THREE_WIRE_CONTROL->PORT,CE); // Reset Enable
	
	TIMER_IRQS->TC0.BITS.TOIE=0; // Overflow interruption disable
	
	return data;
}

void write_data(uint8_t adress, uint8_t data)
{
	SET_BIT(THREE_WIRE_CONTROL->DDR,DATA);
	SET_BIT(THREE_WIRE_CONTROL->PORT,CE); // Reset Disable
	
	TIMER_IRQS->TC0.BITS.TOIE=1; // Overflow interruption enable
	
	send_data(adress);
	send_data(data);
	
	CLR_BIT(THREE_WIRE_CONTROL->PORT,CE); // Reset enable
	
	TIMER_IRQS->TC0.BITS.TOIE=0; // Overflow interruption disable
}

ISR(TIMER0_OVF_vect)
{
	CPL_BIT(THREE_WIRE_CONTROL->PORT,SCLK);
	if(!TST_BIT(THREE_WIRE_CONTROL->PORT,SCLK))
	{
		#ifdef MSB
			rise--;
			if(!rise)
				rise = 8;
		#endif
		
		#ifdef LSB
			rise++;
			rise = rise & 0xFF;
		#endif
	}
	else
	{
		#ifdef MSB
			fall--;
			if(!fall)
				fall = 7;
		#endif
		
		#ifdef LSB
			fall++;
			fall = fall & 0xFF;
		#endif
	}
}
