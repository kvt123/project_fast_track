#ifndef _FLASH_MIDDERWARE_H_
#define _FLASH_MIDDERWARE_H_

#include <stdint.h>
#include "flash_driver.h"

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/


void Flash_Init(void);
void Erase_Multi_Sector(uint32_t Page_Start_Address,uint8_t Num_Of_Page);
uint32_t Format_data4byte_ToWriteFlash(uint8_t* address);

#endif /* _FLASH_MIDDERWARE_H_ */