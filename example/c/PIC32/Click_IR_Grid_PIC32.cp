#line 1 "C:/Users/katarina.perendic/Desktop/IR Grid/example/c/PIC32/Click_IR_Grid_PIC32.c"
#line 1 "c:/users/katarina.perendic/desktop/ir grid/example/c/pic32/click_ir_grid_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;
typedef signed long long int64_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long uint64_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;
typedef signed long long int_least64_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;
typedef unsigned long long uint_least64_t;



typedef signed long int int_fast8_t;
typedef signed long int int_fast16_t;
typedef signed long int int_fast32_t;
typedef signed long long int_fast64_t;


typedef unsigned long int uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long long uint_fast64_t;


typedef signed long int intptr_t;
typedef unsigned long int uintptr_t;


typedef signed long long intmax_t;
typedef unsigned long long uintmax_t;
#line 1 "c:/users/katarina.perendic/desktop/ir grid/example/c/pic32/click_ir_grid_config.h"
#line 1 "c:/users/katarina.perendic/desktop/ir grid/example/c/pic32/click_ir_grid_types.h"
#line 17 "c:/users/katarina.perendic/desktop/ir grid/example/c/pic32/click_ir_grid_config.h"
const uint32_t _IRGRID_I2C_CFG[ 1 ] =
{
 100000
};
#line 1 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic32/include/stdint.h"
#line 57 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
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
#line 94 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
void irgrid_i2cDriverInit( const uint8_t*  gpioObj,  const uint8_t*  i2cObj, uint8_t slave_eeprom, uint8_t slave);
#line 101 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
void irgrid_gpioDriverInit( const uint8_t*  gpioObj);
#line 113 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
uint8_t irgrid_deviceInit(uint8_t refrate);
#line 123 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
uint8_t irgrid_measure();
#line 132 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
void irgrid_get_ir_raw(int16_t *buffer);
#line 141 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
void irgrid_get_temperature(float *buffer);
#line 150 "c:/users/katarina.perendic/desktop/ir grid/library/__irgrid_driver.h"
float irgrid_get_amb_temperature();
#line 42 "C:/Users/katarina.perendic/Desktop/IR Grid/example/c/PIC32/Click_IR_Grid_PIC32.c"
float ir_tmp[ 64 ];
char txt[ 64 ];

void systemInit()
{
 mikrobus_i2cInit( _MIKROBUS1, &_IRGRID_I2C_CFG[ 0 ] );
 mikrobus_logInit( _LOG_USBUART_A, 115200 );
 Delay_ms( 100 );
}

void applicationInit()
{
 irgrid_i2cDriverInit( ( const uint8_t* )&_MIKROBUS1_GPIO, ( const uint8_t* )&_MIKROBUS1_I2C, 0x50, 0x60);
 Delay_ms( 100 );
 irgrid_deviceInit( 16 );

 mikrobus_logWrite( "IR GRID INITIALIZED", _LOG_LINE);
 mikrobus_logWrite( "IR GRID TEMPERATURE MESUREMENT",_LOG_LINE);
}

void applicationTask()
{
 uint8_t i;
 uint8_t rc;
 uint8_t cc;

 if( 1 != irgrid_measure() )
 {
 irgrid_get_temperature( &ir_tmp[ 0 ] );
 }

 for (rc = 0; rc < 4; rc++)
 {
 for (cc = 0; cc < 16; cc++)
 {
 i = (cc * 4) + rc;

 FloatToStr( ir_tmp[ i ], txt );
 Ltrim( txt );
 txt[ 6 ] = 0;
 mikrobus_logWrite( txt, _LOG_TEXT );
 mikrobus_logWrite( "\t", _LOG_TEXT );
 }
 mikrobus_logWrite( " " ,_LOG_LINE );
 }
 mikrobus_logWrite( " " ,_LOG_LINE );
 mikrobus_logWrite( " " ,_LOG_LINE );
 mikrobus_logWrite( " " ,_LOG_LINE );
 Delay_ms(500);
}

void main()
{
 systemInit();
 applicationInit();

 while (1)
 {
 applicationTask();
 }
}
