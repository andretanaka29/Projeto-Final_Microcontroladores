/*
 * DS1302.h
 *
 * Created: 15/06/2019 20:22:24
 *  Author: mikae
 */ 


#ifndef DS1302_H_
#define DS1302_H_

// 24h setup
#define _24h

#ifndef _IO8
	#define _IO8 volatile uint8_t
#endif

/* Defindo estrutura de dados */
typedef struct
{
	_IO8	seconds;
	_IO8	minutes;
	_IO8	hours;
	_IO8	days;
	_IO8	months;
	_IO8	week_day;
	_IO8	years;
}time_data;

typedef struct  
{
	union
	{
		_IO8 MASK;
		struct
		{
			_IO8	TCS3:1; // bit 7	TCSn Trickle Charge select
			_IO8	TCS2:1; // bit 6
			_IO8	TCS1:1; // bit 5
			_IO8	TCS0:1; // bit 4
			_IO8	DS1:1; // bit 3		DSn Diode select
			_IO8	DS0:1; // bit 2
			_IO8	RS1:1; // bit 1		RSn Resistor select
			_IO8	RS0:1; // bit 0
			} BITS;
	} TRICKLE;
} CHARGE_CONF;

time_data *read_time(void);

void write_time(time_data* data);

uint8_t get_seconds(void);

uint8_t get_minutes(void);

uint8_t get_12hours(void);

uint8_t get_24hours(void);

uint8_t get_days(void);

uint8_t get_months(void);

uint8_t get_week_day(void);

uint8_t get_years(void);

void write_seconds(uint8_t data);

void write_minutes(uint8_t data);

void write_12hours(uint8_t data);

void write_24hours(uint8_t data);

void write_days(uint8_t data);

void write_months(uint8_t data);

void write_week_day(uint8_t data);

void write_years(uint8_t data);
#endif /* DS1302_H_ */