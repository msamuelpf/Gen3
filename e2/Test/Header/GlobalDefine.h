/***********************************************************************/
/*                                                                     */
/*  FILE        :GlobalDefine.h                                        */
/*  DATE        :31/01/2014                                            */
/*  DESCRIPTION :Global Literals Definition                            */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyD                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

typedef unsigned char U8;
typedef signed char I8;
typedef unsigned int U16;
typedef signed int I16;
typedef unsigned long int U32;
typedef signed long int I32;
typedef float F32;
typedef double F64;


//#define C_ALT_TEST

//#define C_EFX1870P001 //K24 
#define C_EFX2009P001 // Centauro 200


#define C_OFF                       0
#define C_ON                        1
#define IN                          0
#define OUT                         1
#define END                         0
#define NOT_END                     1
#define C_LED_OFF                   1
#define C_LED_ON                    0

#define C_STOP                      0

#define C_FALSE                     0
#define C_TRUE                      1

#define C_NOT_EQUAL                 0
#define C_EQUAL                     1

#define C_DISABLE                   0
#define C_ENABLE                    1

#define C_CLOSE                     0
#define C_OPEN                      1

#define C_HIGH                      1
#define C_LOW                       0

#define C_BTN_PRESSED               1
#define C_BTN_NOT_PRESSED           0

#define C_KNOBS                  (0)
#define C_DIGITAL                (1)
#define C_HYBRID                 (2)

#define C_BTN_TIME_FILTER_TICK      C_50_ms
//--------------------------------------------------------------------
//                     COMMUNICATION COMMAND MODES
//--------------------------------------------------------------------
#define C_CMD_SET_TE_MODE           (U8)0x00
#define C_CMD_REPORT_MODEL          (U8)0x01
#define C_CMD_GET_MODEL             (U8)0x02
#define C_CMD_GET_16MEM_INDX        (U8)0x03
#define C_CMD_SET_16MEM_INDX        (U8)0x04
#define C_CMD_GET_8MEM_INDX         (U8)0x05
#define C_CMD_SET_8MEM_INDX         (U8)0x06
#define C_CMD_DISPLAY_RQST          (U8)0x07
#define C_CMD_DISPLAY_RQST2         (U8)0x08
#define C_CMD_DISPLAY_RQST3         (U8)0x09
#define C_CMD_WI_FI_RQST            (U8)0x0A
#define C_CMD_DISPENSER             (U8)0x0B
#define C_CMD_DEFAULT_FRAME         (U8)0x0C
#define C_CMD_SMART_GRID            (U8)0x0D
#define C_CMD_FLASH_FILL_RAM        (U8)0x0E
#define C_CMD_FLASH_WRITE_PARAM     (U8)0x0F
#define C_CMD_FLASH_READ_PARAM      (U8)0x10
#define C_CMD_FLASH_BUSY            (U8)0x11
#define C_CMD_TEST_LOADS            (U8)0x12
#define C_CMD_SAFETY_CRC            (U8)0x13
#define C_CMD_AUTOTEST              (U8)0xFE
#define C_CMD_RESET                 (U8)0xFF

#define C_COM_ADDR_ID               (0)
#define C_COM_COMMAND               (1)
#define C_COM_DATA01                ( 2)
#define C_COM_DATA02                ( 3)
#define C_COM_DATA03                ( 4)
#define C_COM_DATA04                ( 5)
#define C_COM_DATA05                ( 6)
#define C_COM_DATA06                ( 7)
#define C_COM_DATA07                ( 8)
#define C_COM_DATA08                ( 9)
#define C_COM_DATA09                (10)
#define C_COM_DATA10                (11)
#define C_COM_DATA11                (12)
#define C_CRC_HI                    (13)
#define C_CRC_LO                    (14)
#define C_COMM_DATA_END             (14)
#define C_COMM_FRAME_SIZE           (15)

