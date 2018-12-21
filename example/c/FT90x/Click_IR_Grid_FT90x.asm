_systemInit:
;Click_IR_Grid_FT90x.c,45 :: 		void systemInit()
;Click_IR_Grid_FT90x.c,47 :: 		mikrobus_i2cInit( _MIKROBUS1, &_IRGRID_I2C_CFG[ 0 ] );
LDK.L	R0, #__IRGRID_I2C_CFG+0
MOVE.L	R1, R0
LDK.L	R0, #0
CALL	_mikrobus_i2cInit+0
;Click_IR_Grid_FT90x.c,48 :: 		mikrobus_logInit( _LOG_USBUART, 115200 );
LDK.L	R1, #115200
LDK.L	R0, #16
CALL	_mikrobus_logInit+0
;Click_IR_Grid_FT90x.c,49 :: 		Delay_ms( 100 );
LPM.L	R28, #3333331
NOP	
L_systemInit0:
SUB.L	R28, R28, #1
CMP.L	R28, #0
JMPC	R30, Z, #0, L_systemInit0
JMP	$+8
	#3333331
NOP	
NOP	
;Click_IR_Grid_FT90x.c,50 :: 		}
L_end_systemInit:
RETURN	
; end of _systemInit
_applicationInit:
;Click_IR_Grid_FT90x.c,52 :: 		void applicationInit()
;Click_IR_Grid_FT90x.c,54 :: 		irgrid_i2cDriverInit( (T_IRGRID_P)&_MIKROBUS1_GPIO, (T_IRGRID_P)&_MIKROBUS1_I2C, 0x50, 0x60);
LDK.L	R3, #96
LDK.L	R2, #80
LDK.L	R1, #__MIKROBUS1_I2C+0
LDK.L	R0, #__MIKROBUS1_GPIO+0
CALL	_irgrid_i2cDriverInit+0
;Click_IR_Grid_FT90x.c,55 :: 		Delay_ms( 100 );
LPM.L	R28, #3333331
NOP	
L_applicationInit2:
SUB.L	R28, R28, #1
CMP.L	R28, #0
JMPC	R30, Z, #0, L_applicationInit2
JMP	$+8
	#3333331
NOP	
NOP	
;Click_IR_Grid_FT90x.c,56 :: 		irgrid_deviceInit( 16 );
LDK.L	R0, #16
CALL	_irgrid_deviceInit+0
;Click_IR_Grid_FT90x.c,58 :: 		mikrobus_logWrite( "IR GRID INITIALIZED", _LOG_LINE);
LDK.L	R0, #?lstr1_Click_IR_Grid_FT90x+0
LDK.L	R1, #2
CALL	_mikrobus_logWrite+0
;Click_IR_Grid_FT90x.c,59 :: 		mikrobus_logWrite( "IR GRID TEMPERATURE MESUREMENT",_LOG_LINE);
LDK.L	R0, #?lstr2_Click_IR_Grid_FT90x+0
LDK.L	R1, #2
CALL	_mikrobus_logWrite+0
;Click_IR_Grid_FT90x.c,60 :: 		}
L_end_applicationInit:
RETURN	
; end of _applicationInit
_applicationTask:
;Click_IR_Grid_FT90x.c,62 :: 		void applicationTask()
LINK	LR, #4
;Click_IR_Grid_FT90x.c,68 :: 		if( 1 != irgrid_measure() )
CALL	_irgrid_measure+0
CMP.B	R0, #1
JMPC	R30, Z, #1, L_applicationTask4
;Click_IR_Grid_FT90x.c,70 :: 		irgrid_get_temperature( &ir_tmp[ 0 ] );
LDK.L	R0, #_ir_tmp+0
CALL	_irgrid_get_temperature+0
;Click_IR_Grid_FT90x.c,71 :: 		}
L_applicationTask4:
;Click_IR_Grid_FT90x.c,73 :: 		for (rc = 0; rc < 4; rc++)
LDK.L	R0, #0
STI.B	SP, #0, R0
L_applicationTask5:
LDI.B	R0, SP, #0
CMP.B	R0, #4
JMPC	R30, C, #0, L_applicationTask6
;Click_IR_Grid_FT90x.c,75 :: 		for (cc = 0; cc < 16; cc++)
LDK.L	R0, #0
STI.B	SP, #1, R0
L_applicationTask8:
LDI.B	R0, SP, #1
CMP.B	R0, #16
JMPC	R30, C, #0, L_applicationTask9
;Click_IR_Grid_FT90x.c,77 :: 		i = (cc * 4) + rc;
LDI.B	R0, SP, #1
ASHL.L	R1, R0, #2
BEXTS.L	R1, R1, #0
LDI.B	R0, SP, #0
ADD.L	R0, R1, R0
BEXTS.L	R0, R0, #0
;Click_IR_Grid_FT90x.c,79 :: 		FloatToStr( ir_tmp[ i ], txt );
BEXTU.L	R0, R0, #256
ASHL.L	R1, R0, #2
LDK.L	R0, #_ir_tmp+0
ADD.L	R0, R0, R1
LDI.L	R0, R0, #0
LDK.L	R1, #_txt+0
CALL	_FloatToStr+0
;Click_IR_Grid_FT90x.c,80 :: 		Ltrim( txt );
LDK.L	R0, #_txt+0
CALL	_Ltrim+0
;Click_IR_Grid_FT90x.c,81 :: 		txt[ 6 ] = 0;
LDK.L	R0, #0
STA.B	_txt+6, R0
;Click_IR_Grid_FT90x.c,82 :: 		mikrobus_logWrite( txt, _LOG_TEXT );
LDK.L	R1, #1
LDK.L	R0, #_txt+0
CALL	_mikrobus_logWrite+0
;Click_IR_Grid_FT90x.c,83 :: 		mikrobus_logWrite( "\t", _LOG_TEXT );
LDK.L	R0, #?lstr3_Click_IR_Grid_FT90x+0
LDK.L	R1, #1
CALL	_mikrobus_logWrite+0
;Click_IR_Grid_FT90x.c,75 :: 		for (cc = 0; cc < 16; cc++)
LDI.B	R0, SP, #1
ADD.L	R0, R0, #1
STI.B	SP, #1, R0
;Click_IR_Grid_FT90x.c,84 :: 		}
JMP	L_applicationTask8
L_applicationTask9:
;Click_IR_Grid_FT90x.c,85 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
LDK.L	R0, #?lstr4_Click_IR_Grid_FT90x+0
LDK.L	R1, #2
CALL	_mikrobus_logWrite+0
;Click_IR_Grid_FT90x.c,73 :: 		for (rc = 0; rc < 4; rc++)
LDI.B	R0, SP, #0
ADD.L	R0, R0, #1
STI.B	SP, #0, R0
;Click_IR_Grid_FT90x.c,86 :: 		}
JMP	L_applicationTask5
L_applicationTask6:
;Click_IR_Grid_FT90x.c,87 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
LDK.L	R0, #?lstr5_Click_IR_Grid_FT90x+0
LDK.L	R1, #2
CALL	_mikrobus_logWrite+0
;Click_IR_Grid_FT90x.c,88 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
LDK.L	R0, #?lstr6_Click_IR_Grid_FT90x+0
LDK.L	R1, #2
CALL	_mikrobus_logWrite+0
;Click_IR_Grid_FT90x.c,89 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
LDK.L	R0, #?lstr7_Click_IR_Grid_FT90x+0
LDK.L	R1, #2
CALL	_mikrobus_logWrite+0
;Click_IR_Grid_FT90x.c,90 :: 		Delay_ms(500);
LPM.L	R28, #16666665
NOP	
L_applicationTask11:
SUB.L	R28, R28, #1
CMP.L	R28, #0
JMPC	R30, Z, #0, L_applicationTask11
JMP	$+8
	#16666665
;Click_IR_Grid_FT90x.c,91 :: 		}
L_end_applicationTask:
UNLINK	LR
RETURN	
; end of _applicationTask
_main:
;Click_IR_Grid_FT90x.c,93 :: 		void main()
LDK.L	SP, #43605
;Click_IR_Grid_FT90x.c,95 :: 		systemInit();
CALL	_systemInit+0
;Click_IR_Grid_FT90x.c,96 :: 		applicationInit();
CALL	_applicationInit+0
;Click_IR_Grid_FT90x.c,98 :: 		while (1)
L_main13:
;Click_IR_Grid_FT90x.c,100 :: 		applicationTask();
CALL	_applicationTask+0
;Click_IR_Grid_FT90x.c,101 :: 		}
JMP	L_main13
;Click_IR_Grid_FT90x.c,102 :: 		}
L_end_main:
L__main_end_loop:
JMP	L__main_end_loop
; end of _main
