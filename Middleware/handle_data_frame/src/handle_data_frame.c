#include <stdint.h>
#include <stdbool.h>
#include "handle_frame_data.h"

/*******************************************************************************
 * Global Variables
 ******************************************************************************/
static parse_status_t status = e_parseStatus_inprogress;
static fp_gpio_callBackFuction spf_gpio_callback;
/*******************************************************************************
 * static fuction
 ******************************************************************************/

/*******************************************************************************
 * code
 ******************************************************************************/



/* fuction parse each srec line */
parse_status_t parseDataFrame(uint8_t pInput[],parse_data_line_struct_t *Output)
{
    ID_Byte Id_Byte =  pInput[1];
    uint32_t DataLength = pInput[2];
    uint32_t dataIndex=0;
    Output->Id_Byte = 0;
    Output->dataLength = 0;
    status = e_parseStatus_inprogress;
    /* check invalid srec record */
    if(pInput[0]!= 0x02)
    {
        return e_parseStatus_error;
    }

    switch (Id_Byte)
    {
        case ID_RECEIVED_SELECT_ON_OFF_MODE:
            if(DataLength == 0x01)
            {
                Output->Id_Byte = ID_RECEIVED_SELECT_ON_OFF_MODE;
                Output->dataLength = 1;
            }
            else
            {
                Output->Id_Byte = ID_RECEIVED_SELECT_ON_OFF_MODE;
                Output->dataLength = DataLength;
                status = e_parseStatus_error;
            }
            break;
        case ID_RECEIVED_SELECT_AUTO_MANUAL_MODE:
            if(DataLength == 0x01)
            {
                Output->Id_Byte = ID_RECEIVED_SELECT_AUTO_MANUAL_MODE;
                Output->dataLength = 1;
            }
            else
            {
                Output->Id_Byte = ID_RECEIVED_SELECT_AUTO_MANUAL_MODE;
                Output->dataLength = DataLength;
                status = e_parseStatus_error;
            }
            break;
        case ID_RECEIVED_SELECT_WIND_LEVEL_MODE:
            if(DataLength == 0x01)
            {
                Output->Id_Byte = ID_RECEIVED_SELECT_WIND_LEVEL_MODE;
                Output->dataLength = 1;
            }
            else
            {
                Output->Id_Byte = ID_RECEIVED_SELECT_WIND_LEVEL_MODE;
                Output->dataLength = DataLength;
                status = e_parseStatus_error;
            }
            break;
        case ID_RECEIVED_SELECT_READ_ALL_STATUS_MODE:
            if(DataLength == 0x00)
            {
                Output->Id_Byte = ID_RECEIVED_SELECT_READ_ALL_STATUS_MODE;
                Output->dataLength = 0;
            }
            else
            {
                Output->Id_Byte = ID_RECEIVED_SELECT_READ_ALL_STATUS_MODE;
                Output->dataLength = DataLength;
                status = e_parseStatus_error;
            }
            break;
        default:
            status = e_parseStatus_error;
            break;
    }

    if(e_parseStatus_error != status)
    {
        /* handle to get data and check end of frame*/
        for (dataIndex = 0; dataIndex < Output->dataLength ; dataIndex++)
        {
            Output->data[dataIndex] = pInput[dataIndex+3];
        }
        /* check end of frame  = 0x03*/
        if(0x03 == pInput[3+Output->dataLength])
        {
            status = e_parseStatus_inprogress;
        }
        else
        {
            status = e_parseStatus_error;
        }

    }

    return status;
}