#define C_DISPLAY_ID                (0x05)
#define C_TEST_EQUIPMENT_ID         (0x08)
#define C_MASTER_BOARD_ID           (0x0A)
#define C_MOTOR_CONTROL_ID          (0x04)
#define C_DISPENSER_ID              (0x07)
#define C_MASTER_TO_DISPLAY         (U8)(0xA5)
#define C_DISPLAY_TO_MASTER         (U8)(0x5A)
#define C_MASTER_TO_TEST_EQUIPMENT  (U8)(0xA8)
#define C_TEST_EQUIPMENT_TO_MASTER  (U8)(0x8A)
#define C_TEST_EQUIPMENT_TO_DISPLAY (U8)(0x85)
#define C_DISPLAY_TO_TEST_EQUIPMENT (U8)(0x58)

#define C_TEST_EQUIPMENT            (0)
#define C_DISPLAY                   (1)
#define C_MAX                       (1)

#define C_NOT_IN_TEST_MODE          (0)
#define C_LVL1                      (40)
#define C_LVL2                      (80)

#define C_TEMODE_OFF                (0)
#define C_TEMODE_ON                 (1)

#define C_TE_COMM_RATE_FAST         (4)
#define C_TE_COMM_RATE_NORMAL       (19)

#define C_MAX_16BIT_INDEX           (19)
#define C_MAX_8BIT_INDEX            (20)

#define C_NO_DISPLAY                (0)
#define C_PANEL                     (1)
#define C_DELAY_START               (2)
#define C_DISPL_LYRA                (3)
#define C_LYRA_NO_DISP              (4)

#define C_ID_CHECKSUM               (0)
#define C_ID_MODEL                  (1)

#define C_NO_HARDWARE               (0xFF)
#define C_NO_VERSION                (0x5A5A) // Equal to Version "ZZ"
#define C_NO_CHECKSUM               (0xFFFF)

#define C_BOARD_VERSION             (0)
#define C_BOARD_CHECKSUM            (1)

#define C_TEXT                      (0)
#define C_LANGUAGE                  (1)

#define C_ENGLISH                   (0)
#define C_SPANISH                   (1)

#define C_WASHER_DISPLAY            (0)
#define C_DRYER_DISPLAY             (1)

#define C_FRAME_0                   (0)
#define C_FRAME_1                   (1)
#define C_FRAME_2                   (2)

#define C_FRAME_SPEIRA              (9)
#define C_FRAME_MABE_STD            (6)
#define C_TIME_PERSONALIZADOR_ENABLE    (200*2)

#define C_MAX_MODEL                 (1)
#define C_NO_SOUND                  (0)

//--------------------------------------------------------------------
//             Input/Outputs Port Configuration             
//--------------------------------------------------------------------


//--------------------------------------------------------------------
//             Input/Outputs Port Definition             
//--------------------------------------------------------------------
#define P_UART_TX         (P0_bit.no0)
#define P_UART_RX         (P0_bit.no1)

#define P_ROW_1           (P12_bit.no4)
#define P_ROW_2           (P6_bit.no0)
#define P_ROW_3           (P12_bit.no2)
#define P_ROW_4           (P12_bit.no3)

#define P_MUX_1           (P6_bit.no3)
#define P_MUX_2           (P14_bit.no7)
#define P_MUX_3           (P6_bit.no2)
#define P_MUX_4           (P6_bit.no1)

#define P_S1              (P1_bit.no5)
#define P_S2              (P1_bit.no0)
#define P_S3              (P1_bit.no3)
#define P_S4              (P1_bit.no2)
#define P_S5              (P1_bit.no1)
#define P_S6              (P1_bit.no4)
#define P_S7              (P1_bit.no6)
#define P_S8              (P5_bit.no1)
#define P_S9              (P5_bit.no0)
#define P_S10             (P3_bit.no0)
#define P_S11             (P7_bit.no0)

#define P_BUZZER          (P3_bit.no1)
#define P_TEST_POINT_1    (P1_bit.no7)



