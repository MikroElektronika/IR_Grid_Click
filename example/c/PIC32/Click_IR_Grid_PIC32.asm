_systemInit:
;Click_IR_Grid_PIC32.c,45 :: 		void systemInit()
ADDIU	SP, SP, -12
SW	RA, 0(SP)
;Click_IR_Grid_PIC32.c,47 :: 		mikrobus_i2cInit( _MIKROBUS1, &_IRGRID_I2C_CFG[ 0 ] );
SW	R25, 4(SP)
SW	R26, 8(SP)
LUI	R2, hi_addr(__IRGRID_I2C_CFG+0)
ORI	R2, R2, lo_addr(__IRGRID_I2C_CFG+0)
MOVZ	R26, R2, R0
MOVZ	R25, R0, R0
JAL	_mikrobus_i2cInit+0
NOP	
;Click_IR_Grid_PIC32.c,48 :: 		mikrobus_logInit( _LOG_USBUART_A, 115200 );
LUI	R26, 1
ORI	R26, R26, 49664
ORI	R25, R0, 32
JAL	_mikrobus_logInit+0
NOP	
;Click_IR_Grid_PIC32.c,49 :: 		Delay_ms( 100 );
LUI	R24, 40
ORI	R24, R24, 45226
L_systemInit0:
ADDIU	R24, R24, -1
BNE	R24, R0, L_systemInit0
NOP	
;Click_IR_Grid_PIC32.c,50 :: 		}
L_end_systemInit:
LW	R26, 8(SP)
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 12
JR	RA
NOP	
; end of _systemInit
_applicationInit:
;Click_IR_Grid_PIC32.c,52 :: 		void applicationInit()
ADDIU	SP, SP, -20
SW	RA, 0(SP)
;Click_IR_Grid_PIC32.c,54 :: 		irgrid_i2cDriverInit( (T_IRGRID_P)&_MIKROBUS1_GPIO, (T_IRGRID_P)&_MIKROBUS1_I2C, 0x50, 0x60);
SW	R25, 4(SP)
SW	R26, 8(SP)
SW	R27, 12(SP)
SW	R28, 16(SP)
ORI	R28, R0, 96
ORI	R27, R0, 80
LUI	R26, hi_addr(__MIKROBUS1_I2C+0)
ORI	R26, R26, lo_addr(__MIKROBUS1_I2C+0)
LUI	R25, hi_addr(__MIKROBUS1_GPIO+0)
ORI	R25, R25, lo_addr(__MIKROBUS1_GPIO+0)
JAL	_irgrid_i2cDriverInit+0
NOP	
;Click_IR_Grid_PIC32.c,55 :: 		Delay_ms( 100 );
LUI	R24, 40
ORI	R24, R24, 45226
L_applicationInit2:
ADDIU	R24, R24, -1
BNE	R24, R0, L_applicationInit2
NOP	
;Click_IR_Grid_PIC32.c,56 :: 		irgrid_deviceInit( 16 );
ORI	R25, R0, 16
JAL	_irgrid_deviceInit+0
NOP	
;Click_IR_Grid_PIC32.c,58 :: 		mikrobus_logWrite( "IR GRID INITIALIZED", _LOG_LINE);
ORI	R26, R0, 2
LUI	R25, hi_addr(?lstr1_Click_IR_Grid_PIC32+0)
ORI	R25, R25, lo_addr(?lstr1_Click_IR_Grid_PIC32+0)
JAL	_mikrobus_logWrite+0
NOP	
;Click_IR_Grid_PIC32.c,59 :: 		mikrobus_logWrite( "IR GRID TEMPERATURE MESUREMENT",_LOG_LINE);
ORI	R26, R0, 2
LUI	R25, hi_addr(?lstr2_Click_IR_Grid_PIC32+0)
ORI	R25, R25, lo_addr(?lstr2_Click_IR_Grid_PIC32+0)
JAL	_mikrobus_logWrite+0
NOP	
;Click_IR_Grid_PIC32.c,60 :: 		}
L_end_applicationInit:
LW	R28, 16(SP)
LW	R27, 12(SP)
LW	R26, 8(SP)
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 20
JR	RA
NOP	
; end of _applicationInit
_applicationTask:
;Click_IR_Grid_PIC32.c,62 :: 		void applicationTask()
ADDIU	SP, SP, -16
SW	RA, 0(SP)
;Click_IR_Grid_PIC32.c,68 :: 		if( 1 != irgrid_measure() )
SW	R25, 4(SP)
SW	R26, 8(SP)
JAL	_irgrid_measure+0
NOP	
ANDI	R3, R2, 255
ORI	R2, R0, 1
BNE	R3, R2, L__applicationTask19
NOP	
J	L_applicationTask4
NOP	
L__applicationTask19:
;Click_IR_Grid_PIC32.c,70 :: 		irgrid_get_temperature( &ir_tmp[ 0 ] );
LUI	R25, hi_addr(_ir_tmp+0)
ORI	R25, R25, lo_addr(_ir_tmp+0)
JAL	_irgrid_get_temperature+0
NOP	
;Click_IR_Grid_PIC32.c,71 :: 		}
L_applicationTask4:
;Click_IR_Grid_PIC32.c,73 :: 		for (rc = 0; rc < 4; rc++)
SB	R0, 12(SP)
L_applicationTask5:
LBU	R2, 12(SP)
SLTIU	R2, R2, 4
BNE	R2, R0, L__applicationTask20
NOP	
J	L_applicationTask6
NOP	
L__applicationTask20:
;Click_IR_Grid_PIC32.c,75 :: 		for (cc = 0; cc < 16; cc++)
SB	R0, 13(SP)
L_applicationTask8:
LBU	R2, 13(SP)
SLTIU	R2, R2, 16
BNE	R2, R0, L__applicationTask21
NOP	
J	L_applicationTask9
NOP	
L__applicationTask21:
;Click_IR_Grid_PIC32.c,77 :: 		i = (cc * 4) + rc;
LBU	R2, 13(SP)
SLL	R3, R2, 2
LBU	R2, 12(SP)
ADDU	R2, R3, R2
;Click_IR_Grid_PIC32.c,79 :: 		FloatToStr( ir_tmp[ i ], txt );
ANDI	R2, R2, 255
SLL	R3, R2, 2
LUI	R2, hi_addr(_ir_tmp+0)
ORI	R2, R2, lo_addr(_ir_tmp+0)
ADDU	R2, R2, R3
LW	R2, 0(R2)
LUI	R26, hi_addr(_txt+0)
ORI	R26, R26, lo_addr(_txt+0)
MOVZ	R25, R2, R0
JAL	_FloatToStr+0
NOP	
;Click_IR_Grid_PIC32.c,80 :: 		Ltrim( txt );
LUI	R25, hi_addr(_txt+0)
ORI	R25, R25, lo_addr(_txt+0)
JAL	_Ltrim+0
NOP	
;Click_IR_Grid_PIC32.c,81 :: 		txt[ 6 ] = 0;
SB	R0, Offset(_txt+6)(GP)
;Click_IR_Grid_PIC32.c,82 :: 		mikrobus_logWrite( txt, _LOG_TEXT );
ORI	R26, R0, 1
LUI	R25, hi_addr(_txt+0)
ORI	R25, R25, lo_addr(_txt+0)
JAL	_mikrobus_logWrite+0
NOP	
;Click_IR_Grid_PIC32.c,83 :: 		mikrobus_logWrite( "\t", _LOG_TEXT );
ORI	R26, R0, 1
LUI	R25, hi_addr(?lstr3_Click_IR_Grid_PIC32+0)
ORI	R25, R25, lo_addr(?lstr3_Click_IR_Grid_PIC32+0)
JAL	_mikrobus_logWrite+0
NOP	
;Click_IR_Grid_PIC32.c,75 :: 		for (cc = 0; cc < 16; cc++)
LBU	R2, 13(SP)
ADDIU	R2, R2, 1
SB	R2, 13(SP)
;Click_IR_Grid_PIC32.c,84 :: 		}
J	L_applicationTask8
NOP	
L_applicationTask9:
;Click_IR_Grid_PIC32.c,85 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
ORI	R26, R0, 2
LUI	R25, hi_addr(?lstr4_Click_IR_Grid_PIC32+0)
ORI	R25, R25, lo_addr(?lstr4_Click_IR_Grid_PIC32+0)
JAL	_mikrobus_logWrite+0
NOP	
;Click_IR_Grid_PIC32.c,73 :: 		for (rc = 0; rc < 4; rc++)
LBU	R2, 12(SP)
ADDIU	R2, R2, 1
SB	R2, 12(SP)
;Click_IR_Grid_PIC32.c,86 :: 		}
J	L_applicationTask5
NOP	
L_applicationTask6:
;Click_IR_Grid_PIC32.c,87 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
ORI	R26, R0, 2
LUI	R25, hi_addr(?lstr5_Click_IR_Grid_PIC32+0)
ORI	R25, R25, lo_addr(?lstr5_Click_IR_Grid_PIC32+0)
JAL	_mikrobus_logWrite+0
NOP	
;Click_IR_Grid_PIC32.c,88 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
ORI	R26, R0, 2
LUI	R25, hi_addr(?lstr6_Click_IR_Grid_PIC32+0)
ORI	R25, R25, lo_addr(?lstr6_Click_IR_Grid_PIC32+0)
JAL	_mikrobus_logWrite+0
NOP	
;Click_IR_Grid_PIC32.c,89 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
ORI	R26, R0, 2
LUI	R25, hi_addr(?lstr7_Click_IR_Grid_PIC32+0)
ORI	R25, R25, lo_addr(?lstr7_Click_IR_Grid_PIC32+0)
JAL	_mikrobus_logWrite+0
NOP	
;Click_IR_Grid_PIC32.c,90 :: 		Delay_ms(500);
LUI	R24, 203
ORI	R24, R24, 29524
L_applicationTask11:
ADDIU	R24, R24, -1
BNE	R24, R0, L_applicationTask11
NOP	
NOP	
NOP	
;Click_IR_Grid_PIC32.c,91 :: 		}
L_end_applicationTask:
LW	R26, 8(SP)
LW	R25, 4(SP)
LW	RA, 0(SP)
ADDIU	SP, SP, 16
JR	RA
NOP	
; end of _applicationTask
_main:
;Click_IR_Grid_PIC32.c,93 :: 		void main()
;Click_IR_Grid_PIC32.c,95 :: 		systemInit();
JAL	_systemInit+0
NOP	
;Click_IR_Grid_PIC32.c,96 :: 		applicationInit();
JAL	_applicationInit+0
NOP	
;Click_IR_Grid_PIC32.c,98 :: 		while (1)
L_main13:
;Click_IR_Grid_PIC32.c,100 :: 		applicationTask();
JAL	_applicationTask+0
NOP	
;Click_IR_Grid_PIC32.c,101 :: 		}
J	L_main13
NOP	
;Click_IR_Grid_PIC32.c,102 :: 		}
L_end_main:
L__main_end_loop:
J	L__main_end_loop
NOP	
; end of _main
