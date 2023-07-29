
#ifndef _GPIO_MIDDERWARE_H_
#define _GPIO_MIDDERWARE_H_

#include <stdint.h>
#include "gpio_driver.h"

/*******************************************************************************
* Definitions
******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/


void GPIO_Configuration(void);

void ControlLed(bool PinState);

#endif /* _GPIO_MIDDERWARE_H_ */