//--------------------------------------------------------------------
//             Timer & counter variables
//--------------------------------------------------------------------
#define C_TMR_INTERRUPT_US  (U16)200// Microsegundos en los que se genera la interrupcion
#define C_MAIN_CLK_MHZ  (U16)4 // Frecuencia del reloj
#define C_TMR_INTERRUPT_REGISTER (U16)(C_TMR_INTERRUPT_US * C_MAIN_CLK_MHZ - 1) // Contador de registro de interrupcion // 200*8 - 1 =1599

#define C_MAIN_TICK_MS   (U8)2  // Main tick en milisegundos
#define C_MAIN_TICK_CNT (I16)(((U32)(C_MAIN_TICK_MS * 1000) /  (U32)C_TMR_INTERRUPT_US)) // Main tick counter


#define C_GEA_TICK_MS   (U8)1  // Main tick en milisegundos
#define C_GEA_TICK_CNT (I16)(((U32)(C_GEA_TICK_MS * 1000) /  (U32)C_TMR_INTERRUPT_US)) // GEA tick counter



//--------------------------------------------------------------------
//             Timer capture mode
//--------------------------------------------------------------------
#define C_CAPTURE_MODE_CLK  ((U32)32000000)

//--------------------------------------------------------------------
//             DMA variables
//--------------------------------------------------------------------
#define C_DMA0_BUFFER_SIZE  ((U16)64)
#define C_DMA_DELTA_ARRAY ((U16)5)

//--------------------------------------------------------------------
//             Imbalance detect variables
//--------------------------------------------------------------------
#define C_LOAD_BUFFER1 ((U8)1)
#define C_LOAD_BUFFER2 ((U8)2)
#define C_IMBALANCE_BUFFER_CNT  ((U16)200)
#define C_IMBALANCE_SETPOINT  ((I32)10000)

//--------------------------------------------------------------------
//             Voltage Measure (DutyCycle Measure )
//--------------------------------------------------------------------
#define C_PERIOD_60_HZ    ((U16)16666)
#define C_PERIOD_50_HZ    ((U16)20000)
#define C_PERIOD_45_HZ    ((U16)22222)
#define C_LINE_MAX_PERIOD (U16)(C_PERIOD_45_HZ / C_TMR_INTERRUPT_US)

//--------------------------------------------------------------------
//             Cycle Selector
//--------------------------------------------------------------------
#define C_CYCLE_EXPRESS      (U8)0
#define C_CYCLE_BEBE         (U8)1
#define C_CYCLE_BLANCA       (U8)2
#define C_CYCLE_COLOR        (U8)3
#define C_CYCLE_JEANS        (U8)4
#define C_CYCLE_VOLUMINOSAS  (U8)5
#define C_CYCLE_AUTOLIMPIEZA (U8)6
#define C_CYCLE_APAGADO      (U8)7
#define C_CYCLE_SHORT  (U8)254
#define C_CYCLE_OPEN   (U8)255

#define C_TOTAL_CYCLE_POSITIONS (U8)6


//--------------------------------------------------------------------
//                     BUZZER Definitions
//--------------------------------------------------------------------
                                         //Nota            Note            PWM
                                         //                Frequency    Frequency
