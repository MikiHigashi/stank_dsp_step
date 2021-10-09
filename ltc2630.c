#include <xc.h>
#include <stdio.h>
#include <string.h>

#define FCY 69784687UL
#include <libpic30.h>
#include "ltc2630.h"
#include "mcc_generated_files/mcc.h"


void LTC2630_write(uint16_t volt) {
    CSLD_SetHigh();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    CSLD_SetLow();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);

    // コマンド出力 0011xxxx
    SDI_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SDI_SetHigh();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);

    // データー送信
    if (volt & 2048) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);

    if (volt & 1024) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);

    if (volt & 512) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);

    if (volt & 256) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);

    if (volt & 128) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    if (volt & 64) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    if (volt & 32) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    if (volt & 16) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    if (volt & 8) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    if (volt & 4) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    if (volt & 2) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    if (volt & 1) {
        SDI_SetHigh();
    }
    else {
        SDI_SetLow();
    }
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    SCK_SetHigh();
    __delay_us(1);
    SCK_SetLow();
    __delay_us(1);
    
    CSLD_SetHigh();
}