parse_status_t handleDataFrame(uint8_t pInput[],parse_data_line_struct_t *OutPutDataFeedBack,fp_gpio_callBackFuction GPIO_callBackFuction)
{
    parse_data_line_struct_t Output;
    parse_status_t parseStatus = parseDataFrame(pInput,&Output);
    switch (Output.Id_Byte)
    {
        case ID_RECEIVED_SELECT_ON_OFF_MODE:
        /* setup frame feed back*/
            OutPutDataFeedBack->Id_Byte = ID_FEEDBACK_SELECT_ON_OFF_MODE;
            OutPutDataFeedBack->dataLength = 0x01;
            if(e_parseStatus_error != parseStatus)
            {
                /* check data = 0 or =1*/
                if((0x00 == Output.data[0]) || (0x01 == Output.data[0]))
                {
                    /* control fan*/
                    switch (Output.data[0])
                    {
                    case 0x00:
                        /* code */
                        GPIO_callBackFuction(false);
                        break;
                     case 0x01:
                        /* code */
                        GPIO_callBackFuction(true);
                        break;
                    default:
                        break;
                    }

                    OutPutDataFeedBack->data[0] = 0x00;


                }
                else
                {
                    OutPutDataFeedBack->data[0] = 0x01;
                }
            }
            else
            {
                /* setup frame feed back*/
                OutPutDataFeedBack->data[0] = 0xFF;
            }
            break;
        case ID_RECEIVED_SELECT_AUTO_MANUAL_MODE:
            /* setup frame feed back*/
            OutPutDataFeedBack->Id_Byte = ID_FEEDBACK_SELECT_AUTO_MANUAL_MODE;
            OutPutDataFeedBack->dataLength = 0x01;
            if(e_parseStatus_error != parseStatus)
            {
                /* check data = 0 or =1*/
                if((0x00 == Output.data[0]) || (0x01 == Output.data[0]))
                {
                    /* control fan mode*/


                    OutPutDataFeedBack->data[0] = 0x00;
                    /* if fan off mode should return value data[0]=2*/
                    //if()

                }
                else
                {
                    OutPutDataFeedBack->data[0] = 0x01;
                }
            }
            else
            {
                OutPutDataFeedBack->data[0] = 0xFF;
            }
            break;

        case ID_RECEIVED_SELECT_WIND_LEVEL_MODE:
            /* setup frame feed back*/
            OutPutDataFeedBack->Id_Byte = ID_FEEDBACK_SELECT_WIND_LEVEL_MODE;
            OutPutDataFeedBack->dataLength = 0x01;
            if(e_parseStatus_error != parseStatus)
            {
                /* check data = 0 or =1*/
                if((0x00 == Output.data[0]) || (0x01 == Output.data[0]) || (0x02 == Output.data[0]))
                {
                    /* control fan mode*/


                    OutPutDataFeedBack->data[0] = 0x00;
                    /* if fan off mode should return value data[0]=2*/
                    //if()
                }
                else
                {
                    OutPutDataFeedBack->data[0] = 0x01;
                }
            }
            else
            {
                OutPutDataFeedBack->data[0] = 0xFF;
            }
            break;
        case ID_RECEIVED_SELECT_READ_ALL_STATUS_MODE:
            /* setup frame feed back*/
            OutPutDataFeedBack->Id_Byte = ID_FEEDBACK_SELECT_READ_ALL_STATUS_MODE;
          if(e_parseStatus_error != parseStatus)
            {
                if(0x00 == Output.dataLength)
                {
                    OutPutDataFeedBack->data[0] = 0x00;
                    OutPutDataFeedBack->dataLength = 0x05;
                    /* read all the state of fan and add info to data array */
                    
                }
            }
            else
            {
                OutPutDataFeedBack->dataLength = 0x01;
                OutPutDataFeedBack->data[0] = 0xFF;
            }
            break;
        default:
            status = e_parseStatus_error;
            break;
    }
    return status;
}

void CreateSendFeedBackFrame(parse_data_line_struct_t *OutPutDataFeedBack, uint8_t* frameData, uint8_t* frameSize)
{
    uint8_t Index =0;
    frameData[0] = 0x02;
    frameData[1] = OutPutDataFeedBack->Id_Byte;
    frameData[2] = OutPutDataFeedBack->dataLength;
    for(Index = 0; Index < OutPutDataFeedBack->dataLength; Index++)
    {
        frameData[3+Index] = OutPutDataFeedBack->data[Index];
    }
    frameData[3+OutPutDataFeedBack->dataLength] = 0x03;
    *frameSize = 4 + OutPutDataFeedBack->dataLength;
}