#define C_SILENCE                   (0)  //Silence              0   
#define C_BEEP                      (1)  //                  4000.00    
#define C_C4                        (2)  //Do        C       8372.02     
#define C_B4                        (3)  //Si        B       7902.13     
#define C_A_4                       (4)  //La#       A#      7458.62     
#define C_A4                        (5)  //La        A       7040.00     
#define C_G_3                       (6)  //Sol#      G#      6644.88     
#define C_G3                        (7)  //Sol       G       6271.93     
#define C_F_3                       (8)  //Fa#       F#      5919.91     
#define C_F3                        (9)  //Fa        F       5587.65     
#define C_E3                        (10) //Mi        E       5274.04     
#define C_D_3                       (11) //Re#       D#      4978.03     
#define C_D3                        (12) //Re        D       4698.64     
#define C_C_3                       (13) //Do#       C#      4434.92     
#define C_C3                        (14) //Do        C       4186.01     4185.85
#define C_B3                        (15) //Si        B       3951.07     3951.01
#define C_A_3                       (16) //La#       A#      3729.31     3729.26
#define C_A3                        (17) //La        A       3520        3519.89
#define C_G_2                       (18) //Sol#      G#      3322.44     3322.26
#define C_G2                        (19) //Sol       G       3135.96     3135.78
#define C_F_2                       (20) //Fa#       F#      2959.96     2959.89
#define C_F2                        (21) //Fa        F       2793.83     2794.08
#define C_E2                        (22) //Mi        E       2637.02     2637.13
#define C_D_2                       (23) //Re#       D#      2489.02     2488.80
#define C_D2                        (24) //Re        D       2349.32     2349.35
#define C_C_2                       (25) //Do#       C#      2217.46     2217.54
#define C_C2                        (26) //Do        C       2093        2092.93
#define C_B2                        (27) //Si        B       1975.53     1975.70
#define C_A_2                       (28) //La#       A#      1864.66     1864.63
#define C_A2                        (29) //La        A       1760        1759.94
#define C_G_1                       (30) //Sol#      G#      1661.22     1661.27
#define C_G1                        (31) //Sol       G       1567.98     1568.01
#define C_F_1                       (32) //Fa#       F#      1479.98     1479.95
#define C_F1                        (33) //Fa        F       1396.91     1396.94
#define C_E1                        (34) //Mi        E       1318.51     1318.48
#define C_D_1                       (35) //Re#       D#      1244.51     1244.48
#define C_D1                        (36) //Re        D       1174.66     1174.61
#define C_C_1                       (37) //Do#       C#      1108.73     1108.71
#define C_C1                        (38) //Do        C       1046.5      1046.52
#define C_B1                        (39) //Si        B       987.77      987.80
#define C_A_1                       (40) //La#       A#      932.33      932.36
#define C_A1                        (41) //La        A       880         879.97
#define C_END_MUSIC             (0xFFFF)

#define C_BUZZER_INIT     ((U8)0)
#define C_BUZZER_PROCESS  ((U8)1)
#define C_BUZZER_KILL     ((U8)2)
#define C_BUZZER_OFF      ((U8)3)

#define C_BUZZER_MAIN_TICK  (U8)(10)
#define C_BUZZER_TICK   (U8)((C_BUZZER_MAIN_TICK / C_MAIN_TICK_MS) - 1)
#define C_BUZZER_1250ms ((U16) (1250 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_1000ms ((U16) (1000 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_900ms  ((U16) (900 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_800ms  ((U16) (800 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_750ms  ((U16) (750 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_700ms  ((U16) (700 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_600ms  ((U16) (600 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_560ms  ((U16) (560 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_500ms  ((U16) (500 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_450ms  ((U16) (450 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_400ms  ((U16) (400 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_350ms  ((U16) (350 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_300ms  ((U16) (300 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_270ms  ((U16) (270 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_250ms  ((U16) (250 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_230ms  ((U16) (230 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_200ms  ((U16) (200 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_170ms  ((U16) (170 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_150ms  ((U16) (150 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_140ms  ((U16) (140 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_130ms  ((U16) (130 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_120ms  ((U16) (120 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_110ms  ((U16) (110 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_100ms  ((U16) (100 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_090ms  ((U16) (90 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_080ms  ((U16) (80 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_070ms  ((U16) (70 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_050ms  ((U16) (50 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_030ms  ((U16) (30 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_020ms  ((U16) (20 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_010ms  ((U16) (10 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_70ms   ((U16) (70 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_50ms   ((U16) (50 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_30ms   ((U16) (30 / C_BUZZER_MAIN_TICK) - 1)
#define C_BUZZER_20ms   ((U16) (20 / C_BUZZER_MAIN_TICK) - 1)

