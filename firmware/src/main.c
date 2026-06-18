#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

#define LCD_PORT PORTC
#define LCD_DIR  DDRC
#define RS PD6  // Move RS to Port D Pin 6
#define En PD7  // Move En to Port D Pin 7

void lcd_command(unsigned char cmd) {
    LCD_PORT = cmd;             // Put command on Port C pins
    PORTD &= ~(1 << RS);        // RS = 0 (Command mode)
    PORTD |= (1 << En);         // Pulse Enable High
    _delay_ms(2);
    PORTD &= ~(1 << En);        // Pulse Enable Low
    _delay_ms(2);
}

void lcd_char(unsigned char data) {
    LCD_PORT = data;            // Put data byte on Port C pins
    PORTD |= (1 << RS);         // RS = 1 (Data mode)
    PORTD |= (1 << En);         // Pulse Enable High
    _delay_ms(2);
    PORTD &= ~(1 << En);        // Pulse Enable Low
    _delay_ms(2);
}

void lcd_init(void) {
    LCD_DIR = 0xFF;             // Set all Port C pins as outputs
    DDRD |= (1 << RS) | (1 << En); // Set control pins as outputs
    _delay_ms(50);              // Wait for LCD power-up
    
    lcd_command(0x38);          // 8-bit mode, 2 lines, 5x7 matrix
    lcd_command(0x0C);          // Display ON, Cursor OFF
    lcd_command(0x01);          // Clear Screen
    _delay_ms(5);
}

void lcd_print(char *str) {
    while (*str) {
        lcd_char(*str++);
    }
}

void update_display(int current_count) {
    lcd_command(0x01);          // Clear screen
    _delay_ms(5);
    lcd_print("Object Counter");
    lcd_command(0xC0);          // Move to line 2
    lcd_print("Count: ");
    
    lcd_char((current_count / 10) + '0');
    lcd_char((current_count % 10) + '0');
}

int main(void) {
    // Buttons, LED, and Buzzer inputs/outputs on PORTA and PORTB
    DDRB &= ~(1 << PB0);
    DDRA &= ~(1 << PA0);
    PORTB |= (1 << PB0);        // Input Pull-up
    PORTA |= (1 << PA0);        // Input Pull-up
    DDRB |= (1 << PB2) | (1 << PB3); // LED and Buzzer outputs

    int count = 0;
    lcd_init();
    update_display(count);

    while (1) {
        // Counter Button
        if ((PINB & (1 << PB0)) == 0) {
            _delay_ms(50);      // Debounce
            if ((PINB & (1 << PB0)) == 0) {
                count++;
                if (count > 99) count = 0;
                update_display(count);
                while ((PINB & (1 << PB0)) == 0); // Wait for release
            }
        }

        // Trigger Alert
        if (count >= 5) {
            PORTB |= (1 << PB2);
            PORTB |= (1 << PB3);
        }

        // Reset Button
        if ((PINA & (1 << PA0)) == 0) {
            count = 0;
            PORTB &= ~(1 << PB2);
            PORTB &= ~(1 << PB3);
            update_display(count);
        }
    }
}