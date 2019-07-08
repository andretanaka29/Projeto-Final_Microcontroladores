/*
 * modbus.h
 *
 *  Created on: 26 de jun de 2019
 *      Author: Tanaka
 */

#ifndef MODBUS_H_
#define MODBUS_H_

#define SIZE_PKG 8

/**
  * @brief  Calcula o CRC.
  * @param	pacote de dados dados e tamanho
  *
  * @retval Valor do CRC.
  */
uint16_t CRC16_2(uint8_t *buf, int len);

/**
  * @brief  Transmite dado.
  * @param	dado a ser transmitido e endereço do sensor.
  *
  * @retval pacote de resposta.
  */
void transmite_dado(uint16_t dado, uint16_t sensor);

/**
  * @brief  Lê dado.
  * @param	endereço do dado a ser lido.
  *
  * @retval pacote de resposta.
  */
uint16_t le_dado(uint16_t adress);

/**
  * @brief  Manda pacote de dados pela UART.
  * @param	Pacote de dados e tamanho do pacote.
  *
  * @retval Nenhum.
  */
void send_pkg(uint8_t* tx_pkg, uint8_t size);

/**
  * @brief  Recepção de pacote de dados pela UART.
  * @param	Pacote de dados e tamanho do pacote.
  *
  * @retval Nenhum.
  */
void receive_pkg(uint8_t* rx_pkg, uint8_t size);

/**
  * @brief  Checa por mensagens de erro no pacote.
  * @param	Pacote de dados transmitido e Pacote de dados recebido.
  *
  * @retval Flag de erro.
  */
uint8_t check_error(uint8_t* tx_pkg, uint8_t* rx_pkg);

#endif /* MODBUS_H_ */