#define C_MUSIC_BEEP             ((U8)0)
#define C_MUSIC_ENDOFCYCLE       ((U8)1)
#define C_MUSIC_END_DELAY        ((U8)2)
#define C_MUSIC_BEEP_LID         ((U8)3)
#define C_MUSIC_DOUBLE_BEEP      ((U8)4)
#define C_MUSIC_WARNING_BEEP     ((U8)5)
#define C_MUSIC_TECHNICIAN_TEST  ((U8)6)

//--------------------------------------------------------------------
//             Pressure sensor
//--------------------------------------------------------------------
#define C_PRESSURE_STATE_INIT   ((U8)0)
#define C_PRESSURE_STATE_FILTER ((U8)1)
#define C_PRESSURE_FILTER_CONST ((U32)128)
#define C_PRESSURE_FILTER_SHIFT ((U8)7)

//--------------------------------------------------------------------
//             Communication Protocol Definition
//--------------------------------------------------------------------
#define C_COMM_TIME_MS                    (U8)50
#define C_COMM_TICK                       (U8)(C_COMM_TIME_MS / C_MAIN_TICK_MS)
#define C_COMM_LEVEL_0  (U8)0
#define C_COMM_LEVEL_1  (U8)1
#define C_COMM_LEVEL_2  (U8)2
#define C_PERSONALIZE_TIME  (U8)30  // Time in seconds to personalize software after Power C_ON
#define C_TEST_EQUIPMENT_DISCONNECT_TIME  (U16)2000 // Time in miliseconds
#define C_TEST_EQUIPMENT_DISCONNECT_TICK  (U8)(C_TEST_EQUIPMENT_DISCONNECT_TIME / (U16)C_COMM_TIME_MS)
#define C_COMM_LEVEL_2_TIME (U16)50
#define C_COMM_LEVEL_2_TICK (U8)(C_COMM_LEVEL_2_TIME / (U16)C_COMM_TIME_MS)
#define C_COMM_LEVEL_1_TIME (U16)200
#define C_COMM_LEVEL_1_TICK (U8)(C_COMM_LEVEL_1_TIME / (U16)C_COMM_TIME_MS)
#define C_COMM_LEVEL_0_TIME (U16)1000
#define C_COMM_LEVEL_0_TICK (U8)(C_COMM_LEVEL_0_TIME / (U16)C_COMM_TIME_MS)
#define C_FRAME_RECEIVED_OK       (U8)0
#define C_FRAME_RECEIVED_INVALID  (U8)1
#define C_UI_DISCONNECTED         (U8)2
#define C_DISCONNECT_DETECT_TIME  (U16)5000 // Time in milliseconds
#define C_DISCONNECT_DETECT_TICK  (U8)(C_DISCONNECT_DETECT_TIME / (U16)C_COMM_TIME_MS)

#define C_WASHER          (U8)0
#define C_REFRIG          (U8)1
#define C_OVEN            (U8)2
#define C_DRYER           (U8)3
#define C_USER_INTERFACE  (U8)4

//--------------------------------------------------------------------
//             Display
//--------------------------------------------------------------------
#define C_MUX_LINES (U8)4

//--------------------------------------------------------------------
//             DISPLAY LEVELS
//--------------------------------------------------------------------
#define C_WATER_LEVEL_OFF   (U8)0  // Nivel apagado
#define C_WATER_LEVEL_LOW   (U8)1  // Nivel Bajo
#define C_WATER_LEVEL_MID   (U8)2  // Nivel Medio
#define C_WATER_LEVEL_HIGH  (U8)3  // Nivel Alto
#define C_WATER_LEVEL_AUTO  (U8)4  // Nivel Auto
#define C_WATER_LEVEL_ALL_ON (U8)5  // Nivel all on

