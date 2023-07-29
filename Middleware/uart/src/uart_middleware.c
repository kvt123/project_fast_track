#include <stdint.h>
#include "uart_middleware.h"


void USART_Configuration(void)
{
    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USART1 */
  USART_Init(USART1, &USART_InitStructure);
  /* Enable USART1 Receive and Transmit interrupts */
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART1, USART_IT_TXE, DISABLE);

/* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);

}

void USART1_transmit_string(uint8_t *buffer, uint16_t length_buffer)
{
    uint16_t i=0;
    for(i =0; i< length_buffer; i++)
    {
//        if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
 //       {
        if(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == SET)
        {
            USART_SendData(USART1, buffer[i]);
            while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET);
        }
    
 //       }
    }
}