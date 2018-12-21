/*
    __irgrid_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__irgrid_driver.h"
#include "__irgrid_hal.c"

/* ------------------------------------------------------------------- MACROS */

const uint8_t _IRGRID_CAL_ACOMMON_L     = 0xD0;
const uint8_t _IRGRID_CAL_ACOMMON_H     = 0xD1;
const uint8_t _IRGRID_CAL_ACP_L         = 0xD3;
const uint8_t _IRGRID_CAL_ACP_H         = 0xD4;
const uint8_t _IRGRID_CAL_BCP           = 0xD5;
const uint8_t _IRGRID_CAL_ALPHA_CP_L    = 0xD6;
const uint8_t _IRGRID_CAL_ALPHA_CP_H    = 0xD7;
const uint8_t _IRGRID_CAL_TGC           = 0xD8;
const uint8_t _IRGRID_CAL_AI_SCALE      = 0xD9;
const uint8_t _IRGRID_CAL_BI_SCALE      = 0xD9;
const uint8_t _IRGRID_VTH_L             = 0xDA;
const uint8_t _IRGRID_VTH_H             = 0xDB;
const uint8_t _IRGRID_KT1_L             = 0xDC;
const uint8_t _IRGRID_KT1_H             = 0xDD;
const uint8_t _IRGRID_KT2_L             = 0xDE;
const uint8_t _IRGRID_KT2_H             = 0xDF;
const uint8_t _IRGRID_KT_SCALE          = 0xD2;
const uint8_t _IRGRID_CAL_A0_L          = 0xE0;
const uint8_t _IRGRID_CAL_A0_H          = 0xE1;
const uint8_t _IRGRID_CAL_A0_SCALE      = 0xE2;
const uint8_t _IRGRID_CAL_DELTA_A_SCALE = 0xE3;
const uint8_t _IRGRID_CAL_EMIS_L        = 0xE4;
const uint8_t _IRGRID_CAL_EMIS_H        = 0xE5;
const uint8_t _IRGRID_OSC_TRIM_VALUE    = 0xF7;

/* ---------------------------------------------------------------- VARIABLES */

#ifdef __IRGRID_DRV_I2C__
static uint8_t _slaveEEPROM;
static uint8_t _slaveRAM;
#endif

static uint8_t  _refresh_rate;
static float    _temperature_amb;

static uint8_t  _eeprom_data[256];
static int16_t  _ir_data[64];
static float    _temperature_data[64];
static float    _a_data[64];
static float    _b_data[64];
static float    _alpha_a_data[64];

static int16_t a_common;
static int16_t a_i_scale; 
static int16_t b_i_scale;
static int16_t k_t1_scale;
static int16_t k_t2_scale;
static int16_t resolution;
static int16_t cpix;
static int16_t ptat;

static float k_t1; 
static float k_t2;
static float emissivity;
static float tgc;
static float alpha_cp;
static float a_cp;
static float b_cp;
static float v_th;

/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */

static uint16_t _get_cfg();
static void _get_eeprom();
static void _get_ir();
static void _get_ptat();
static void _get_cpix();
static void _set_cgf();
static void _set_trim();
static void _calc_ta();
static void _calc_to();

static double _floor(double x);
static static double _eval_poly(double x, const double code * d, int n);
static double _sqrt(double x);
static double _exp(double x);
static double _log(double x);
static double __pow(double x, double y);
static void _memcpy(char * d1, char * s1, int n);

/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */
static void _memcpy(char * d1, char * s1, int n) {
  char *dd;
  char *ss;

  ss = s1;
  dd = d1;
  while(n--)
    *dd++ = *ss++;
}

#if defined  __MIKROC_PRO_FOR_PIC__

#define __pow(x,y)  _pow(x,y)
#define _sqrt(x) sqrt(x)
#define _log(x)  log(x)
#define _exp(x)  exp(x)

#else

#define DBL_MAX       3.40282347e+38
#define DBL_MANT_DIG  23
#define EXCESS        126
#define MAX_EXPONENT  255
#define _FRNDINT(x)   ((double)(long)(x))
#define CHAR_BIT      8
#define EXP_MAX       89.416
#define EXP_MIN      -87.33655

