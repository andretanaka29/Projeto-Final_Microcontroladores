/*
 * pwm.c
 *
 *  Created on: 4 de jul de 2019
 *      Author: Tanaka
 */

#include <avr/io.h>
#include <util/delay.h>

#include "lib/bits.h"
#include "lib/avr_timer.h"
#include "lib/avr_gpio.h"
#include "pwm.h"

void pwm_init()
{
	/* PD3: pino OC2B como saída */
	GPIO_D->DDR |= SET(PD3);

	/* Table 15-6.  Compare Output Mode, Fast PWM Mode */
	/* COM0B1   COM0B0  Desc:
	    0       0       Normal port operation, OC0B disconnected.
	    0       1       Reserved
	    1       0       Clear OC2B on Compare Match, set OC2B at BOTTOM (non-inverting mode)
	    1       1       Set OC2B on Compare Match, clear OC2B at BOTTOM (inverting mode).*/

	/* WGM02, WGM01 WGM00 setados: modo PWM rápido com TOP em OCRA */
	TIMER_2->TCCRA = SET(WGM21) | SET(WGM20) | SET(COM2B1);
	TIMER_2->TCCRB = SET(WGM22) | SET(CS21);

	/* OCRA define frequência do PWM */
	TIMER_2->OCRA = TOP;
}

void duty_cycle(uint8_t ciclo)
{
	if (ciclo <= 100)
	{
		TIMER_2->OCRB = (TOP*ciclo)/100;
	}
	else
	{
		TIMER_2->OCRB = TOP;
	}
}
