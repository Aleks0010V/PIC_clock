/*
 * File:   lcd.c
 * Author: Aleksandr Valentirov
 *
 * Created on March 8, 2020, 1:52 PM
 */

#include <stdlib.h>
#include <stdint.h>
#include <xc.h>
#include "lcd.h"
#include "system.h"

// port D of PIC16F18875 is used
#define LCD_PORT_DIR TRISB
#define LCD_O_DATA LATB
#define LCD_I_DATA PORTB
#define RS LATDbits.LATD5  // 1 - data, 0 - command
#define RW LATDbits.LATD6  // 1 - read, 0 - write
#define E LATDbits.LATD7   // enable signal
#define LCD_EN_DELAY 500


// low-level function to send data or command
void lcd_write_data(uint8_t data){
    E = 0;
    LCD_PORT_DIR = 0;
    LCD_O_DATA = data;
    E = 1;
    __delay_us(LCD_EN_DELAY);
    E = 0;
    __delay_us(LCD_EN_DELAY);
    return;
}

// no comments
void lcd_send_cmd(uint8_t cmd){
    RS = 0;
    RW = 0;
    lcd_write_data(cmd);
    return;
}

// no comments
void lcd_send_data(uint8_t data){
    RS = 1;
    RW = 0;
    lcd_write_data(data);
}

// sets display`s light, cursor visibility and cursor blinking
void display_controll(char d, char c, char b){
    // assembling final command
    uint8_t cmd = (8 | (d << 2)) | (8 | (c << 1)) | (8 | b);
    lcd_send_cmd(cmd);
    __delay_us(50);
    return;
}

// initializes the LCD as datasheet says
// works with 20x4 and 16x2
void lcd_init(void){

    RS = 0;
    RW = 0;
    E = 0;

    __delay_ms(150);  // power-up
    lcd_send_cmd(0b00110000);  //
    __delay_ms(6);  // first Function Set

    lcd_send_cmd(0b00110000);  //
    __delay_us(150);  // second
    lcd_send_cmd(0b00110000);  //
    __delay_us(150);  // third Function Set


    lcd_send_cmd(0b00111000);  // setting screen params by default (Function Set)
    __delay_us(100);  //
    display_controll(0, 0, 0);  // setting display params for init
    __delay_us(100);
    lcd_send_cmd(1);  // clear display
    __delay_ms(3);
    lcd_send_cmd(0b00000110);  // entry mode set command
    __delay_us(100);


    display_controll(1, 0, 0);
    __delay_us(50);

    return;
}

// literally, sets the cursor`s position
// with HD44780 command 0x80 + address + position index
void lcd_set_cursor(uint8_t r, uint8_t c)
{
    uint8_t pos;
    switch(r){
        case 1:
            pos = 0x80;
            break;
        case 2:
            pos = 0xC0;  // 0x80 + 0x40
            break;
        case 3:
            pos = 0x94;  // 0x80 + 0x14
            break;
        case 4:
            pos = 0xD4;  // 0x80 + 0x54
            break;
    }
    pos = pos + c - 1;
    lcd_send_cmd(pos);
    __delay_us(80);
}

// sends specific number of characters to the display
void lcd_write_ascii(uint8_t *str, size_t data_size){
    while(data_size--){
        lcd_send_data(*str++);
    }
}

// sends a string which ends with \0
void lcd_write_string(uint8_t *str){
    while((*str) != '\0'){
        lcd_send_data(*str++);
    }
}

// takes a position and clears N cells after it, including it
void clear_n_cells(uint8_t row, uint8_t pos, uint8_t n){
    lcd_set_cursor(row, pos);
    while(n--){
        lcd_send_data(' ');
    }
    return;
}
