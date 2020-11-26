/*
 * File:   internal_interrupt.c
 * Author: aleks
 *
 * Created on August 19, 2020, 1:50 PM
 */


#include <xc.h>
#include <stdint.h>
#include "rs3231_i2c.h"
#include "lcd.h"

void int_i_initialize(void) {
    INTPPS = 0x06; // internal interrupt pin is RA6
    INTEDG = 0;
    return;
}

void int_ISR(void) {
    INTF = 0;
    clear_a1f();
//    clear_a2f();

    uint8_t time_string[8];
    uint8_t date_string[10];
    get_time_string(time_string);
    get_date_string(date_string);
    lcd_set_cursor(1, 1);
    lcd_write_ascii(time_string, 8);
    lcd_set_cursor(2, 1);
    lcd_write_ascii(date_string, 10);
}
