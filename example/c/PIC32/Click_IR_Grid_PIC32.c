/*
Example for IR_Grid Click

    Date          : jul 2018.
    Author        : MikroE Team

Test configuration PIC32 :
    
    MCU                : P32MX795F512L
    Dev. Board         : EasyPIC Fusion v7
    PIC32 Compiler ver : v4.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C module and USB UART for data logging
- Application Initialization - Initializes driver init and IR Grid module
- Application Task - (code snippet) - Reads the temperature of all pixels and creates a pixel temperature matrix that logs on usbuart every half of second

*/

#include "Click_IR_Grid_types.h"
#include "Click_IR_Grid_config.h"

float   ir_tmp[ 64 ];
char    demoText   [ 64 ];

void systemInit()
{
    mikrobus_i2cInit( _MIKROBUS1, &_IRGRID_I2C_CFG[ 0 ] );
    mikrobus_logInit( _LOG_USBUART_A, 115200 );
    Delay_ms( 100 );
}

void applicationInit()
{
    irgrid_i2cDriverInit( (T_IRGRID_P)&_MIKROBUS1_GPIO, (T_IRGRID_P)&_MIKROBUS1_I2C, 0x50, 0x60);
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

            FloatToStr( ir_tmp[ i ], demoText    );
            Ltrim( demoText    );
            demoText   [ 6 ] = 0;
            mikrobus_logWrite( demoText   , _LOG_TEXT );
            mikrobus_logWrite( "    ", _LOG_TEXT );
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