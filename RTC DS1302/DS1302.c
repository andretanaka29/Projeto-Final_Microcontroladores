/*
 * DS1302.c
 *
 * Created: 15/06/2019 20:22:09
 *  Author: mikae
 */ 

#include <avr/io.h>
#include <stdio.h>

#include "bits.h"
#include "avr_gpio.h"
#include "avr_usart.h"

#include "DS1302.h"
#include "three_wire.h"


const uint8_t registers_read[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8B, 0x8D};
const uint8_t registers_write[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8A, 0x8C};

time_data *read_time(void)
{
	time_data *read = {0};
	
	read->seconds = get_seconds();
	read->minutes = get_minutes();
	#ifdef _24h
		read->hours = get_24hours();
	#else
		read->hours = get_12hours();
	#endif
	read->days = get_days();
	read->years = get_years();
	
	return read;
}

void write_time(time_data* data)
{
	write_seconds(data->seconds);
	write_minutes(data->minutes);
	#ifdef _24h
		write_24hours(data->hours);
	#else
		write_12hours(data->hours);
	#endif
	write_days(data->days);
	write_years(data->years);
}

uint8_t get_seconds(void)
{
	return get_data(registers_read[0]);
}

uint8_t get_minutes(void)
{
	return get_data(registers_read[1]);
}

uint8_t get_12hours(void)
{
	return get_data(registers_read[2]);
}

uint8_t get_24hours(void)
{
	return get_data(registers_read[2]);
}

uint8_t get_days(void)
{
	return get_data(registers_read[3]);
}

uint8_t get_months(void)
{
	return get_data(registers_read[4]);
}

uint8_t get_week_day(void)
{
	return get_data(registers_read[5]);
}

uint8_t get_years(void)
{
	return get_data(registers_read[6]);
}

void write_seconds(uint8_t data)
{
	write_data(registers_write[0], data);
}

void write_minutes(uint8_t data)
{
	write_data(registers_write[1], data);
}

void write_24hours(uint8_t data)
{
	write_data(registers_write[2], data);
}

void write_12hours(uint8_t data)
{
	write_data(registers_write[2], data);
}

void write_days(uint8_t data)
{
	write_data(registers_write[3], data);
}

void write_months(uint8_t data)
{
	write_data(registers_write[4], data);
}

void write_week_day(uint8_t data)
{
	write_data(registers_write[5], data);
}

void write_years(uint8_t data)
{
	write_data(registers_write[6], data);
}