#define C_TEMPERATURE_LEVEL_OFF     (U8)0  // Nivel apagado
#define C_TEMPERATURE_LEVEL_COLD    (U8)1  // Nivel Frio
#define C_TEMPERATURE_LEVEL_WARM    (U8)2  // Nivel Tibio
#define C_TEMPERATURE_LEVEL_HOT     (U8)3  // Nivel Caliente
#define C_TEMPERATURE_LEVEL_WARM_2  (U8)4  // Nivel Tibio 2
#define C_TEMPERATURE_LEVEL_WARM_3  (U8)5  // Nivel Tibio 3
#define C_TEMPERATURE_LEVEL_WARM_4  (U8)6  // Nivel Tibio 4
#define C_TEMPERATURE_LEVEL_AUTO    (U8)7  // Nivel Auto
#define C_TEMPERATURE_LEVEL_ON      (U8)15 // All LEDs On


#define C_SPIN_LEVEL_OFF  (U8)0  // Nivel apagado
#define C_SPIN_LEVEL_LOW  (U8)1  // Nivel Bajo
#define C_SPIN_LEVEL_MID  (U8)2  // Nivel Medio
#define C_SPIN_LEVEL_HIGH (U8)3  // Nivel Alto

#define C_SOIL_LEVEL_OFF  (U8)0  // Nivel apagado
#define C_SOIL_LEVEL_LOW  (U8)1  // Nivel bajo
#define C_SOIL_LEVEL_MID  (U8)2  // Nivel medio
#define C_SOIL_LEVEL_HIGH (U8)3  // Nivel alto

#define C_ECO_LEVEL_DISABLE (U8)0  // Nivel apagado
#define C_ECO_LEVEL_ENABLE  (U8)1  // Nivel Enable


//--------------------------------------------------------------------
//             Display
//--------------------------------------------------------------------
#define C_DISPLAY_0       (U8)0
#define C_DISPLAY_1       (U8)1
#define C_DISPLAY_2       (U8)2
#define C_DISPLAY_3       (U8)3
#define C_DISPLAY_4       (U8)4
#define C_DISPLAY_5       (U8)5
#define C_DISPLAY_6       (U8)6
#define C_DISPLAY_7       (U8)7
#define C_DISPLAY_8       (U8)8
#define C_DISPLAY_9       (U8)9
#define C_DISPLAY_A       (U8)10
#define C_DISPLAY_B       (U8)11
#define C_DISPLAY_C       (U8)12
#define C_DISPLAY_D       (U8)13
#define C_DISPLAY_E       (U8)14
#define C_DISPLAY_F       (U8)15
#define C_DISPLAY_G       (U8)16
#define C_DISPLAY_H       (U8)17
#define C_DISPLAY_J       (U8)18
#define C_DISPLAY_L       (U8)19
#define C_DISPLAY_N       (U8)20
#define C_DISPLAY_P       (U8)21
#define C_DISPLAY_R       (U8)22
#define C_DISPLAY_T       (U8)23
#define C_DISPLAY_U       (U8)24
#define C_DISPLAY_Y       (U8)25
#define C_DISPLAY_CLR     (U8)26
#define C_DISPLAY_SEG_A   (U8)27
#define C_DISPLAY_SEG_B   (U8)28
#define C_DISPLAY_SEG_C   (U8)29
#define C_DISPLAY_SEG_D   (U8)30
#define C_DISPLAY_SEG_E   (U8)31
#define C_DISPLAY_SEG_F   (U8)32
#define C_DISPLAY_SEG_G   (U8)33
#define C_DISPLAY_SEG_BCE (U8)34
#define C_DISPLAY_SEG_EF  (U8)35
#define C_DISPLAY_SEG_AB  (U8)36
#define C_DISPLAY_SEG_CD  (U8)37
#define C_DISPLAY_SEG_DE  (U8)38
#define C_DISPLAY_SEG_FA  (U8)39

