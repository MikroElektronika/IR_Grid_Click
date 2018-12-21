![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# IR_Grid Click

- **CIC Prefix**  : IRGRID
- **Author**      : MikroE Team
- **Verison**     : 1.0.0
- **Date**        : Mar 2018.

---

### Software Support

We provide a library for the IR_Grid Click on our [LibStock](https://libstock.mikroe.com/projects/view/2364/ir-grid-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library performs IR and temperature measurement. Sensor gets IR picture of detected object (body) and measures ambient temperature, 
compares that two measurements and shows IR picture as 16x4 matrix. For more details check documentation.

Key functions :

- ``` uint8_t irgrid_deviceInit(uint8_t refrate) ``` - Device Initialization
- ``` uint8_t irgrid_measure() ``` - Measurement
- ``` void irgrid_get_ir_raw(int16_t *buffer) ``` - Read Raw Temperature buffer
- ``` void irgrid_get_temperature(float *buffer) ``` - Read Calculated Temperature buffer
- ``` float irgrid_get_amb_temperature() ``` - Read Ambient Temperature



**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C module and USB UART for data logging
- Application Initialization - Initializes driver init and IR Grid module
- Application Task - (code snippet) - Reads the temperature of all pixels and creates a pixel temperature matrix that logs on usbuart every half of second


```.c
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

            FloatToStr( ir_tmp[ i ], demoText );
            Ltrim( demoText );
            demoText[ 6 ] = 0;
            mikrobus_logWrite( demoText, _LOG_TEXT );
            mikrobus_logWrite( "    ", _LOG_TEXT );
        }
        mikrobus_logWrite( " " ,_LOG_LINE );
    }
    mikrobus_logWrite( " " ,_LOG_LINE );
    mikrobus_logWrite( " " ,_LOG_LINE );
    mikrobus_logWrite( " " ,_LOG_LINE );
    Delay_ms(500);
}
```

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/2364/ir-grid-click) page.

Other mikroE Libraries used in the example:

- I2C
- UART

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
### Architectures Supported

#### mikroC

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x |   |

#### mikroBasic

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x |   |

#### mikroPascal

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x |   |

---
---
