/*
 * pwm.h
 *
 *  Created on: 4 de jul de 2019
 *      Author: Tanaka
 */

#ifndef PWM_H_
#define PWM_H_

#define TOP 200

/**
  * @brief  Inicialização do hardware de PWM.
  * @param	Nenhum.
  *
  * @retval Nenhum.
  */
void pwm_init();

/**
  * @brief  Ajusta duty-cycle do PWM.
  * @param	Valor do duty-cycle em %.
  *
  * @retval Nenhum.
  */
void duty_cycle(uint8_t ciclo);

#endif /* PWM_H_ */
