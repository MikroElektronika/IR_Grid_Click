_systemInit:
;Click_IR_Grid_STM.c,32 :: 		void systemInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_IR_Grid_STM.c,34 :: 		mikrobus_i2cInit( _MIKROBUS1, &_IRGRID_I2C_CFG[ 0 ] );
MOVW	R0, #lo_addr(__IRGRID_I2C_CFG+0)
MOVT	R0, #hi_addr(__IRGRID_I2C_CFG+0)
MOV	R1, R0
MOVS	R0, #0
BL	_mikrobus_i2cInit+0
;Click_IR_Grid_STM.c,35 :: 		mikrobus_logInit( _LOG_USBUART_A, 115200 );
MOV	R1, #115200
MOVS	R0, #32
BL	_mikrobus_logInit+0
;Click_IR_Grid_STM.c,36 :: 		Delay_ms( 100 );
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_systemInit0:
SUBS	R7, R7, #1
BNE	L_systemInit0
NOP
NOP
NOP
;Click_IR_Grid_STM.c,37 :: 		}
L_end_systemInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _systemInit
_applicationInit:
;Click_IR_Grid_STM.c,39 :: 		void applicationInit()
SUB	SP, SP, #4
STR	LR, [SP, #0]
;Click_IR_Grid_STM.c,41 :: 		irgrid_i2cDriverInit( (T_IRGRID_P)&_MIKROBUS1_GPIO, (T_IRGRID_P)&_MIKROBUS1_I2C, 0x50, 0x60);
MOVS	R3, #96
MOVS	R2, #80
MOVW	R1, #lo_addr(__MIKROBUS1_I2C+0)
MOVT	R1, #hi_addr(__MIKROBUS1_I2C+0)
MOVW	R0, #lo_addr(__MIKROBUS1_GPIO+0)
MOVT	R0, #hi_addr(__MIKROBUS1_GPIO+0)
BL	_irgrid_i2cDriverInit+0
;Click_IR_Grid_STM.c,42 :: 		Delay_ms( 100 );
MOVW	R7, #20351
MOVT	R7, #18
NOP
NOP
L_applicationInit2:
SUBS	R7, R7, #1
BNE	L_applicationInit2
NOP
NOP
NOP
;Click_IR_Grid_STM.c,43 :: 		irgrid_deviceInit( 16 );
MOVS	R0, #16
BL	_irgrid_deviceInit+0
;Click_IR_Grid_STM.c,45 :: 		mikrobus_logWrite( "IR GRID INITIALIZED", _LOG_LINE);
MOVW	R0, #lo_addr(?lstr1_Click_IR_Grid_STM+0)
MOVT	R0, #hi_addr(?lstr1_Click_IR_Grid_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_IR_Grid_STM.c,46 :: 		mikrobus_logWrite( "IR GRID TEMPERATURE MESUREMENT",_LOG_LINE);
MOVW	R0, #lo_addr(?lstr2_Click_IR_Grid_STM+0)
MOVT	R0, #hi_addr(?lstr2_Click_IR_Grid_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_IR_Grid_STM.c,47 :: 		}
L_end_applicationInit:
LDR	LR, [SP, #0]
ADD	SP, SP, #4
BX	LR
; end of _applicationInit
_applicationTask:
;Click_IR_Grid_STM.c,49 :: 		void applicationTask()
SUB	SP, SP, #8
STR	LR, [SP, #0]
;Click_IR_Grid_STM.c,55 :: 		if( 1 != irgrid_measure() )
BL	_irgrid_measure+0
CMP	R0, #1
IT	EQ
BEQ	L_applicationTask4
;Click_IR_Grid_STM.c,57 :: 		irgrid_get_temperature( &ir_tmp[ 0 ] );
MOVW	R0, #lo_addr(_ir_tmp+0)
MOVT	R0, #hi_addr(_ir_tmp+0)
BL	_irgrid_get_temperature+0
;Click_IR_Grid_STM.c,58 :: 		}
L_applicationTask4:
;Click_IR_Grid_STM.c,60 :: 		for (rc = 0; rc < 4; rc++)
MOVS	R0, #0
STRB	R0, [SP, #4]
L_applicationTask5:
LDRB	R0, [SP, #4]
CMP	R0, #4
IT	CS
BCS	L_applicationTask6
;Click_IR_Grid_STM.c,62 :: 		for (cc = 0; cc < 16; cc++)
MOVS	R0, #0
STRB	R0, [SP, #5]
L_applicationTask8:
LDRB	R0, [SP, #5]
CMP	R0, #16
IT	CS
BCS	L_applicationTask9
;Click_IR_Grid_STM.c,64 :: 		i = (cc * 4) + rc;
LDRB	R0, [SP, #5]
LSLS	R1, R0, #2
SXTH	R1, R1
LDRB	R0, [SP, #4]
ADDS	R0, R1, R0
SXTH	R0, R0
;Click_IR_Grid_STM.c,66 :: 		FloatToStr( ir_tmp[ i ], txt );
UXTB	R0, R0
LSLS	R1, R0, #2
MOVW	R0, #lo_addr(_ir_tmp+0)
MOVT	R0, #hi_addr(_ir_tmp+0)
ADDS	R0, R0, R1
LDR	R0, [R0, #0]
MOVW	R1, #lo_addr(_txt+0)
MOVT	R1, #hi_addr(_txt+0)
BL	_FloatToStr+0
;Click_IR_Grid_STM.c,67 :: 		Ltrim( txt );
MOVW	R0, #lo_addr(_txt+0)
MOVT	R0, #hi_addr(_txt+0)
BL	_Ltrim+0
;Click_IR_Grid_STM.c,68 :: 		txt[ 6 ] = 0;
MOVS	R1, #0
MOVW	R0, #lo_addr(_txt+6)
MOVT	R0, #hi_addr(_txt+6)
STRB	R1, [R0, #0]
;Click_IR_Grid_STM.c,69 :: 		mikrobus_logWrite( txt, _LOG_TEXT );
MOVS	R1, #1
MOVW	R0, #lo_addr(_txt+0)
MOVT	R0, #hi_addr(_txt+0)
BL	_mikrobus_logWrite+0
;Click_IR_Grid_STM.c,70 :: 		mikrobus_logWrite( "\t", _LOG_TEXT );
MOVW	R0, #lo_addr(?lstr3_Click_IR_Grid_STM+0)
MOVT	R0, #hi_addr(?lstr3_Click_IR_Grid_STM+0)
MOVS	R1, #1
BL	_mikrobus_logWrite+0
;Click_IR_Grid_STM.c,62 :: 		for (cc = 0; cc < 16; cc++)
LDRB	R0, [SP, #5]
ADDS	R0, R0, #1
STRB	R0, [SP, #5]
;Click_IR_Grid_STM.c,71 :: 		}
IT	AL
BAL	L_applicationTask8
L_applicationTask9:
;Click_IR_Grid_STM.c,72 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
MOVW	R0, #lo_addr(?lstr4_Click_IR_Grid_STM+0)
MOVT	R0, #hi_addr(?lstr4_Click_IR_Grid_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_IR_Grid_STM.c,60 :: 		for (rc = 0; rc < 4; rc++)
LDRB	R0, [SP, #4]
ADDS	R0, R0, #1
STRB	R0, [SP, #4]
;Click_IR_Grid_STM.c,73 :: 		}
IT	AL
BAL	L_applicationTask5
L_applicationTask6:
;Click_IR_Grid_STM.c,74 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
MOVW	R0, #lo_addr(?lstr5_Click_IR_Grid_STM+0)
MOVT	R0, #hi_addr(?lstr5_Click_IR_Grid_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_IR_Grid_STM.c,75 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
MOVW	R0, #lo_addr(?lstr6_Click_IR_Grid_STM+0)
MOVT	R0, #hi_addr(?lstr6_Click_IR_Grid_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_IR_Grid_STM.c,76 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
MOVW	R0, #lo_addr(?lstr7_Click_IR_Grid_STM+0)
MOVT	R0, #hi_addr(?lstr7_Click_IR_Grid_STM+0)
MOVS	R1, #2
BL	_mikrobus_logWrite+0
;Click_IR_Grid_STM.c,77 :: 		Delay_ms(500);
MOVW	R7, #36223
MOVT	R7, #91
NOP
NOP
L_applicationTask11:
SUBS	R7, R7, #1
BNE	L_applicationTask11
NOP
NOP
NOP
;Click_IR_Grid_STM.c,78 :: 		}
L_end_applicationTask:
LDR	LR, [SP, #0]
ADD	SP, SP, #8
BX	LR
; end of _applicationTask
_main:
;Click_IR_Grid_STM.c,80 :: 		void main()
;Click_IR_Grid_STM.c,82 :: 		systemInit();
BL	_systemInit+0
;Click_IR_Grid_STM.c,83 :: 		applicationInit();
BL	_applicationInit+0
;Click_IR_Grid_STM.c,85 :: 		while (1)
L_main13:
;Click_IR_Grid_STM.c,87 :: 		applicationTask();
BL	_applicationTask+0
;Click_IR_Grid_STM.c,88 :: 		}
IT	AL
BAL	L_main13
;Click_IR_Grid_STM.c,89 :: 		}
L_end_main:
L__main_end_loop:
B	L__main_end_loop
; end of _main
