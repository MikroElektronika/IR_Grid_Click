/*
    __irgrid_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __irgrid_driver.h
@brief    IR_Grid Driver
@mainpage IR_Grid Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   IRGRID
@brief      IR_Grid Click Driver
@{

| Global Library Prefix | **IRGRID** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **jul 2018.**      |
| Developer             | **MikroE Team**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _IRGRID_H_
#define _IRGRID_H_

/** 
 * @macro T_IRGRID_P
 * @brief Driver Abstract type 
 */
#define T_IRGRID_P    const uint8_t*

/** @defgroup IRGRID_COMPILE Compilation Config */              /** @{ */

//  #define   __IRGRID_DRV_SPI__                            /**<     @macro __IRGRID_DRV_SPI__  @brief SPI driver selector */
   #define   __IRGRID_DRV_I2C__                            /**<     @macro __IRGRID_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __IRGRID_DRV_UART__                           /**<     @macro __IRGRID_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup IRGRID_VAR Variables */                           /** @{ */

extern const uint8_t _IRGRID_CAL_ACOMMON_L;
extern const uint8_t _IRGRID_CAL_ACOMMON_H;
extern const uint8_t _IRGRID_CAL_ACP_L;
extern const uint8_t _IRGRID_CAL_ACP_H;
extern const uint8_t _IRGRID_CAL_BCP;
extern const uint8_t _IRGRID_CAL_ALPHA_CP_L;
extern const uint8_t _IRGRID_CAL_ALPHA_CP_H;
extern const uint8_t _IRGRID_CAL_TGC;
extern const uint8_t _IRGRID_CAL_AI_SCALE;
extern const uint8_t _IRGRID_CAL_BI_SCALE;
extern const uint8_t _IRGRID_VTH_L;
extern const uint8_t _IRGRID_VTH_H;
extern const uint8_t _IRGRID_KT1_L;
extern const uint8_t _IRGRID_KT1_H;
extern const uint8_t _IRGRID_KT2_L;
extern const uint8_t _IRGRID_KT2_H;
extern const uint8_t _IRGRID_KT_SCALE;
extern const uint8_t _IRGRID_CAL_A0_L;
extern const uint8_t _IRGRID_CAL_A0_H;
extern const uint8_t _IRGRID_CAL_A0_SCALE;
extern const uint8_t _IRGRID_CAL_DELTA_A_SCALE;
extern const uint8_t _IRGRID_CAL_EMIS_L;
extern const uint8_t _IRGRID_CAL_EMIS_H;
extern const uint8_t _IRGRID_OSC_TRIM_VALUE;

                                                                       /** @} */

#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup IRGRID_INIT Driver Initialization */              /** @{ */

#ifdef   __IRGRID_DRV_SPI__
void irgrid_spiDriverInit(T_IRGRID_P gpioObj, T_IRGRID_P spiObj);
#endif
#ifdef   __IRGRID_DRV_I2C__
void irgrid_i2cDriverInit(T_IRGRID_P gpioObj, T_IRGRID_P i2cObj, uint8_t slave_eeprom, uint8_t slave);
#endif
#ifdef   __IRGRID_DRV_UART__
void irgrid_uartDriverInit(T_IRGRID_P gpioObj, T_IRGRID_P uartObj);
#endif

// GPIO Only Drivers - remove in other cases
void irgrid_gpioDriverInit(T_IRGRID_P gpioObj);
                                                                       /** @} */
/** @defgroup IRGRID_FUNC Driver Functions */                   /** @{ */

/**
 * @brief Device Initialization
 *
 * @param[in] refrate - Refresh Rate
 * @retval 0 - OK
 *
 * Initializes device, reads eeprom memory and places it inside internal buffers.
 */
uint8_t irgrid_deviceInit(uint8_t refrate);

/**
 * @brief Measurement
 *
 * @retval 0 - OK
 *
 * Measures temperature and places it inside internal buffers. This function is needed to be 
 * called prior to ```irgrid_get_ir_raw``` or ```irgrid_get_temperature```.
 */
uint8_t irgrid_measure();

/**
 * @brief Read Raw Temperature buffer
 *
 * @param[out] - buffer 
 *
 * Populates provided buffer with raw measurements. Buffer must have at least 64 members.
 */
void irgrid_get_ir_raw(int16_t *buffer);

/**
 * @brief Read Calculated Temperature buffer
 *
 * @param[out] - buffer 
 *
 * Populates provided buffer with calculated temperatures. Buffer must have at least 64 members.
 */
void irgrid_get_temperature(float *buffer);

/**
 * @brief Read Ambient Temperature
 *
 * @retval - Ambient temperature
 *
 * Read Ambient temperautre.
 */
float irgrid_get_amb_temperature();


                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_IR_Grid_STM.c
    @example Click_IR_Grid_TIVA.c
    @example Click_IR_Grid_CEC.c
    @example Click_IR_Grid_KINETIS.c
    @example Click_IR_Grid_MSP.c
    @example Click_IR_Grid_PIC.c
    @example Click_IR_Grid_PIC32.c
    @example Click_IR_Grid_DSPIC.c
    @example Click_IR_Grid_AVR.c
    @example Click_IR_Grid_FT90x.c
    @example Click_IR_Grid_STM.mbas
    @example Click_IR_Grid_TIVA.mbas
    @example Click_IR_Grid_CEC.mbas
    @example Click_IR_Grid_KINETIS.mbas
    @example Click_IR_Grid_MSP.mbas
    @example Click_IR_Grid_PIC.mbas
    @example Click_IR_Grid_PIC32.mbas
    @example Click_IR_Grid_DSPIC.mbas
    @example Click_IR_Grid_AVR.mbas
    @example Click_IR_Grid_FT90x.mbas
    @example Click_IR_Grid_STM.mpas
    @example Click_IR_Grid_TIVA.mpas
    @example Click_IR_Grid_CEC.mpas
    @example Click_IR_Grid_KINETIS.mpas
    @example Click_IR_Grid_MSP.mpas
    @example Click_IR_Grid_PIC.mpas
    @example Click_IR_Grid_PIC32.mpas
    @example Click_IR_Grid_DSPIC.mpas
    @example Click_IR_Grid_AVR.mpas
    @example Click_IR_Grid_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __irgrid_driver.h

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */