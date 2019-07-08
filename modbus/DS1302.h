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

/**
  * @brief  Requesita os segundos ao DS1302.
  * @param	Nenhum.
  *
  * @retval Valor dos segundos.
  */
uint8_t get_seconds(void);

/**
  * @brief  Requesita valor dos minutos ao DS1302.
  * @param	Nenhum.
  *
  * @retval Valor dos minutos.
  */
uint8_t get_minutes(void);

/**
  * @brief  Requesita valor das horas no padrão 12h ao DS1302.
  * @param	Nenhum.
  *
  * @retval Valor das horas de 1-12.
  */
uint8_t get_12hours(void);

/**
  * @brief  Requesita valor das horas padrão 24h ao DS1302.
  * @param	Nenhum.
  *
  * @retval Valor das horas 0-23.
  */
uint8_t get_24hours(void);

/**
  * @brief  Requesita o dia ao DS1302.
  * @param	Nenhum.
  *
  * @retval Dia.
  */
uint8_t get_days(void);

/**
  * @brief  Requesita o mês ao DS1302.
  * @param	Nenhum.
  *
  * @retval Mês.
  */
uint8_t get_months(void);

/**
  * @brief  Requesita o dia da semana ao DS1302.
  * @param	Nenhum.
  *
  * @retval Dia da semana valor de 1-7.
  */
uint8_t get_week_day(void);

/**
  * @brief  Requesita o ano ao DS1302.
  * @param	Nenhum.
  *
  * @retval Ano.
  */
uint8_t get_years(void);

/**
  * @brief  Escreve os segundos no DS1302.
  * @param	Valor dos segundos.
  *
  * @retval Nenhum.
  */
void write_seconds(uint8_t data);

/**
  * @brief  Escreve os minutos no DS1302.
  * @param	Valor dos minutos.
  *
  * @retval Nenhum.
  */
void write_minutes(uint8_t data);

/**
  * @brief  Escreve as horas no DS1302.
  * @param	Valor das horas padrão 12h.
  *
  * @retval Nenhum.
  */
void write_12hours(uint8_t data);

/**
  * @brief  Escreve as horas no DS1302.
  * @param	Valor das horas padrão 24h.
  *
  * @retval Nenhum.
  */
void write_24hours(uint8_t data);

/**
  * @brief  Escreve o dia no DS1302.
  * @param	Dia.
  *
  * @retval Nenhum.
  */
void write_days(uint8_t data);

/**
  * @brief  Escreve o mês no DS1302.
  * @param	Mês.
  *
  * @retval Nenhum.
  */
void write_months(uint8_t data);

/**
  * @brief  Escreve o dia da semana no DS1302.
  * @param	Dia da semana, valor de 1-7.
  *
  * @retval Nenhum.
  */
void write_week_day(uint8_t data);

/**
  * @brief  Escreve o ano no DS1302.
  * @param	Ano.
  *
  * @retval Nenhum.
  */
void write_years(uint8_t data);

#endif /* DS1302_H_ */