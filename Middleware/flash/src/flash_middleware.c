#include <stdint.h>
#include <stdbool.h>
#include "flash_middleware.h"





#define  STATUS_LED_ADDRESS    ((uint32_t)0x08001000)
#define FLASH_PAGE_SIZE    ((uint16_t)0x400)

volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;

typedef void (*function) (void);
function jump_to_app;
uint32_t Jump_Address;

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

void Flash_Init(void)
{
    /* unlock bank 1*/
    FLASH_UnlockBank1();

    /* Clear All pending flags */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

}
