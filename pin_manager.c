/*
 * File:   pin_manager.c
 * Author: aleks
 *
 * Created on August 14, 2020, 12:28 PM
 */


#include <xc.h>

void pin_Initiasize(void) {

    // clear output register
    LATA = 0;
    LATB = 0; // lcd parallel data bus
    LATC = 0;
    LATD = 0;
    LATCbits.LATC4 = 1; // SS1 select should be high on start

    // 0 - digital, 1 - analog
    ANSELA = 0;
    ANSELB = 0;
    ANSELC = 0;
    ANSELD = 0;

    // 0 - output, 1 - input
    TRISA = 0b01000000;
    TRISB = 0;
    // RC2 - MSSP1 I2C SDA.
    // RC3 - MSSP1 I2C SCL.
    TRISC = 0b00001100;
    TRISD = 0; // lcd parallel data bus
}