static union both
{
        struct flt
        {
                unsigned char   mant[2];
                unsigned        hmant:7;
                unsigned        exp:8;
                unsigned        sign:1;

        }        flt;
        double        fl;
};

//--------------
static double _frexp(double value, int * eptr) {
  union both uv;
  volatile int bb;

  uv.fl = value;
  bb = uv.flt.exp - EXCESS;
  *eptr = bb;
  uv.flt.exp = EXCESS;
 return uv.fl;
}

//--------------
static double _ldexp(double value, int newexp) {
   union both uv;

  uv.fl = value;
  newexp += uv.flt.exp;
  if (newexp < 0)
    return 0.0;
  else
    if (newexp > MAX_EXPONENT)
      if (value < 0.0)
        return -DBL_MAX;
      else
        return DBL_MAX;
    else
      uv.flt.exp = newexp;
  return uv.fl;

}



//-------------- Returns number rounded DOWN to the nearest integer
static double _floor(double x) {
  double    i;
  int       expon;

  expon = ((*(unsigned long *)&x >> 23) & 255);
  expon = expon- 127;
  if(expon < 0)
    if (x < 0.0)
      return -1.0;
    else
      return  0.0;
  if((unsigned)expon > sizeof(double) * CHAR_BIT - 8)
    return x;           /* already an integer */
  i = _FRNDINT(x);

  if(i > x)
    return i - 1.0;
  return i;
}

//-------------- Calculates polynom for number x, with coefficients stored in d[], for degree n
static static double _eval_poly(double x, const double code * d, int n) {
  double res;

  res = d[n];
  while(n)
    res = x * res + d[--n];

  return res;
}


//-------------- Returns square root of given number
static double _sqrt(double x) {
  double    og, ng;
  unsigned int     niter;
  int       expon;

  if(x <= 0.0)
    return 0.0;
  og = x;
  if(og < 1.0)
    og = 1.0/og;
  og = _frexp(og, &expon);
  og = _ldexp(og, expon/2);                // make an educated guess //
  if(x < 1.0)
    og = 1.0/og;
  niter = 20;
  do {
    ng = (x/og + og)/2.0;
    if(ng == og)
              break;
    og = ng;
  } while(--niter);

  return og;
}

//-------------- Returns number e raised to the _power of argument x
static double _exp(double x) {
  int       exp;
  char     sign;                                // Promenjeno unsigned int u
                                                                  // unsigned char (optimizacija)  MZ 11.08.2008.

  const static double coeff[] = {
    1.0000000000e+00,
    6.9314718056e-01,
    2.4022650695e-01,
    5.5504108945e-02,
    9.6181261779e-03,
    1.3333710529e-03,
    1.5399104432e-04,
    1.5327675257e-05,
    1.2485143336e-06,
    1.3908092221e-07,
  };

  if(x == 0.0)
    return 1.0;
  if (x > EXP_MAX)    //too big?
    return DBL_MAX;
  if (x < EXP_MIN)    //too small?
    return 0.0;
  sign = x < 0.0;
  if(sign)
    x = -x;
  x *= 1.4426950409;            // convert to log2 //
  exp = (int)_floor(x);
  x -= (double)exp;
  x = _ldexp(_eval_poly(x, coeff, sizeof coeff/sizeof coeff[0] - 1), exp);
  if(sign) {
    if (x == DBL_MAX)
      return 0.0;
    return 1.0/x;
  }
  return x;
}


//-------------- Returns natural logarithm of given argument - ln(x)
static double _log(double x) {
  int       exp;
  static const double coeff[] = {
     0.0000000001,      // a0 //
     0.9999964239,      // a1 //
    -0.4998741238,      // a2 //
     0.3317990258,      // a3 //
    -0.2407338084,      // a4 //
     0.1676540711,      // a5 //
    -0.0953293897,      // a6 //
     0.0360884937,      // a7 //
    -0.0064535442,      // a8 //
  };

  // zero or -ve arguments are not defined //

  if(x <= 0.0)
            return 0.0;
  x = _frexp(x, &exp) * 2.0 - 1.0;
  exp--;
  x = _eval_poly(x, coeff, sizeof coeff/sizeof coeff[0] - 1);
  return x + 0.69314718055995 * exp;
  //return x +   0.68768932874451 * exp;
}

