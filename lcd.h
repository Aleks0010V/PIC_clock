/*
 * File:   lcd.h
 * Author: Aleksandr Valentirov
 *
 * Created on March 8, 2020, 1:51 PM
 */

#include <stdint.h>

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

    void lcd_send_data(unsigned char data);
    void lcd_send_cmd(uint8_t cmd);
    void lcd_init(void);
    void lcd_set_cursor(uint8_t r, unsigned char c);
    void lcd_write_ascii(uint8_t *str, size_t data_size);
    void lcd_write_string(uint8_t *str);
    void clear_n_cells(uint8_t row, uint8_t pos, uint8_t n);
    void display_controll(uint8_t d, uint8_t c, uint8_t b);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */
