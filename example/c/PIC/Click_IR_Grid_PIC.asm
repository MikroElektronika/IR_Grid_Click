
_systemInit:

;Click_IR_Grid_PIC.c,32 :: 		void systemInit()
;Click_IR_Grid_PIC.c,34 :: 		mikrobus_i2cInit( _MIKROBUS1, &_IRGRID_I2C_CFG[ 0 ] );
	CLRF        FARG_mikrobus_i2cInit_bus+0 
	MOVLW       __IRGRID_I2C_CFG+0
	MOVWF       FARG_mikrobus_i2cInit_cfg+0 
	MOVLW       hi_addr(__IRGRID_I2C_CFG+0)
	MOVWF       FARG_mikrobus_i2cInit_cfg+1 
	MOVLW       higher_addr(__IRGRID_I2C_CFG+0)
	MOVWF       FARG_mikrobus_i2cInit_cfg+2 
	CALL        _mikrobus_i2cInit+0, 0
;Click_IR_Grid_PIC.c,35 :: 		mikrobus_logInit( _LOG_USBUART, 115200 );
	MOVLW       16
	MOVWF       FARG_mikrobus_logInit_port+0 
	MOVLW       0
	MOVWF       FARG_mikrobus_logInit_baud+0 
	MOVLW       194
	MOVWF       FARG_mikrobus_logInit_baud+1 
	MOVLW       1
	MOVWF       FARG_mikrobus_logInit_baud+2 
	MOVLW       0
	MOVWF       FARG_mikrobus_logInit_baud+3 
	CALL        _mikrobus_logInit+0, 0
;Click_IR_Grid_PIC.c,36 :: 		Delay_ms( 100 );
	MOVLW       9
	MOVWF       R11, 0
	MOVLW       30
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_systemInit0:
	DECFSZ      R13, 1, 1
	BRA         L_systemInit0
	DECFSZ      R12, 1, 1
	BRA         L_systemInit0
	DECFSZ      R11, 1, 1
	BRA         L_systemInit0
	NOP
;Click_IR_Grid_PIC.c,37 :: 		}
L_end_systemInit:
	RETURN      0
; end of _systemInit

_applicationInit:

;Click_IR_Grid_PIC.c,39 :: 		void applicationInit()
;Click_IR_Grid_PIC.c,41 :: 		irgrid_i2cDriverInit( (T_IRGRID_P)&_MIKROBUS1_GPIO, (T_IRGRID_P)&_MIKROBUS1_I2C, 0x50, 0x60);
	MOVLW       __MIKROBUS1_GPIO+0
	MOVWF       FARG_irgrid_i2cDriverInit_gpioObj+0 
	MOVLW       hi_addr(__MIKROBUS1_GPIO+0)
	MOVWF       FARG_irgrid_i2cDriverInit_gpioObj+1 
	MOVLW       higher_addr(__MIKROBUS1_GPIO+0)
	MOVWF       FARG_irgrid_i2cDriverInit_gpioObj+2 
	MOVLW       __MIKROBUS1_I2C+0
	MOVWF       FARG_irgrid_i2cDriverInit_i2cObj+0 
	MOVLW       hi_addr(__MIKROBUS1_I2C+0)
	MOVWF       FARG_irgrid_i2cDriverInit_i2cObj+1 
	MOVLW       higher_addr(__MIKROBUS1_I2C+0)
	MOVWF       FARG_irgrid_i2cDriverInit_i2cObj+2 
	MOVLW       80
	MOVWF       FARG_irgrid_i2cDriverInit_slave_eeprom+0 
	MOVLW       96
	MOVWF       FARG_irgrid_i2cDriverInit_slave+0 
	CALL        _irgrid_i2cDriverInit+0, 0
;Click_IR_Grid_PIC.c,42 :: 		Delay_ms( 100 );
	MOVLW       9
	MOVWF       R11, 0
	MOVLW       30
	MOVWF       R12, 0
	MOVLW       228
	MOVWF       R13, 0
L_applicationInit1:
	DECFSZ      R13, 1, 1
	BRA         L_applicationInit1
	DECFSZ      R12, 1, 1
	BRA         L_applicationInit1
	DECFSZ      R11, 1, 1
	BRA         L_applicationInit1
	NOP
;Click_IR_Grid_PIC.c,43 :: 		irgrid_deviceInit( 16 );
	MOVLW       16
	MOVWF       FARG_irgrid_deviceInit_refrate+0 
	CALL        _irgrid_deviceInit+0, 0
;Click_IR_Grid_PIC.c,45 :: 		mikrobus_logWrite( "IR GRID INITIALIZED", _LOG_LINE);
	MOVLW       ?lstr1_Click_IR_Grid_PIC+0
	MOVWF       FARG_mikrobus_logWrite_data_+0 
	MOVLW       hi_addr(?lstr1_Click_IR_Grid_PIC+0)
	MOVWF       FARG_mikrobus_logWrite_data_+1 
	MOVLW       2
	MOVWF       FARG_mikrobus_logWrite_format+0 
	CALL        _mikrobus_logWrite+0, 0
;Click_IR_Grid_PIC.c,46 :: 		mikrobus_logWrite( "IR GRID TEMPERATURE MESUREMENT",_LOG_LINE);
	MOVLW       ?lstr2_Click_IR_Grid_PIC+0
	MOVWF       FARG_mikrobus_logWrite_data_+0 
	MOVLW       hi_addr(?lstr2_Click_IR_Grid_PIC+0)
	MOVWF       FARG_mikrobus_logWrite_data_+1 
	MOVLW       2
	MOVWF       FARG_mikrobus_logWrite_format+0 
	CALL        _mikrobus_logWrite+0, 0
;Click_IR_Grid_PIC.c,47 :: 		}
L_end_applicationInit:
	RETURN      0
; end of _applicationInit

_applicationTask:

;Click_IR_Grid_PIC.c,49 :: 		void applicationTask()
;Click_IR_Grid_PIC.c,55 :: 		if( 1 != irgrid_measure() )
	CALL        _irgrid_measure+0, 0
	MOVLW       1
	XORWF       R0, 0 
	BTFSC       STATUS+0, 2 
	GOTO        L_applicationTask2
;Click_IR_Grid_PIC.c,57 :: 		irgrid_get_temperature( &ir_tmp[ 0 ] );
	MOVLW       _ir_tmp+0
	MOVWF       FARG_irgrid_get_temperature_buffer+0 
	MOVLW       hi_addr(_ir_tmp+0)
	MOVWF       FARG_irgrid_get_temperature_buffer+1 
	CALL        _irgrid_get_temperature+0, 0
;Click_IR_Grid_PIC.c,58 :: 		}
L_applicationTask2:
;Click_IR_Grid_PIC.c,60 :: 		for (rc = 0; rc < 4; rc++)
	CLRF        applicationTask_rc_L0+0 
L_applicationTask3:
	MOVLW       4
	SUBWF       applicationTask_rc_L0+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_applicationTask4
;Click_IR_Grid_PIC.c,62 :: 		for (cc = 0; cc < 16; cc++)
	CLRF        applicationTask_cc_L0+0 
L_applicationTask6:
	MOVLW       16
	SUBWF       applicationTask_cc_L0+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_applicationTask7
;Click_IR_Grid_PIC.c,64 :: 		i = (cc * 4) + rc;
	MOVF        applicationTask_cc_L0+0, 0 
	MOVWF       R0 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R0, 1 
	BCF         R0, 0 
	MOVF        applicationTask_rc_L0+0, 0 
	ADDWF       R0, 0 
	MOVWF       R3 
;Click_IR_Grid_PIC.c,66 :: 		FloatToStr( ir_tmp[ i ], txt );
	MOVF        R3, 0 
	MOVWF       R0 
	MOVLW       0
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       _ir_tmp+0
	ADDWF       R0, 0 
	MOVWF       FSR0 
	MOVLW       hi_addr(_ir_tmp+0)
	ADDWFC      R1, 0 
	MOVWF       FSR0H 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_FloatToStr_fnum+0 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_FloatToStr_fnum+1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_FloatToStr_fnum+2 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_FloatToStr_fnum+3 
	MOVLW       _txt+0
	MOVWF       FARG_FloatToStr_str+0 
	MOVLW       hi_addr(_txt+0)
	MOVWF       FARG_FloatToStr_str+1 
	CALL        _FloatToStr+0, 0
;Click_IR_Grid_PIC.c,67 :: 		Ltrim( txt );
	MOVLW       _txt+0
	MOVWF       FARG_Ltrim_string+0 
	MOVLW       hi_addr(_txt+0)
	MOVWF       FARG_Ltrim_string+1 
	CALL        _Ltrim+0, 0
;Click_IR_Grid_PIC.c,68 :: 		txt[ 6 ] = 0;
	CLRF        _txt+6 
;Click_IR_Grid_PIC.c,69 :: 		mikrobus_logWrite( txt, _LOG_TEXT );
	MOVLW       _txt+0
	MOVWF       FARG_mikrobus_logWrite_data_+0 
	MOVLW       hi_addr(_txt+0)
	MOVWF       FARG_mikrobus_logWrite_data_+1 
	MOVLW       1
	MOVWF       FARG_mikrobus_logWrite_format+0 
	CALL        _mikrobus_logWrite+0, 0
;Click_IR_Grid_PIC.c,70 :: 		mikrobus_logWrite( "\t", _LOG_TEXT );
	MOVLW       ?lstr3_Click_IR_Grid_PIC+0
	MOVWF       FARG_mikrobus_logWrite_data_+0 
	MOVLW       hi_addr(?lstr3_Click_IR_Grid_PIC+0)
	MOVWF       FARG_mikrobus_logWrite_data_+1 
	MOVLW       1
	MOVWF       FARG_mikrobus_logWrite_format+0 
	CALL        _mikrobus_logWrite+0, 0
;Click_IR_Grid_PIC.c,62 :: 		for (cc = 0; cc < 16; cc++)
	INCF        applicationTask_cc_L0+0, 1 
;Click_IR_Grid_PIC.c,71 :: 		}
	GOTO        L_applicationTask6
L_applicationTask7:
;Click_IR_Grid_PIC.c,72 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
	MOVLW       ?lstr4_Click_IR_Grid_PIC+0
	MOVWF       FARG_mikrobus_logWrite_data_+0 
	MOVLW       hi_addr(?lstr4_Click_IR_Grid_PIC+0)
	MOVWF       FARG_mikrobus_logWrite_data_+1 
	MOVLW       2
	MOVWF       FARG_mikrobus_logWrite_format+0 
	CALL        _mikrobus_logWrite+0, 0
;Click_IR_Grid_PIC.c,60 :: 		for (rc = 0; rc < 4; rc++)
	INCF        applicationTask_rc_L0+0, 1 
;Click_IR_Grid_PIC.c,73 :: 		}
	GOTO        L_applicationTask3
L_applicationTask4:
;Click_IR_Grid_PIC.c,74 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
	MOVLW       ?lstr5_Click_IR_Grid_PIC+0
	MOVWF       FARG_mikrobus_logWrite_data_+0 
	MOVLW       hi_addr(?lstr5_Click_IR_Grid_PIC+0)
	MOVWF       FARG_mikrobus_logWrite_data_+1 
	MOVLW       2
	MOVWF       FARG_mikrobus_logWrite_format+0 
	CALL        _mikrobus_logWrite+0, 0
;Click_IR_Grid_PIC.c,75 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
	MOVLW       ?lstr6_Click_IR_Grid_PIC+0
	MOVWF       FARG_mikrobus_logWrite_data_+0 
	MOVLW       hi_addr(?lstr6_Click_IR_Grid_PIC+0)
	MOVWF       FARG_mikrobus_logWrite_data_+1 
	MOVLW       2
	MOVWF       FARG_mikrobus_logWrite_format+0 
	CALL        _mikrobus_logWrite+0, 0
;Click_IR_Grid_PIC.c,76 :: 		mikrobus_logWrite( " " ,_LOG_LINE );
	MOVLW       ?lstr7_Click_IR_Grid_PIC+0
	MOVWF       FARG_mikrobus_logWrite_data_+0 
	MOVLW       hi_addr(?lstr7_Click_IR_Grid_PIC+0)
	MOVWF       FARG_mikrobus_logWrite_data_+1 
	MOVLW       2
	MOVWF       FARG_mikrobus_logWrite_format+0 
	CALL        _mikrobus_logWrite+0, 0
;Click_IR_Grid_PIC.c,77 :: 		Delay_ms(500);
	MOVLW       41
	MOVWF       R11, 0
	MOVLW       150
	MOVWF       R12, 0
	MOVLW       127
	MOVWF       R13, 0
L_applicationTask9:
	DECFSZ      R13, 1, 1
	BRA         L_applicationTask9
	DECFSZ      R12, 1, 1
	BRA         L_applicationTask9
	DECFSZ      R11, 1, 1
	BRA         L_applicationTask9
;Click_IR_Grid_PIC.c,78 :: 		}
L_end_applicationTask:
	RETURN      0
; end of _applicationTask

_main:

;Click_IR_Grid_PIC.c,80 :: 		void main()
;Click_IR_Grid_PIC.c,82 :: 		systemInit();
	CALL        _systemInit+0, 0
;Click_IR_Grid_PIC.c,83 :: 		applicationInit();
	CALL        _applicationInit+0, 0
;Click_IR_Grid_PIC.c,85 :: 		while (1)
L_main10:
;Click_IR_Grid_PIC.c,87 :: 		applicationTask();
	CALL        _applicationTask+0, 0
;Click_IR_Grid_PIC.c,88 :: 		}
	GOTO        L_main10
;Click_IR_Grid_PIC.c,89 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
