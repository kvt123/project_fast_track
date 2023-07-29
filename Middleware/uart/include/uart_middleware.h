#ifndef _UART_MIDDERWARE_H_
#define _UART_MIDDERWARE_H_

#include <stdint.h>
#include "uart_driver.h"

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/


void USART_Configuration(void);

void USART1_transmit_string(uint8_t *buffer, uint16_t length_buffer);


#endif /* _UART_MIDDERWARE_H_ */