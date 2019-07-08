/*
 * three_wire.h
 *
 * Created: 16/06/2019 14:13:35
 *  Author: mikae
 */ 


#ifndef THREE_WIRE_H_
#define THREE_WIRE_H_

#define LSB

#define THREE_WIRE_CONTROL GPIO_D

#define CE 	PD5 	// Enable Read/Write
#define SCLK PD6	// Clock
#define DATA PD7	// Data pin

/**
  * @brief  Inicializa hardware usado no protocolo de três fios.
  * @param	Nenhum.
  *
  * @retval Nenhum.
  */
void three_wire_init(void);

/**
  * @brief  Transmite dado.
  * @param	dado a ser transmitido.
  *
  * @retval Nenhum.
  */
void send_data(uint8_t data);

/**
  * @brief  Lê dado.
  * @param	Comando a ser mandado.
  *
  * @retval Dado lido.
  */
uint8_t get_data(uint8_t adress);

/**
  * @brief  Escreve dado.
  * @param	Endereço e dado a ser transmitido.
  *
  * @retval Nenhum.
  */
void write_data(uint8_t adress, uint8_t data);

#endif /* THREE_WIRE_H_ */