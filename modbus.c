/*
 * modbus.c
 *
 *  Created on: 26 de jun de 2019
 *      Author: Tanaka
 */
#define  F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include "avr_usart.h"
#include "modbus.h"

uint16_t CRC16_2(uint8_t *buf, int len)
{
  uint32_t crc = 0xFFFF;
  int i;

  for (i = 0; i < len; i++)
  {
    crc ^= (uint16_t)buf[i];          // XOR byte into least sig. byte of crc

    for (int i = 8; i != 0; i--) {    // Loop over each bit
      if ((crc & 0x0001) != 0) {      // If the LSB is set
        crc >>= 1;                    // Shift right and XOR 0xA001
        crc ^= 0xA001;
      }
      else                            // Else LSB is not set
        crc >>= 1;                    // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  return crc;
}

void transmite_dado(uint16_t dado, uint16_t sensor)
{
	uint8_t pkg[SIZE_PKG], rx_pkg[SIZE_PKG];
	uint16_t crc;

	pkg[0] = 0x15;
	pkg[1] = 0x01;
	pkg[2] = sensor>>8;
	pkg[3] = sensor & 0xFF;
	pkg[4] = dado>>8;
	pkg[5] = dado & 0xFF;

	crc = CRC16_2(pkg,6);

	pkg[6] = crc >> 8;
	pkg[7] = crc & 0xff;

	do
	{
		send_pkg(pkg, SIZE_PKG);
		receive_pkg(rx_pkg, SIZE_PKG);
	} while(!check_error(pkg,rx_pkg));
}

uint16_t le_dado(uint16_t adress)
{
	uint8_t pkg[SIZE_PKG], rx_pkg[SIZE_PKG];
	uint16_t crc;
	
	pkg[0] = 0x15;
	pkg[1] = 0x02;
	pkg[2] = (adress >> 8);
	pkg[3] = (adress & 0xFF);
	pkg[4] = 0x00;
	pkg[5] = 0x01;

	crc = CRC16_2(pkg,6);

	pkg[6] = crc >> 8;
	pkg[7] = crc & 0xff;
	
	do 
	{
		send_pkg(pkg, SIZE_PKG);
		receive_pkg(rx_pkg, SIZE_PKG);
	} while(!check_error(pkg,rx_pkg));

	return rx_pkg[5];
}

void send_pkg(uint8_t* tx_pkg, uint8_t size)
{
	uint8_t i;
	
	for(i=0; i < size; i++)
		USART_tx(tx_pkg[i]);
}

void receive_pkg(uint8_t* rx_pkg, uint8_t size)
{
	uint8_t i;
	
	for(i=0; i < size; i++)
		rx_pkg[i] = USART_rx();
}

uint8_t check_error(uint8_t* tx_pkg, uint8_t* rx_pkg)
{
	uint8_t f;
	
	if(tx_pkg[2]==rx_pkg[2]) // OK
		f = 0;
	else if(rx_pkg[2]==0xFF) // invalid CRC
		f = 1;
	else if(rx_pkg[2]==0xFE) // invalid Register
		f = 2;
	else
		f = 3;	// Unknown behavior 
		
	return f;
}