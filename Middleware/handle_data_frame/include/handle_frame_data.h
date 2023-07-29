#ifndef _UART_FRAME_HANDLE_H_
#define _UART_FRAME_HANDLE_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_DATA_SIZE                    6
/*******************************************************************************
 * Typedef
 ******************************************************************************/

/* Return code by parsing function */
typedef enum {
    e_parseStatus_done = 0U,
    e_parseStatus_inprogress = 1U,
    e_parseStatus_error = 2U,
    e_parseStatus_undefined = 3U
} parse_status_t;


/* type of parameter public for output of parseData fuction */
typedef struct
{
    uint32_t Id_Byte;
    uint8_t data[MAX_DATA_SIZE];
    uint8_t dataLength;
} parse_data_line_struct_t;
////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
typedef enum
{
    ID_RECEIVED_SELECT_ON_OFF_MODE = 0x01u,
    ID_RECEIVED_SELECT_AUTO_MANUAL_MODE = 0x02u,
    ID_RECEIVED_SELECT_WIND_LEVEL_MODE = 0x03u,
    ID_RECEIVED_SELECT_READ_ALL_STATUS_MODE = 0x04u,
    ID_FEEDBACK_SELECT_ON_OFF_MODE = 0x81u,
    ID_FEEDBACK_SELECT_AUTO_MANUAL_MODE = 0x82u,
    ID_FEEDBACK_SELECT_WIND_LEVEL_MODE = 0x83u,
    ID_FEEDBACK_SELECT_READ_ALL_STATUS_MODE = 0x84u,
} ID_Byte;

/*******************************************************************************
 * API
 ******************************************************************************/
typedef void (*fp_gpio_callBackFuction)(bool);
/*!
 *@brief fuction parse each srec line
 *@param
 */
parse_status_t parseDataFrame(uint8_t pInput[],parse_data_line_struct_t *Output);
parse_status_t handleDataFrame(uint8_t pInput[],parse_data_line_struct_t *OutPutDataFeedBack,fp_gpio_callBackFuction GPIO_callBackFuction);
void CreateSendFeedBackFrame(parse_data_line_struct_t *OutPutDataFeedBack, uint8_t* frameData, uint8_t* frameSize);


#endif /* _UART_FRAME_HANDLE_H_ */
