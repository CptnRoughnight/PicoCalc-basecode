#ifndef I2C_KEYBOARD_H
#define I2C_KEYBOARD_H

#include <pico/stdlib.h>
#include <pico/platform.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>



#define KEY_JOY_UP      0x01
#define KEY_JOY_DOWN    0x02
#define KEY_JOY_LEFT    0x03
#define KEY_JOY_RIGHT   0x04
#define KEY_JOY_CENTER  0x05
#define KEY_BTN_LEFT1   0x06
#define KEY_BTN_RIGHT1  0x07

#define KEY_BACKSPACE   0x08 
#define KEY_TAB         0x09
#define KEY_ENTER       0x0A 
// 0x0D - CARRIAGE RETURN
#define KEY_BTN_LEFT2   0x11
#define KEY_BTN_RIGHT2  0x12


#define KEY_MOD_ALT     0xA1
#define KEY_MOD_SHL     0xA2
#define KEY_MOD_SHR     0xA3
#define KEY_MOD_SYM     0xA4
#define KEY_MOD_CTRL    0xA5

#define KEY_ESC       0xB1
#define KEY_UP        0xb5
#define KEY_DOWN      0xb6
#define KEY_LEFT      0xb4
#define KEY_RIGHT     0xb7

#define KEY_BREAK     0xd0 // == KEY_PAUSE
#define KEY_INSERT    0xD1
#define KEY_HOME      0xD2
#define KEY_DEL       0xD4
#define KEY_END       0xD5
#define KEY_PAGE_UP    0xd6
#define KEY_PAGE_DOWN  0xd7

#define KEY_CAPS_LOCK   0xC1

#define I2C_KBD_MOD i2c1
#define I2C_KBD_SDA 6   // 6
#define I2C_KBD_SCL 7  // 7

#define I2C_KBD_SPEED  100000 //400000 // if dual i2c, then the speed of keyboard i2c should be 10khz

#define I2C_KBD_ADDR 0x1F

void init_i2c_kbd();
int read_i2c_kbd();

#endif