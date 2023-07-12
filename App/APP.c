#include "stm32f10x.h"
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "APP.h"
#include "queue.h"
#include "gpio.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_flash.h"
#include "stm32f10x_usart.h"
#include "uart_frame_handle.h"

#define  STATUS_LED_ADDRESS    ((uint32_t)0x08001000)
#define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08008000)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x0800C000)
#define USART1_RxPin             GPIO_Pin_10
#define USART1_TxPin             GPIO_Pin_9


uint32_t EraseCounter = 0x00, Address = 0x00;
uint32_t Data = 0x3210ABCD;
uint32_t NbrOfPage = 0x00;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
/* sequence of flash */
//   FLASH_UnlockBank1();

//   /* Clear All pending flags */
//   FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

//  /* Define the number of page to be erased */
//   FLASH_ErasePage(STATUS_LED_ADDRESS);

//   FLASHStatus = FLASH_ProgramWord(STATUS_LED_ADDRESS, (uint32_t)0x01);


//   FLASH_LockBank1();



typedef void (*function) (void);
function jump_to_app;
uint32_t Jump_Address;

void UART0_callBackFuction(uint8_t ch);
static void ControlLed(bool PinState);



void RCC_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); // Enable the GPIOC clock
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); // Enable the GPIOA clock

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}


void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Configure the NVIC Preemption Priority Bits */  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

    /* Enable the USARTy Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}

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

void Erase_Multi_Sector(uint32_t Page_Start_Address,uint8_t Num_Of_Page)
{
    uint32_t i;
    for(i =Page_Start_Address; i <= (Page_Start_Address + Num_Of_Page*FLASH_PAGE_SIZE); i = i + FLASH_PAGE_SIZE )
    {
        FLASH_ErasePage(i);
    }
}

uint32_t Format_data4byte_ToWriteFlash(uint8_t* address)
{
    uint32_t retValue =0x00000000;
    retValue |= ((address[3]&((uint8_t)0xFF))<<24) | ((address[2]&((uint8_t)0xFF))<<16) | ((address[1]&((uint8_t)0xFF))<<8) | ((address[0]&((uint8_t)0xFF))<<0);
    return retValue;
}


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
    uint32_t index;
    bool stopProgram= false;
    uint8_t frameData[20] ={0};
    uint8_t frameSize;
    while(!stopProgram)
    {
        if(!queue_isEmpty())
        {
            popBuff = queue_pop();
            handleDataFrame(popBuff, &Output,ControlLed);
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

static void ControlLed(bool PinState)
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