//-------------- Returns argument x raised to _power of argument y
static double __pow(double x, double y) {
  unsigned char sign = 0;       
                               
  long yi;

  if(y == 0.0)
    return 1.0;
  if(x == 0.0)
    return 0.0;
  if(x < 0.0) {
    yi = (long)y;
    if((double)yi != y)
      return 0.0;
    sign = yi & 1;
    x = -x;
  }
  x = _log(x);
  x = x*y;
  x = _exp(x);

  if(sign)
    return -x;
  return x;
}
#endif

/* --------------------------------------------- C_Math and C_String */

static void _get_eeprom() 
{
    uint8_t writeReg;
    
    writeReg = 0;

    hal_i2cStart();
    hal_i2cWrite( _slaveEEPROM, &writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveEEPROM, _eeprom_data, 256, END_MODE_STOP );
}

static void _set_cgf()
{
    uint8_t tmp[5];
    uint8_t Hz_LSB;
    uint8_t Hz_MSB;

    switch (_refresh_rate)
    {
    case 0:
        Hz_LSB = 0x3F;
        break;
    case 1:
        Hz_LSB = 0x3E;
        break;
    case 2:
        Hz_LSB = 0x3D;
        break;
    case 4:
        Hz_LSB = 0x3C;
        break;
    case 8:
        Hz_LSB = 0x3B;
        break;
    case 16:
        Hz_LSB = 0x3A;
        break;
    case 32:
        Hz_LSB = 0x39;
        break;
    default:
        Hz_LSB = 0x3E;
        break;
    }

    Hz_MSB = 0x46;

    tmp[0] = 0x03;
    tmp[1] = (uint8_t)Hz_LSB - 0x55;
    tmp[2] = (Hz_LSB);
    tmp[3] = Hz_MSB - 0x55;
    tmp[4] = Hz_MSB;

    hal_i2cStart();
    hal_i2cWrite(_slaveRAM, tmp, 5, END_MODE_STOP);
    resolution = (_get_cfg() & 0x30) >> 4;
}

static void _set_trim() 
{
    uint8_t tmp[5];

    tmp[0] = 0x04;
    tmp[1] = (uint8_t) _eeprom_data[_IRGRID_OSC_TRIM_VALUE] - 0xAA;
    tmp[2] = _eeprom_data[_IRGRID_OSC_TRIM_VALUE];
    tmp[3] = 0x56;
    tmp[4] = 0x00;

    hal_i2cStart();
    hal_i2cWrite(_slaveRAM, tmp, 5, END_MODE_STOP);
}

static void _get_ir() 
{
    uint8_t i;
    uint8_t tmp_w[4];
    uint8_t tmp_r[128];

    tmp_w[0] = 0x02;
    tmp_w[1] = 0x00;
    tmp_w[2] = 0x01;
    tmp_w[3] = 0x40;

    hal_i2cStart();
    hal_i2cWrite( _slaveRAM, tmp_w, 4, END_MODE_RESTART );
    hal_i2cRead( _slaveRAM, tmp_r, 128, END_MODE_STOP );

    for (i = 0; i < 64; i++)
    {
            _ir_data[i] = 0;
        _ir_data[i] |= tmp_r[(i * 2) + 1];
        _ir_data[i] <<= 8;
        _ir_data[i] |= tmp_r[i * 2];
    }
}

static void _get_ptat() 
{
    uint8_t rd[2];
    uint8_t tmp[4];

    tmp[0] = 0x02;
    tmp[1] = 0x40;
    tmp[2] = 0x00;
    tmp[3] = 0x01;

    hal_i2cStart();
    hal_i2cWrite(_slaveRAM, tmp, 4, END_MODE_RESTART);
    hal_i2cRead(_slaveRAM, rd, 2, END_MODE_STOP );

    ptat = ((uint16_t)(rd[1] << 8) | rd[0]);
}

