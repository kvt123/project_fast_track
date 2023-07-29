
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "APP.h"
#include "uart_middleware.h"
#include "rcc_middleware.h"
#include "queue_middleware.h"
#include "misc_middleware.h"
#include "gpio_middleware.h"
#include "handle_frame_data.h"
#include "flash_middleware.h"


#define  STATUS_LED_ADDRESS    ((uint32_t)0x08001000)
#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08008000)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x0800C000)



//typedef void (*function) (void);
//function jump_to_app;
//uint32_t Jump_Address;

void USART1_callBackFuction(uint8_t ch);




/* function init button,uart0, queue */
void app_init()
{

    RCC_Configuration();

    /* NVIC configuration */
  NVIC_Configuration();
  GPIO_Configuration();

  USART_Configuration();

  HAL_GPIO_Write_Pin(GPIOC, GPIO_Pin_13, Bit_SET);
    /*initial queue*/
    queue_init();
    FLASH_UnlockBank1();

    /* Clear All pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
}

/*function jump to Boot */
void StartProgram(void)
{
    parse_status_t status;
    parse_data_line_struct_t Output;
    uint8_t *popBuff;
    bool stopProgram= false;
    uint8_t frameData[20] ={0};
    uint8_t frameSize;
    while(!stopProgram)
    {
        if(!queue_isEmpty())
        {
            popBuff = queue_pop();
            handleDataFrame(popBuff, &Output,Control_Led);
            CreateSendFeedBackFrame(&Output, frameData, &frameSize);
            queue_get();
            USART1_transmit_string(frameData,frameSize);
        }
    }
    
}



void USART1_callBackFuction(uint8_t ch)
{
    if( 0x03 == ch)
    {
        queue_push_data(ch);
        queue_put_newLine();
    }
    else
    {
        queue_push_data(ch);
    }
}





