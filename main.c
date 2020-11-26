/*
 * File:   main.c
 * Author: aleks
 *
 * Created on November 22, 2020, 10:50 PM
 */


#include <xc.h>
#include "system.h"
#include "timer_0.h"
#include "rs3231_i2c.h"
#include "I2C.h"
#include "internal_interrupt.h"
#include "lcd.h"

const uint8_t max_pos = 10;
const uint8_t max_row = 2;

void main(void) {
    System_Initialize();
    interrupt_enable();
    peripheral_int_enable();
    TMR0IF = 0;
    t0_int_enable();
    t0_enable();
    INTF = 0;
    INT_enable();

    // RTC configuration
    set_minutes(59);
    set_hours(0, 21);
    set_seconds(56);
    set_date(23);
    set_month(10);
    set_year(20, 21);
    
    uint8_t config_mode = 0, next_pos_trigger = 0, increment = 0;
    uint8_t pos = 1, row = 1;
    uint8_t current_time[8];
    uint8_t current_date[10];
    
    while (1) {
        if(PORTAbits.RA3 == 0 && config_mode == 0) {
            config_mode = 1;
            GIE = 0;
//            get_time_string(current_time);
//            get_date_string(current_date);
            lcd_set_cursor(1, 1);
            display_controll(1, 1, 1);
        } else if (PORTAbits.RA3 == 1 && config_mode == 1) {
            config_mode = 0;
            display_controll(1, 0, 0);
            lcd_send_cmd(1);  // clear display
            __delay_ms(3);
            GIE = 1;
        }
        
        if (config_mode == 1){
            if (PORTAbits.RA2 == 0 && next_pos_trigger == 0){
                next_pos_trigger = 1;
                if(pos < max_pos){
                    pos++;
                } else if (row < max_row) {
                    pos = 1;
                    row++;
                } else {
                    pos = 1, row = 1;
                }
                lcd_set_cursor(row, pos);
            } else if(PORTAbits.RA2 == 1 && next_pos_trigger == 1) {
                next_pos_trigger = 0;
            }
            
            if (PORTAbits.RA1 == 0 && increment == 0){
            
            } else if(PORTAbits.RA1 == 1 && increment == 1) {

            }
        }
        
    }

    return;
}

void __interrupt() ISR(void) {
    if (TMR0IF & TMR0IE)
        t0_ISR();
    if (SSP1IF & SSP1IE)
        i2c_ISR();
    if (INTF & INTE)
        int_ISR();
    return;
}
