#include <stdint.h>
#include <stdbool.h>
#include "gpio_middleware.h"



#define USART1_RxPin             GPIO_Pin_10
#define USART1_TxPin             GPIO_Pin_9

void GPIO_Configuration(void)
{

    GPIO_InitTypeDef InitStruct;

    /* init pin C13 for led blue*/
    InitStruct.GPIO_Pin  = GPIO_Pin_13;
    InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;

     HAL_GPIO_Init(GPIOC, &InitStruct);

      /* init button pin A2 for bootloader program*/
    InitStruct.GPIO_Pin  = GPIO_Pin_2;
    InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;

     HAL_GPIO_Init(GPIOA, &InitStruct);


     /* configuration USART1 RX as input*/
    InitStruct.GPIO_Pin  = USART1_RxPin;
    InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    HAL_GPIO_Init(GPIOA, &InitStruct);

    /* configuration USART1 TX as input*/
    InitStruct.GPIO_Pin  = USART1_TxPin;
    InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;   ///// transmit may be wrong
    HAL_GPIO_Init(GPIOA, &InitStruct);

}

void ControlLed(bool PinState)
{
    if(true == PinState)
    {
        HAL_GPIO_Write_Pin(GPIOC, GPIO_Pin_13,Bit_RESET);
    }
    else
    {
        HAL_GPIO_Write_Pin(GPIOC, GPIO_Pin_13,Bit_SET);
    }
}