/***********************************************************************
    Time definition
***********************************************************************/
#define C_20_ms       (U16)(20 / C_MAIN_TICK_MS)
#define C_30_ms       (U16)(30 / C_MAIN_TICK_MS)
#define C_40_ms       (U16)(40 / C_MAIN_TICK_MS)
#define C_50_ms       (U16)(50 / C_MAIN_TICK_MS)
#define C_60_ms       (U16)(60 / C_MAIN_TICK_MS)
#define C_70_ms       (U16)(70 / C_MAIN_TICK_MS)
#define C_100_ms      (U16)(100 / C_MAIN_TICK_MS)
#define C_120_ms      (U16)(120 / C_MAIN_TICK_MS)
#define C_160_ms      (U16)(160 / C_MAIN_TICK_MS)
#define C_200_ms      (U16)(200 / C_MAIN_TICK_MS)
#define C_250_ms      (U16)(250 / C_MAIN_TICK_MS)
#define C_300_ms      (U16)(300 / C_MAIN_TICK_MS)
#define C_350_ms      (U16)(350 / C_MAIN_TICK_MS)
#define C_400_ms      (U16)(400 / C_MAIN_TICK_MS)
#define C_450_ms      (U16)(450 / C_MAIN_TICK_MS)
#define C_500_ms      (U16)(500 / C_MAIN_TICK_MS)
#define C_600_ms      (U16)(600 / C_MAIN_TICK_MS)
#define C_700_ms      (U16)(700 / C_MAIN_TICK_MS)
#define C_750_ms      (U16)(750 / C_MAIN_TICK_MS)
#define C_800_ms      (U16)(800 / C_MAIN_TICK_MS)
#define C_900_ms      (U16)(900 / C_MAIN_TICK_MS)
#define C_1000_ms     (U16)(1000 / C_MAIN_TICK_MS)
#define C_1200_ms     (U16)(1200 / C_MAIN_TICK_MS)
#define C_1250_ms     (U16)(1250 / C_MAIN_TICK_MS)
#define C_1400_ms     (U16)(1400 / C_MAIN_TICK_MS)
#define C_1500_ms     (U16)(1500 / C_MAIN_TICK_MS)
#define C_1800_ms     (U16)(1800 / C_MAIN_TICK_MS)
#define C_2000_ms     (U16)(2000 / C_MAIN_TICK_MS)
#define C_2500_ms     (U16)(2500 / C_MAIN_TICK_MS)
// Tick maximo de 16 bits @ Tick = 10ms => 655 segundos = 10 minutos
#define C_1_SEC       (U32)((U32)1 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_2_SEC       (U32)((U32)2 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_3_SEC       (U32)((U32)3 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_4_SEC       (U32)((U32)4 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_5_SEC       (U32)((U32)5 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_10_SEC      (U32)((U32)10 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_15_SEC      (U32)((U32)15 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_19_SEC      (U32)((U32)19 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_20_SEC      (U32)((U32)20 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_25_SEC      (U32)((U32)25 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_30_SEC      (U32)((U32)30 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_35_SEC      (U32)((U32)35 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_40_SEC      (U32)((U32)40 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_45_SEC      (U32)((U32)45 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_50_SEC      (U32)((U32)50 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_60_SEC      (U32)((U32)60 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_90_SEC      (U32)((U32)90 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_120_SEC     (U32)((U32)120 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_150_SEC     (U32)((U32)150 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_180_SEC     (U32)((U32)180 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_300_SEC     (U32)((U32)300 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_600_SEC     (U32)((U32)600 * (U32)1000 / (U32)C_MAIN_TICK_MS)
#define C_720_SEC     (U32)((U32)720 * (U32)1000 / (U32)C_MAIN_TICK_MS)  // 12 minutos
#define C_900_SEC     (U32)((U32)900 * (U32)1000 / (U32)C_MAIN_TICK_MS)  // 15 minutos
#define C_3600_SEC     (U32)((U32)3600 * (U32)1000 / (U32)C_MAIN_TICK_MS)  // 60 minutos

/***********************************************************************
    TEST
***********************************************************************/
#define C_TEST_INIT               (U8)0
#define C_TEST_1                  (U8)1
#define C_TEST_2                  (U8)2
#define C_TEST_3                  (U8)3
#define C_TEST_4                  (U8)4
#define C_TEST_5                  (U8)5
#define C_TEST_6                  (U8)6
#define C_TEST_7                  (U8)7
#define C_TEST_8                  (U8)8
#define C_TEST_9                  (U8)9
#define C_TEST_10                 (U8)10
#define C_TEST_11                 (U8)11
#define C_TEST_12                 (U8)12
#define C_TEST_13                 (U8)13
#define C_TEST_14                 (U8)14
#define C_TEST_15                 (U8)15
#define C_TEST_16                 (U8)16
#define C_TEST_17                 (U8)17
#define C_TEST_18                 (U8)18
#define C_TEST_19                 (U8)19
#define C_TEST_20                 (U8)20
#define C_TEST_END                (U8)255

#define C_ALT_PERIOD  (U16)C_3_SEC
//--------------------------------------------------------------------
//             Structure Definitions
//--------------------------------------------------------------------
    struct  Ubit_def 
      {
        U8  b0:1;
        U8  b1:1;
        U8  b2:1;
        U8  b3:1;
        U8  b4:1;
        U8  b5:1;
        U8  b6:1;
        U8  b7:1;
      };
      
    struct SNibble_def
      {
        U8  LSNibble:4;
        U8  MSNibble:4;
      };
      
    union   Ubyte_def
      {
        struct  Ubit_def Ubit;
        struct  SNibble_def  nu4byte;
        U8      Ubyte;
      };

    struct  UInt_bit_def 
      {
        U8  b0:1;
        U8  b1:1;
        U8  b2:1;
        U8  b3:1;
        U8  b4:1;
        U8  b5:1;
        U8  b6:1;
        U8  b7:1;
        U8  b8:1;
        U8  b9:1;
        U8  b10:1;
        U8  b11:1;
        U8  b12:1;
        U8  b13:1;
        U8  b14:1;
        U8  b15:1;
      };
      
    /*union   UInt_def
      {
        U16      UInt;
      };*/
    union UByteNibble_def
      {
        struct  SNibble_def  nu4byte;   //byte
        U8  UNbyte;
      };

    struct SByte_def 
      {
        U8  LSByte;
        U8  MSByte;
      };
      
    union UInt_def
      {
        struct  UInt_bit_def Ubit;
        struct  SByte_def  nu8byte;   //nibble byte
        U16 Uint;
      };
      
    struct SInt_def 
      {
        U16  LSInt;
        U16  MSInt;
      };
      
    union ULongInt_def
      {
        struct  SInt_def  nu16Int;   //nibble byte
        U32     ULongInt;
      };

  struct SBuzzerParam
    {
      U16 u16FrequencyHz;
      U16 u16AttackTimeCsec;
      U16 u16DecayTimeCsec;
      U16 u16SustainTimeCsec;
      U16 u16ReleaseTimeCsec;
      U16 u16PeakVolume;
      U16 u16SustainVolume;
    };
    
    typedef enum {
        C_BUZZER_KILL_ST    = 0,
        C_BUZZER_INIT_ST,
        C_BUZZER_ATTACK_ST,
        C_BUZZER_DECAY_ST,
        C_BUZZER_SUSTAIN_ST,
        C_BUZZER_RELEASE_ST
    }EBuzzerSt;
    
struct stFilterBtnParameters
  {
    U8 u8FilteredSignal;
    U8 u8LastSignal;
    U16 u8TimeCnt;
    U16 u8TimeLimit;
  };
  
typedef enum {
  E_ST_INIT                 = 0,
  E_ST_OPERATION_MODE       = 1,
  E_ST_SUPPLIER_FCT         = 2,
  E_ST_UI_TEST_MODE         = 3,
  E_ST_ALT_TEST_MODE        = 4
} EMainProcessState;