static void _get_cpix() 
{
    uint8_t rd[2];
    uint8_t tmp[4];

    tmp[0] = 0x02;
    tmp[1] = 0x41;
    tmp[2] = 0x00;
    tmp[3] = 0x01;

    hal_i2cStart();
    hal_i2cWrite(_slaveRAM, tmp, 4, END_MODE_RESTART);
    hal_i2cRead(_slaveRAM, rd, 2, END_MODE_STOP );

    cpix = ((uint16_t)(rd[1] << 8) | rd[0]);
    
    if (cpix >= 32768)
    {
        cpix -= 65536;
    }
}

static uint16_t _get_cfg() 
{
    uint8_t rd[2];
    uint8_t tmp[4];
    uint16_t config;

    tmp[0] = 0x02;
    tmp[1] = 0x92;
    tmp[2] = 0x00;
    tmp[3] = 0x01;

    hal_i2cStart();
    hal_i2cWrite(_slaveRAM, tmp, 4, END_MODE_RESTART);
    hal_i2cRead(_slaveRAM, rd, 2, END_MODE_STOP );

    config = ((uint16_t) (rd[1] << 8) | rd[0]);
    return config;
}

static void _calc_ta() 
{
    k_t1_scale = (int16_t) (_eeprom_data[_IRGRID_KT_SCALE] & 0xF0) >> 4;
    k_t2_scale = (int16_t) (_eeprom_data[_IRGRID_KT_SCALE] & 0x0F) + 10;
    v_th = (float) 256 * _eeprom_data[_IRGRID_VTH_H] + _eeprom_data[_IRGRID_VTH_L];
    
    if (v_th >= 32768.0)
    {
        v_th -= 65536.0;
    }
    v_th = v_th / __pow(2, (3 - resolution));
    k_t1 = (float) 256 * _eeprom_data[_IRGRID_KT1_H] + _eeprom_data[_IRGRID_KT1_L];
    
    if (k_t1 >= 32768.0)
    {
        k_t1 -= 65536.0;
    }

    k_t1 /= (__pow(2, k_t1_scale) * __pow(2, (3 - resolution)));
    k_t2 = (float) 256 * _eeprom_data[_IRGRID_KT2_H] + _eeprom_data[_IRGRID_KT2_L];
    
    if (k_t2 >= 32768.0)
    {
        k_t2 -= 65536.0;
    }

    k_t2 /= (__pow(2, k_t2_scale) * __pow(2, (3 - resolution)));
    
    _temperature_amb = ((-k_t1 + _sqrt(__pow(k_t1, 2) - (4 * k_t2 * (v_th - (float) ptat)))) / (2 * k_t2)) + 25.0;
}

