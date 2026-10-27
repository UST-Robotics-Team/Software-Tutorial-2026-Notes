#ifndef __LCD_MAIN_H
#define __LCD_MAIN_H

/**
 * Select the LCD TFT model you are using
 * Uncomment to Select
 * !!! Remember to comment out others if you are not using
 */
// 3.5 inch
//#define MODEL_ILI9486
// 2.8 inch
//#define MODEL_ILI9341
// 1.8 inch
#define MODEL_ST7735
//#define MODEL_ST7735S

/* Includes */
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>

#include "gpio.h"
#include "spi.h"
#include "stm32f4xx.h"

/* Enums */
typedef enum {
    PIN_ON_TOP, PIN_ON_LEFT, PIN_ON_BOTTOM, PIN_ON_RIGHT
} TFT_ORIENTATION;

/* Colors */
#define RGB888TO565(RGB888) (((RGB888 >> 8) & 0xF800) | ((RGB888 >> 5) & 0x07E0) | ((RGB888 >> 3) & 0x001F))

#define WHITE (RGB888TO565(0xFFFFFF))
#define BLACK (RGB888TO565(0x000000))
#define DARK_GREY (RGB888TO565(0x555555))
#define GREY (RGB888TO565(0xAAAAAA))
#define RED (RGB888TO565(0xFF0000))
#define DARK_RED (RGB888TO565(0x800000))
#define ORANGE (RGB888TO565(0xFF9900))
#define YELLOW (RGB888TO565(0xFFFF00))
#define GREEN (RGB888TO565(0x00FF00))
#define DARK_GREEN (RGB888TO565(0x00CC00))
#define BLUE (RGB888TO565(0x0000FF))
#define BLUE2 (RGB888TO565(0x202060))
#define SKY_BLUE (RGB888TO565(0x11CFFF))
#define CYAN (RGB888TO565(0x8888FF))
#define PURPLE (RGB888TO565(0x00AAAA))
#define PINK (RGB888TO565(0xC71585))
#define GRAYSCALE(S) (2113 * S)

/* Pixels */
#define CHAR_WIDTH 8
#define CHAR_HEIGHT 16

/* Dimensions */
#ifdef MODEL_ILI9486  // 3.2 inch
#define SCREEN_CHOSEN
#define MAX_WIDTH 320
#define MAX_HEIGHT 480

#define PIXEL_BYTES 3

#define CHAR_MAX_X_VERTICAL 40
#define CHAR_MAX_Y_VERTICAL 30

#define CHAR_MAX_X_HORIZONTAL 60
#define CHAR_MAX_Y_HORIZONTAL 20

#define CHAR_MAX_X 60  // max between CHAR_MAX_X_VERTICAL and CHAR_MAX_X_HORIZONTAL
#define CHAR_MAX_Y 30  // max between CHAR_MAX_Y_VERTICAL and CHAR_MAX_Y_HORIZONTAL

#endif

#ifdef MODEL_ILI9341  // 2.8 inch
#define SCREEN_CHOSEN
#define MAX_WIDTH 240
#define MAX_HEIGHT 320

#define PIXEL_BYTES 2

#define CHAR_MAX_X_VERTICAL 30
#define CHAR_MAX_Y_VERTICAL 20

#define CHAR_MAX_X_HORIZONTAL 40
#define CHAR_MAX_Y_HORIZONTAL 15

#define CHAR_MAX_X 40  // max between CHAR_MAX_X_VERTICAL and CHAR_MAX_X_HORIZONTAL
#define CHAR_MAX_Y 20  // max between CHAR_MAX_Y_VERTICAL and CHAR_MAX_Y_HORIZONTAL

#endif

#if defined(MODEL_ST7735) || defined(MODEL_ST7735S)  // 1.8 inch
#define SCREEN_CHOSEN
#define MAX_WIDTH 128
#define MAX_HEIGHT 160

#define PIXEL_BYTES 2

#define CHAR_MAX_X_VERTICAL 16
#define CHAR_MAX_Y_VERTICAL 10

