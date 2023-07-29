#include <stdint.h>
#include "rcc_middleware.h"


void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Enable the GPIOC clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Enable the GPIOA clock

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}