static void _calc_to() 
{
    uint16_t i;
    
    float vcp_offset_compensated;
    float vir_offset_compensated;
    float vir_tgc_compensated;
    float vir_normal;
    float vir_compensated;

    emissivity = (256 * _eeprom_data[_IRGRID_CAL_EMIS_H] + _eeprom_data[_IRGRID_CAL_EMIS_L]) / 32768.0;
    a_common = (int16_t) 256 * _eeprom_data[_IRGRID_CAL_ACOMMON_H] + _eeprom_data[_IRGRID_CAL_ACOMMON_L];
    
    alpha_cp = (256 * _eeprom_data[_IRGRID_CAL_ALPHA_CP_H] + _eeprom_data[_IRGRID_CAL_ALPHA_CP_L]) / (__pow(2, _eeprom_data[_IRGRID_CAL_A0_SCALE]) * __pow(2, (3 - resolution)));
    a_i_scale = (int16_t) (_eeprom_data[_IRGRID_CAL_AI_SCALE] & 0xF0) >> 4;
    b_i_scale = (int16_t) _eeprom_data[_IRGRID_CAL_BI_SCALE] & 0x0F;
    
    a_cp = (float) 256 * _eeprom_data[_IRGRID_CAL_ACP_H] + _eeprom_data[_IRGRID_CAL_ACP_L];
    a_cp /= __pow(2, (3 - resolution));
    b_cp = (float) _eeprom_data[_IRGRID_CAL_BCP];
    b_cp /= (__pow(2, b_i_scale) * __pow(2, (3 - resolution)));
    tgc = (float) _eeprom_data[_IRGRID_CAL_TGC];
    tgc /= 32.0;
    vcp_offset_compensated = (float) cpix - (a_cp + b_cp * (_temperature_amb - 25.0));
    
    for (i = 0; i < 64; i++)
    {
        _a_data[i] = ((float) a_common + _eeprom_data[i] * __pow(2, a_i_scale)) / __pow(2, (3 - resolution));
        _b_data[i] = _eeprom_data[0x40 + i];

        if (_b_data[i] > 127)
        {
            _b_data[i] -= 256;
        }

        _b_data[i] = _b_data[i] / (__pow(2, b_i_scale) * __pow(2, (3 - resolution)));
        vir_offset_compensated = _ir_data[i] - (_a_data[i] + _b_data[i] * (_temperature_amb - 25.0));
        vir_tgc_compensated = vir_offset_compensated - tgc * vcp_offset_compensated;
        _alpha_a_data[i] = ((256 * _eeprom_data[_IRGRID_CAL_A0_H] + _eeprom_data[_IRGRID_CAL_A0_L]) / __pow(2, _eeprom_data[_IRGRID_CAL_A0_SCALE]));
        _alpha_a_data[i] += (_eeprom_data[0x80 + i] / __pow(2, _eeprom_data[_IRGRID_CAL_DELTA_A_SCALE]));
        _alpha_a_data[i] = _alpha_a_data[i] / __pow(2, 3 - resolution);
        vir_normal = vir_tgc_compensated / (_alpha_a_data[i] - tgc * alpha_cp);
        vir_compensated = vir_normal / emissivity;
        
        // Compensated compared to original formula ... 
        _temperature_data[i] = 329.5 - (_exp((_log((vir_compensated + __pow((_temperature_amb + 273.15), 4)))/4.0)));
    }
}

/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __IRGRID_DRV_SPI__

void irgrid_spiDriverInit(T_IRGRID_P gpioObj, T_IRGRID_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... _power ON
    // ... configure CHIP
}

#endif
#ifdef   __IRGRID_DRV_I2C__

void irgrid_i2cDriverInit(T_IRGRID_P gpioObj, T_IRGRID_P i2cObj, uint8_t slave_eeprom, uint8_t slave)
{
    _slaveEEPROM = slave_eeprom;
    _slaveRAM = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... _power ON
    // ... configure CHIP
}

#endif
#ifdef   __IRGRID_DRV_UART__

void irgrid_uartDriverInit(T_IRGRID_P gpioObj, T_IRGRID_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... _power ON
    // ... configure CHIP
}

#endif

// GPIO Only Drivers - remove in other cases
void irgrid_gpioDriverInit(T_IRGRID_P gpioObj)
{
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... _power ON
}

/* ----------------------------------------------------------- IMPLEMENTATION */

uint8_t irgrid_deviceInit(uint8_t refrate)
{
    uint8_t i;

    i = 0;
    _refresh_rate = refrate;
    
    do 
    {
        _get_eeprom();
        _set_trim();
        _set_cgf();

        if (i++ > 16)
        {
            return 1;
        }
    
    } while (!((_get_cfg() & 0x0400) >> 10));

    return 0;
}

uint8_t irgrid_measure()
{
    uint8_t i;

    i = 0;

    do 
    {
        _get_eeprom();
        _set_trim();
        _set_cgf();

        if (i++ > 16)
        {
            return 1;
        }
    
    } while (!((_get_cfg() & 0x0400) >> 10));

    _get_ptat();
    _get_ir();
    _calc_ta();
    _get_cpix();
    _calc_to();

    return 0;
}

float irgrid_get_amb_temperature() 
{
    return _temperature_amb;
}

void irgrid_get_ir_raw(int16_t *buffer)
{
    _memcpy(buffer, _ir_data, sizeof(int16_t) * 64);
}

void irgrid_get_temperature(float *buffer)
{
    _memcpy(buffer, _temperature_data, sizeof(float) * 64);
}





/* -------------------------------------------------------------------------- */
/*
  __irgrid_driver.c

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