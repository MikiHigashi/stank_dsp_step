// 自作ステッピングモータードライバー dsPIC 版
#define FCY 69784687UL
#include <libpic30.h>
#include "mcc_generated_files/mcc.h"
#include <stdio.h>
#include <string.h>
#include "soft_i2c.h"
#include "lcd_i2c.h"
#include "ltc2630.h"


uint16_t left = 0x8080; // SPI2DMAにて旋回値を受け取る


uint16_t table_pwm[] = {
	0,
	65535,
	59577,
	54161,
	49237,
	44761,
	40692,
	36993,
	33630,
	30573,
	27793,
	25267,
	22970,
	20881,
	18983,
	17257,
	15689,
	14262,
	12966,
	11787,
	10716,
	9741,
	8856,
	8051,
	7319,
	6653,
	6049,
	5499,
	4999,
	4544,
	4131,
	3756,
	3414,
	3104,
	2822,
	2565,
	2332,
	2120,
	1927,
	1752,
	1593,
	1448,
	1316,
	1197,
	1088,
	63296,
	57542,
	52311,
	47555,
	43232,
	39302,
	35729,
	13004,
	7948,
	5723,
	4472,
	3669,
	3111,
	2700,
	2385,
	2136,
	1934,
	1767,
	1626,
	1506,
	1403,
	1313,
	1234,
	1163,
	1101,
	2089,
	1988,
	1895,
	1812,
	1735,
	1664,
	1599,
	1492,
	1398,
	1316,
	1242,
	1177,
	1118,
	2129,
	2032,
	1943,
	1862,
	1788,
	1719,
	1655,
	1596,
	1540,
	1489,
	1441,
	1396,
	1353,
	1314,
	1276,
	1240,
	1207,
	1175,
	1145,
	1116,
	2178,
	2126,
	2076,
	2029,
	1984,
	1941,
	1899,
	1860,
	1822,
	1785,
	1750,
	1717,
	1684,
	1653,
	1623,
	1594,
	1566,
	1539,
	1513,
	1488,
	1463,
	1439,
	1417,
	1394,
	1373,
	1352,
	1332,
	1312,
	1293,
	1275,
	1257,
	1239,
	1222,
	1206,
	1190,
	1174,
	1159,
	1144,
	1130,
	1115,
	1102,
	2176,
	2150,
	2124,
	2099,
	2075,
	2051,
	2028,
	2005,
	1983,
	1961,
	1940,
	1919,
	1898,
	1878,
	1859,
	1840,
	1821,
	1802,
	1784,
	1767,
	1749,
	1732,
	1716,
	1699,
	1683,
	1668,
	1652,
	1637,
	1622,
	1607,
	1593,
	1579,
	1565,
	1551,
	1538,
	1525,
	1512,
	1499,
	1487,
	1474,
	1462,
	1450,
	1439,
	1427,
	1416,
	1405,
	1394,
	1383,
	1372,
	1362,
	1352,
	1341,
	1331,
	1322,
	1312,
	1302,
	1293,
	1284,
	1274,
	1265,
	1256,
	1248,
	1239,
	1230,
	1222,
	1214,
	1205,
	1197,
	1189,
	1181,
	1174,
	1166,
	1158,
	1151,
	1144,
	1136,
	1129,
	1122,
	1115,
	1108,
	1101,
	1094,
	1088,
	1081,
	1075,
	1068
};


uint8_t table_ps[] = {
	0,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	6,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};


uint8_t table_m0[] = {
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1
};


uint8_t table_m1[] = {
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1
};


uint8_t table_m2[] = {
	0,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};


uint8_t table_idx[] = {
    0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	13,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
	21,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
	34,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	68,
	69,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	79,
	82,
	85,
	88,
	91,
	94,
	97,
	100,
	103,
	106,
	109,
	112,
	115,
	118,
	121,
	124,
	127,
	130,
	133,
	136,
	139,
	142,
	145,
	148,
	151,
	154,
	157,
	160,
	163,
	166,
	169,
	172,
	175,
	178,
	181,
	184,
	187,
	190,
	193,
	196,
	199,
	202,
	205,
	208,
	211,
	214,
	217,
	220,
	223,
	226,
	229,
	229
};


uint8_t table_idx2[] = {
	0,
	50,
	52,
	54,
	56,
	58,
	60,
	62,
	64,
	66,
	67,
	69,
	70,
	71,
	73,
	74,
	76,
	77,
	78,
	80,
	81,
	82,
	84,
	85,
	87,
	88,
	89,
	91,
	92,
	93,
	95,
	96,
	98,
	99,
	100,
	102,
	103,
	104,
	106,
	107,
	109,
	110,
	111,
	113,
	114,
	115,
	117,
	118,
	120,
	121,
	122,
	124,
	125,
	127,
	128,
	129,
	131,
	132,
	133,
	135,
	136,
	138,
	139,
	140,
	142,
	143,
	144,
	146,
	147,
	149,
	150,
	151,
	153,
	154,
	155,
	157,
	158,
	160,
	161,
	162,
	164,
	165,
	166,
	168,
	169,
	171,
	172,
	173,
	175,
	176,
	178,
	179,
	180,
	182,
	183,
	184,
	186,
	187,
	189,
	190,
	191,
	193,
	194,
	195,
	197,
	198,
	200,
	201,
	202,
	204,
	205,
	206,
	208,
	209,
	211,
	212,
	213,
	215,
	216,
	217,
	219,
	220,
	222,
	223,
	224,
	226,
	227,
	229,
	229,
};



