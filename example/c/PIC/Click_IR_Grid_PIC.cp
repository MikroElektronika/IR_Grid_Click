#line 1 "C:/Users/katarina.perendic/Desktop/IR Grid/example/c/PIC/Click_IR_Grid_PIC.c"
#line 1 "c:/users/katarina.perendic/desktop/ir grid/example/c/pic/click_ir_grid_types.h"
#line 1 "c:/users/public/documents/mikroelektronika/mikroc pro for pic/include/stdint.h"




typedef signed char int8_t;
typedef signed int int16_t;
typedef signed long int int32_t;


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long int uint32_t;


typedef signed char int_least8_t;
typedef signed int int_least16_t;
typedef signed long int int_least32_t;


typedef unsigned char uint_least8_t;
typedef unsigned int uint_least16_t;
typedef unsigned long int uint_least32_t;



typedef signed char int_fast8_t;
typedef signed int int_fast16_t;
typedef signed long int int_fast32_t;


typedef unsigned char uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned long int uint_fast32_t;


typedef signed int intptr_t;
typedef unsigned int uintptr_t;


typedef signed long int intmax_t;
typedef unsigned long int uintmax_t;
#line 1 "c:/users/katarina.perendic/desktop/ir grid/example/c/pic/click_ir_grid_config.h"
#line 1 "c:/users/katarina.perendic/desktop/ir grid/example/c/pic/click_ir_grid_types.h"
#line 3 "c:/users/katarina.perendic/desktop/ir grid/example/c/pic/click_ir_grid_config.h"
const uint32_t _IRGRID_I2C_CFG[ 1 ] =
{
 100000
};
#line 28 "C:/Users/katarina.perendic/Desktop/IR Grid/example/c/PIC/Click_IR_Grid_PIC.c"
float ir_tmp[ 64 ];
char txt[ 64 ];

void systemInit()
{
 mikrobus_i2cInit( _MIKROBUS1, &_IRGRID_I2C_CFG[ 0 ] );
 mikrobus_logInit( _LOG_USBUART, 115200 );
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