#define CHAR_MAX_X_HORIZONTAL 20
#define CHAR_MAX_Y_HORIZONTAL 8

#define CHAR_MAX_X 20  // max between CHAR_MAX_X_VERTICAL and CHAR_MAX_X_HORIZONTAL
#define CHAR_MAX_Y 10  // max between CHAR_MAX_Y_VERTICAL and CHAR_MAX_Y_HORIZONTAL

#endif

#ifndef SCREEN_CHOSEN
#error "You must choose which screen you are using at the top"
#endif

/* Structs */
typedef struct {
    uint8_t curr_screen;

    // each of them save 2 buffer, current screen and next screen
    char text_buf[2][CHAR_MAX_X_VERTICAL * CHAR_MAX_Y_VERTICAL];
    uint16_t text_color_buf[2][CHAR_MAX_X_VERTICAL * CHAR_MAX_Y_VERTICAL];
    uint16_t bg_color_buf[2][CHAR_MAX_X_VERTICAL * CHAR_MAX_Y_VERTICAL];
} TFTBuffer_STRUCT, *TFTBuffer;
// type name of struct and type name of struct pointer

/* Extern variables */
// TFT intrinsics
extern uint8_t tft_orientation;
extern uint16_t curr_bg_color;
extern uint16_t curr_text_color;
extern uint16_t curr_text_color_sp;
extern uint16_t curr_highlight_color;
extern uint8_t char_max_x, char_max_y;

// Buffers
extern TFTBuffer_STRUCT default_tft_screens;
extern TFTBuffer tft_screens;

/* Macro */
#define TFT_XY(x, y) ((y)*char_max_x + (x))  // 2D to 1D index

// Useful function to improve performance
static inline bool tft_char_is_changed(const TFTBuffer buf, uint8_t x,
        uint8_t y) {
    const uint16_t idx = TFT_XY(x, y);
    return ((buf->text_buf[buf->curr_screen][idx]
            != buf->text_buf[!buf->curr_screen][idx])
            || (buf->text_color_buf[buf->curr_screen][idx]
                    != buf->text_color_buf[!buf->curr_screen][idx])
            || (buf->bg_color_buf[buf->curr_screen][idx]
                    != buf->bg_color_buf[!buf->curr_screen][idx]));
}

/* Display properties configuration */
void tft_init(TFT_ORIENTATION orientation, uint16_t bg_color,
        uint16_t text_color, uint16_t text_color_sp, uint16_t highlight_color); //, DISPLAY_MODE mode);
void tft_set_bg_color(uint16_t bg_color);
void tft_set_text_color(uint16_t text_color);
void tft_set_highlight_color(uint16_t highlight_color);
void tft_set_special_color(uint16_t text_color_sp);

/* Pixel printing */
void tft_force_clear(void);
void tft_print_rectangle(uint16_t color, uint32_t x, uint32_t y, uint32_t w,
        uint32_t h);
void tft_print_pixel(uint16_t color, uint32_t x, uint32_t y);
void tft_print_image(void *buf, uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void tft_print_image565(uint16_t **image, uint16_t x, uint16_t y, uint16_t w,
        uint16_t h);

/* Text buffer printing */
void tft_print_colored(uint8_t x, uint8_t y, const char *fp,
        uint16_t text_color, uint16_t bg_color);
void tft_printc(uint8_t x, uint8_t y, const char *fp);
/* The mini printf does not support the l length modifier. Use %u/%x for
   32-bit values; %lu/%lx would print a literal letter instead. */
void tft_prints(uint8_t x, uint8_t y, const char *fmt, ...) __attribute__((format(printf, 3, 4)));
void tft_printi(uint8_t x, uint8_t y, int32_t num);
void tft_printl(uint8_t x, uint8_t y, int64_t num);
void tft_printu(uint8_t x, uint8_t y, uint32_t num);
void tft_printf(uint8_t x, uint8_t y, float num, uint32_t dp);
uint8_t tft_update(uint32_t period);
uint8_t tft_update2(uint32_t period);

#endif /* __LCD_MAIN_H */