// 超低速と低速の境界
#define MIN_SPEED 50
// delay_ms
#define NUM_WAIT 3


char buf[32];
uint8_t motor = 128; // 走行値

uint16_t pulse_snd;
uint16_t pulse_res;
//uint16_t pulse_mol = 0; // MO がＬ期間に何回のセンサーパルスが入ったか
//uint16_t pulse_mo1 = 0; // MO の１周期間に何回のセンサーパルスが入ったか
//uint16_t pulse_mo = 0; // MO の新規発生


uint8_t PS_M1 = 0;

uint8_t now_speed = 0; // 現在速度
uint8_t pre_speed = 0; // 前回速度
signed char now_cw_n_ccw = 0; // 現在回転方向 1:正 -1:逆 -:停止

uint8_t target_speed = 0; // 目標速度
signed char target_cw_n_ccw = 0; // 目標回転方向 1:正 -1:逆 -:停止


//uint16_t lata0; // 旧LATA
//uint16_t lata1; // 最新LATA
//uint16_t latax; // 変化


void set_speed(uint8_t spd) {
        uint16_t s = table_pwm[spd];
        PTCON2 = table_ps[spd]; // プリスケーラー
        PTPER = s;
        PDC1 = (s >> 1);                
        _LATB2 = table_m0[spd]; // MODE0 ピン出力
        _LATB3 = table_m1[spd]; // MODE1 ピン出力
        _LATB4 = table_m2[spd]; // MODE2 ピン出力
}


uint8_t flg_late1;
uint8_t flg_latel;


// アラート発生
void in_alert(void) {
    PDC1 = 0;                
    PWM_Disable();
    ENABLE_SetLow();
    __delay_ms(10);
    ENABLE_SetHigh();
    PWM_Enable();
}


int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    DMA_ChannelEnable(DMA_CHANNEL_0);
    DMA_PeripheralAddressSet(DMA_CHANNEL_0, (volatile unsigned int) &SPI2BUF);
    DMA_StartAddressASet(DMA_CHANNEL_0, (uint16_t)(&left));        
    
//    char buf[32];
//    __delay_ms(100);    
//    LCD_i2c_init(8);

    // 出力全OFF
    MODE0_SetHigh(); // 1/128step
    MODE1_SetHigh(); // 1/128step
    MODE2_SetHigh(); // 1/128step
    PTPER = 65535;
    PDC1 = 0;                
    PWM_Disable();
    ENABLE_SetHigh();
    flg_late1 = flg_latel = 0;

    motor = 0;
    now_speed = pre_speed = 0;
    now_cw_n_ccw = 0;
    LTC2630_write(0);
    
    WATCHDOG_TimerClear();
    __delay_ms(500);

    while (1)
    {
        WATCHDOG_TimerClear();

        if ((LO0_GetValue() == 0) || (LO1_GetValue() == 0)) {
            in_alert();
        }

        // 入力値
        uint8_t turn = (left & 255); // 旋回値
        motor = (left >> 8); // 走行値
        
        if ((motor <=  136) && (motor >= 120)) {
            motor = 0; // ほぼ停止なので照準用超信地旋回する
        }
        else {
            motor = 1; // 走行中なので走行用旋回する
        }
        
        if (turn > 128) {
            if (motor) {
                target_speed = table_idx2[turn - 128]; // 目標速度
            }
            else {
                target_speed = table_idx[turn - 128]; // 目標速度
            }
            target_cw_n_ccw = 1;
        }
        else if (turn < 128) {
            if (motor) {
                target_speed = table_idx2[128 - turn]; // 目標速度
            }
            else {
                target_speed = table_idx[128 - turn]; // 目標速度
            }
            target_cw_n_ccw = (-1);
        }
        else {
            target_speed = 0; // 目標速度
            target_cw_n_ccw = 0;
        }

//        LCD_i2C_cmd(0x80);
//        sprintf(buf, "%3d %3d" , target_speed, motor);
//        LCD_i2C_data(buf);
        
        if (target_cw_n_ccw == now_cw_n_ccw) {
            if (target_speed <= MIN_SPEED) { // あるていど遅い
                now_speed = target_speed; // 即座に目標速度に合わせる
            }
            else {
                if (now_speed < target_speed) {
                    if (target_speed > MIN_SPEED) {
                        if (now_speed < MIN_SPEED) {
                            now_speed = MIN_SPEED;
                        }
                        else {
                            now_speed ++;
                        }
                    }
                    else {
                        now_speed = target_speed;
                    }
                }
                if (now_speed > target_speed) {
                    now_speed --;
                }
            }
        }
        else { // 向きが違う
            if (now_cw_n_ccw) { // 停止ではない
                // いったん停止させる
                now_cw_n_ccw = 0;
                now_speed = 0;
            }
            else {
                now_cw_n_ccw = target_cw_n_ccw;
                if (now_cw_n_ccw > 0) {
                    CW_CCW_SetLow();
                }
                else {
                    CW_CCW_SetHigh();
                }
            }
        }

        if (now_speed > 0) {
            if (now_speed != pre_speed) {
                set_speed(now_speed);
                if (now_speed < MIN_SPEED) {
                    LTC2630_write(500);
                }
                else {
                    LTC2630_write(1700);
                }
                PWM_Enable();
            }
        }
        else {
            PDC1 = 0;                
            PWM_Disable();
        }
        
        __delay_ms(NUM_WAIT);
        pre_speed = now_speed;
    }
    return 1; 
}
/**
 End of File
*/

