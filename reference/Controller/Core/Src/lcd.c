#include "lcd/lcd.h"

#include "lcd/lcd_font.h"
#include "lcd/lcd_init.h"
#include "lcd/strhelper.h"
#include "main.h"

/* GPIO configuration */
#if (!defined(TFT_RST_GPIO_Port) && !defined(TFT_RST_Pin)) && (defined(TFT_RES_GPIO_Port) && defined(TFT_RES_Pin))
#define TFT_RST_GPIO_Port TFT_RES_GPIO_Port
#define TFT_RST_Pin TFT_RES_Pin
#endif

/* Private data */
uint16_t curr_bg_color = BLACK;
uint16_t curr_highlight_color = BLACK;
uint16_t curr_text_color = BLACK;
uint16_t curr_text_color_sp = BLACK;
uint8_t tft_orientation = 0, tft_enabled = 1;
uint8_t char_max_x, char_max_y;

TFTBuffer_STRUCT default_tft_screens = { 0 };
TFTBuffer tft_screens = &default_tft_screens;

#define TFT_COLOR_PALETTE_SIZE 32U
static uint16_t tft_color_palette[TFT_COLOR_PALETTE_SIZE] = { BLACK };
static uint8_t tft_color_palette_count = 1U;

#ifdef MODEL_ST7735
static uint8_t col_shift;
static uint8_t row_shift;
#endif

/* Macros that make life easier */
#define curr_screen tft_screens->curr_screen
#define curr_text_buf tft_screens->text_buf[curr_screen]
#define next_text_buf tft_screens->text_buf[!curr_screen]
#define curr_text_color_buf tft_screens->text_color_buf[curr_screen]
#define next_text_color_buf tft_screens->text_color_buf[!curr_screen]
#define curr_bg_color_buf tft_screens->bg_color_buf[curr_screen]
#define next_bg_color_buf tft_screens->bg_color_buf[!curr_screen]

/* Defines */
#define CHAR_PIXELS CHAR_WIDTH* CHAR_HEIGHT
#define CHAR_BYTES CHAR_PIXELS* PIXEL_BYTES

#if defined(MODEL_ILI9486)
#define THREADED_TFT_BUF_LEN (7)
#elif defined(MODEL_ILI9341)
#define THREADED_TFT_BUF_LEN (21)
#elif defined(MODEL_ST7789)
#define THREADED_TFT_BUF_LEN (3) /* 384 pixels: at least one 320-pixel row. */
#elif defined(MODEL_ST7735) || defined(MODEL_ST7735S)
#define THREADED_TFT_BUF_LEN (2) /* Two 512-byte buffers fit the F103C6 RAM. */
#endif

#define TFT_DMA_BUF_PIXELS (CHAR_PIXELS * THREADED_TFT_BUF_LEN)
#define TFT_DMA_BUF_SIZE (CHAR_BYTES * THREADED_TFT_BUF_LEN)

/* Internal variables */
uint8_t buf_ptr = 0;
static uint8_t tft_dma_bufs[2][TFT_DMA_BUF_SIZE];
#define curr_tft_dma_buf tft_dma_bufs[buf_ptr]

static uint8_t tft_color_index(uint16_t color) {
    uint8_t index;

    for (index = 0U; index < tft_color_palette_count; ++index) {
        if (tft_color_palette[index] == color)
            return index;
    }

    if (tft_color_palette_count < TFT_COLOR_PALETTE_SIZE) {
        index = tft_color_palette_count++;
        tft_color_palette[index] = color;
        return index;
    }

    return 0U;
}

/* TFT SPI communication - with MCU */
static inline void write_command(uint8_t command) {
    while (HAL_SPI_GetState(&TFT_SPI) != HAL_SPI_STATE_READY)
        // wait for the spi to be ready
        ;

    HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_RESET); // Data-Command Pin 0-Command 1-Data
    if (HAL_SPI_Transmit(&TFT_SPI, &command, 1, 10) != HAL_OK)
        Error_Handler();
    HAL_GPIO_WritePin(TFT_DC_GPIO_Port, TFT_DC_Pin, GPIO_PIN_SET);
}
static inline void write_data(uint8_t *data, uint16_t size) {
    if (HAL_SPI_Transmit(&TFT_SPI, data, size, 100) != HAL_OK)
        Error_Handler();
}
static inline void write_many(uint8_t command, uint8_t *data, uint16_t size) {
    write_command(command);
    write_data(data, size);
}
static inline void write_many_dma(uint8_t command, uint8_t *data, uint16_t size) {
    write_command(command);
    /* SPI DMA is not configured on this controller. Send a bounded chunk. */
    write_data(data, size);
}
static inline void write_byte(uint8_t command, uint8_t data) {
    write_command(command);
    write_data(&data, 1);
}
static inline void write_2hword(uint8_t command, uint16_t a, uint16_t b) {
    write_command(command);
    uint8_t buf[4] = { a >> 8, a & 0xFF, b >> 8, b & 0xFF };
    write_data(buf, 4);
}

/**
 * @brief Clear the whole text buffer
 *
 */
static inline void tft_clear(void) {
    for (uint8_t y = 0; y < char_max_y; y++) {
        for (uint8_t x = 0; x < char_max_x; x++) {
            curr_text_buf[TFT_XY(x, y)] = ' ';
        }
    }
}

/**
 * @brief Clear the whole text buffer and color buffers
 *
 */
static inline void tft_clear_full(void) {
    uint8_t text_color_index = tft_color_index(curr_text_color);
    uint8_t bg_color_index = tft_color_index(curr_bg_color);

    for (uint8_t y = 0; y < char_max_y; y++) {
        for (uint8_t x = 0; x < char_max_x; x++) {
            uint16_t idx = TFT_XY(x, y);
            curr_text_buf[idx] = ' ';
            curr_text_color_buf[idx] = text_color_index;
            curr_bg_color_buf[idx] = bg_color_index;
        }
    }
}

static inline void tft_set_region(uint16_t x, uint16_t y, uint16_t w,
        uint16_t h) {
    uint16_t startx = x;
    uint16_t starty = y;
    uint16_t endx = x + w;
    uint16_t endy = y + h;

#ifdef MODEL_ST7735
    startx += col_shift;
    starty += row_shift;
    endx += col_shift;
    endy += row_shift;
#endif

    write_2hword(0x2a, startx, endx);  // Column addr set
    write_2hword(0x2b, starty, endy);  // Row addr set
}

/**
 * @brief  Initialization of TFT
 * @param  orientation: default orientation
 * @param  bg_color: default background color
 * @param  text_color: default text color
 * @param  text_color_sp: default special text color
 * @param  highlight_color: default highlight color
 */
void tft_init(TFT_ORIENTATION orientation, uint16_t bg_color,
        uint16_t text_color, uint16_t text_color_sp, uint16_t highlight_color) {
    curr_screen = 0;
    if ((unsigned)orientation > PIN_ON_RIGHT)
        orientation = PIN_ON_TOP;
    tft_orientation = orientation;
    char_max_x = (orientation % 2) ? CHAR_MAX_X_HORIZONTAL : CHAR_MAX_X_VERTICAL;
    char_max_y = (orientation % 2) ? CHAR_MAX_Y_HORIZONTAL : CHAR_MAX_Y_VERTICAL;
    HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(TFT_RST_GPIO_Port, TFT_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(TFT_RST_GPIO_Port, TFT_RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(TFT_RST_GPIO_Port, TFT_RST_Pin, GPIO_PIN_SET);
    HAL_Delay(100);

    HAL_GPIO_WritePin(TFT_BL_GPIO_Port, TFT_BL_Pin, GPIO_PIN_SET);


    uint32_t i = 0;
    while (tft_init_code[++i] != TFT_EOF_MARKER) {
        if (tft_init_code[i] == TFT_ORIENTATION_CMD) {
            write_byte(tft_init_code[i],
                    tft_orientation_init_code[tft_orientation]);
            i++;
        } else if (tft_init_code[i + 1] == TFT_DELAY_MARKER) {
            write_command(tft_init_code[i]);
            HAL_Delay(tft_init_code[i + 2]);
            i += 3;
        } else if (tft_init_code[i + 1] == TFT_EOL_MARKER) {
            write_command(tft_init_code[i]);
            i++;
        } else {
            int len;
            for (len = 0; tft_init_code[i + len + 1] != TFT_EOL_MARKER; len++) {
            }
            write_many(tft_init_code[i], (uint8_t*) &tft_init_code[i + 1], len);
            i += len + 1;
        }
    }

#ifdef MODEL_ST7735
    switch (tft_orientation) {
    default:
    case 0:
        col_shift = 2;
        row_shift = 1;
        break;
    case 1:
        col_shift = 1;
        row_shift = 2;
        break;
    case 2:
        col_shift = 2;
        row_shift = 2;
        break;
    case 3:
        col_shift = 1;
        row_shift = 2;
        break;
    }
#endif

    tft_set_bg_color(bg_color);
    tft_set_text_color(text_color);
    tft_set_special_color(text_color_sp);
    tft_set_highlight_color(highlight_color);

    tft_force_clear();
}

/**
 * @brief Set current background color
 *
 * @param bg_color (BLACK, BLUE, RED, ...)
 */
void tft_set_bg_color(uint16_t bg_color) {
    curr_bg_color = bg_color;
}

/**
 * @brief Set current highlight color
 *
 * @param highlight_color (YELLOW, ORANGE, CYAN, ...)
 */
void tft_set_highlight_color(uint16_t highlight_color) {
    curr_highlight_color = highlight_color;
}

/**
 * @brief Set current text color
 *
 * @param text_color (WHITE, SKYBLUE, GREEN, ...)
 */
void tft_set_text_color(uint16_t text_color) {
    curr_text_color = text_color;
}

/**
 * @brief Set current special text color
 *
 * @param text_color_sp (YELLOW, ORANGE, CYAN, ...)
 */
void tft_set_special_color(uint16_t text_color_sp) {
    curr_text_color_sp = text_color_sp;
}

/**
 * @brief  Clear every pixels on the screen
 */
void tft_force_clear(void) {
    tft_clear_full();
    tft_update(0);
    tft_clear_full();
    if (tft_orientation % 2)
        tft_print_rectangle(curr_bg_color, 0, 0, MAX_HEIGHT, MAX_WIDTH);
    else
        tft_print_rectangle(curr_bg_color, 0, 0, MAX_WIDTH, MAX_HEIGHT);
}

/**
 * @brief Print character(s) at certain position with additional formatting
 *
 * @param x starting x-coordinate
 * @param y starting y-coordinate
 * @param fp pointer to the character(s)
 */
void tft_print_colored(uint8_t x, uint8_t y, const char *fp,
        uint16_t text_color, uint16_t bg_color) {
    uint8_t i = x;
    uint8_t j = y;
    uint8_t is_special = 0;
    uint8_t is_highlighted = 0;
    uint8_t is_underlined = 0;
    uint8_t text_color_index = tft_color_index(text_color);
    uint8_t special_color_index = tft_color_index(curr_text_color_sp);
    uint8_t bg_color_index = tft_color_index(bg_color);
    uint8_t highlight_color_index = tft_color_index(curr_highlight_color);

    while (*fp && i < char_max_x && j < char_max_y) {
        switch (*fp) {
        case '\n':
            j++;  // fall through
        case '\r':
            i = x;
            break;
        case '`': // escape character
            if (*(fp + 1) != '\0') {
                fp++;
                curr_text_buf[TFT_XY(i, j)] = ((*fp) | (is_underlined ? 0x80 : 0x00));
                curr_text_color_buf[TFT_XY(i, j)] = is_special ? special_color_index : text_color_index;
                curr_bg_color_buf[TFT_XY(i, j)] = is_highlighted ? highlight_color_index : bg_color_index;
                i++;
            }
            break;
        case '[':
        case ']':
            is_special = (*fp == '[');
            break;
        case '{':
        case '}':
            is_highlighted = (*fp == '{');
            break;
        case '|':
            is_underlined = !is_underlined;
            break;
        default:
            curr_text_buf[TFT_XY(i, j)] = ((*fp) | (is_underlined ? 0x80 : 0x00));
            curr_text_color_buf[TFT_XY(i, j)] = is_special ? special_color_index : text_color_index;
            curr_bg_color_buf[TFT_XY(i, j)] = is_highlighted ? highlight_color_index : bg_color_index;
            i++;
            break;
        }
        fp++;
    }
}

/**
 * @brief Print character(s) at certain position
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * @param fp pointer to character
 */
void tft_printc(uint8_t x, uint8_t y, const char *fp) {
    tft_print_colored(x, y, fp, curr_text_color, curr_bg_color);
}

/**
 * @brief Print a string at certain position, wrap with [] for special words, wrap with {} for highlight, wrap with |
 * for underline, prefix with ` to escape the abovementioned characters
 * @param x starting x-coordinate
 * @param y starting y-coordinate
 * @param fmt string to be printed with format
 * @param __VA_ARGS__ variables to replace spaceholders
 */
void tft_prints(uint8_t x, uint8_t y, const char *fmt, ...) {
    char buf[CHAR_MAX_X * 2 + 1] = { 0 };

    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);

    tft_printc(x, y, buf);
}

/**
 * @brief Print a signed integer at certain position
 *
 * @param x starting x-coordinate
 * @param y starting y-coordinate
 * @param num the integer
 */
void tft_printi(uint8_t x, uint8_t y, int32_t num) {
    char buf[12] = { 0 };

    itos(buf, num);

    tft_printc(x, y, buf);
}

/**
 * @brief Print a signed long at certain position
 *
 * @param x starting x-coordinate
 * @param y starting y-coordinate
 * @param num the long
 */
void tft_printl(uint8_t x, uint8_t y, int64_t num) {
    char buf[21] = { 0 };

    ltos(buf, num);

    tft_printc(x, y, buf);
}

/**
 * @brief Print a unsigned integer at certain position
 *
 * @param x starting x-coordinate
 * @param y starting y-coordinate
 * @param num the integer
 */
void tft_printu(uint8_t x, uint8_t y, uint32_t num) {
    char buf[12] = { 0 };

    utos(buf, num);

    tft_printc(x, y, buf);
}

/**
 * @brief Print a float at certain position
 *
 * @param x starting x-coordinate
 * @param y starting y-coordinate
 * @param num the float
 * @param dp decimal places
 */
void tft_printf(uint8_t x, uint8_t y, float num, uint32_t dp) {
    char buf[40] = {0};

    ftos(buf, num, dp > 6U ? 6U : dp);

    tft_printc(x, y, buf);
}

static inline void tft_buffer_pixel(uint8_t *out, uint16_t rgb565) {
#if PIXEL_BYTES == 3  // Expand RGB565 source colors to RGB666 transfers.
    out[0] = (rgb565 & 0xF800) >> (11 - 3);
    out[1] = (rgb565 & 0x7E0) >> (5 - 2);
    out[2] = (rgb565 & 0x1F) << 3;
#else
    out[0] = rgb565 >> 8;
    out[1] = rgb565;
#endif
}

static inline void tft_buffer_pixels(uint8_t *out, uint16_t rgb565,
        uint32_t len) {
    uint8_t buf[PIXEL_BYTES];
    tft_buffer_pixel(buf, rgb565);
    while (len--) {
        *out++ = buf[0];
        *out++ = buf[1];
#if PIXEL_BYTES == 3
        *out++ = buf[2];
#endif
    }
}

void tft_print_rectangle_dma(uint16_t color, uint32_t x, uint32_t y, uint32_t w,
        uint32_t h) {
    uint32_t width = (tft_orientation % 2) ? MAX_HEIGHT : MAX_WIDTH;
    uint32_t height = (tft_orientation % 2) ? MAX_WIDTH : MAX_HEIGHT;
    if (x >= width || y >= height || w == 0 || h == 0) return;
    if (w > width - x) w = width - x;
    if (h > height - y) h = height - y;
    uint32_t i = w * h;
    int32_t l = (i > TFT_DMA_BUF_PIXELS) ? TFT_DMA_BUF_PIXELS : i; // safety guard
    tft_buffer_pixels(curr_tft_dma_buf, color, l);
    tft_set_region(x, y, w - 1, h - 1);
    write_command(0x2c);
    while (HAL_SPI_GetState(&TFT_SPI) != HAL_SPI_STATE_READY)
        ;
    write_many_dma(0x2c, curr_tft_dma_buf, l * PIXEL_BYTES);
    buf_ptr ^= 0x1;
}

/**
 * @brief Print a rectangle at certain position
 *
 * @param color (RED, GREEN, PINK, ...)
 * @param x starting x-coordinate
 * @param y starting y-coordinate
 * @param w width
 * @param h height
 */
void tft_print_rectangle(uint16_t color, uint32_t x, uint32_t y, uint32_t w,
        uint32_t h) {
    uint32_t width = (tft_orientation % 2) ? MAX_HEIGHT : MAX_WIDTH;
    uint32_t height = (tft_orientation % 2) ? MAX_WIDTH : MAX_HEIGHT;
    if (x >= width || y >= height || w == 0 || h == 0) return;
    if (w > width - x) w = width - x;
    if (h > height - y) h = height - y;
    uint32_t i = w * h;
    if (i <= (64)) {
        uint8_t buf[PIXEL_BYTES];
        tft_buffer_pixel(buf, color);

        tft_set_region(x, y, w - 1, h - 1);
        write_command(0x2c);
        for (; i != 0; i--) {
            write_data(buf, PIXEL_BYTES);
        }
    } else {
        // max no. of rows that can fit in the dma buffer
        uint16_t buf_max_h = TFT_DMA_BUF_PIXELS / w;
        uint16_t num_section = h / buf_max_h;
        for (int k = 0; k < num_section; ++k) {
            tft_print_rectangle_dma(color, x, y + k * buf_max_h, w, buf_max_h);
        }
        if (h % buf_max_h > 0) {
            tft_print_rectangle_dma(color, x, y + num_section * buf_max_h, w,
                    h % buf_max_h);
        }
    }
}

/**
 * @brief Print single colored pixel at certain position
 *
 * @param color (WHITE, YELLOW, DARK_GREEN, ...)
 * @param x x-coordinate
 * @param y y-coordinate
 */
void tft_print_pixel(uint16_t color, uint32_t x, uint32_t y) {
    uint32_t width = (tft_orientation % 2) ? MAX_HEIGHT : MAX_WIDTH;
    uint32_t height = (tft_orientation % 2) ? MAX_WIDTH : MAX_HEIGHT;
    if (x >= width || y >= height) return;
    tft_set_region(x, y, 0, 0);

    uint8_t buf[PIXEL_BYTES];

    tft_buffer_pixel(buf, color);

    write_many(0x2c, buf, PIXEL_BYTES);
}

/**
 * @brief Print an image buffer at certain position
 *
 * @param buf image buffer (RGB565 stored in 2 bytes)
 * @param x starting x-coordinate
 * @param y starting y-coordinate
 * @param w width
 * @param h height
 */
void tft_print_image(void *buf, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
    uint32_t width = (tft_orientation % 2) ? MAX_HEIGHT : MAX_WIDTH;
    uint32_t height = (tft_orientation % 2) ? MAX_WIDTH : MAX_HEIGHT;
    if (!buf || x >= width || y >= height || !w || !h ||
        w > width - x || h > height - y || w * h > UINT16_MAX / PIXEL_BYTES) return;
    while (HAL_SPI_GetState(&TFT_SPI) != HAL_SPI_STATE_READY)
        ;  // wait for the SPI to be ready

    tft_set_region(x, y, w - 1, h - 1);

    write_many_dma(0x2c, buf, w * h * PIXEL_BYTES);
}

void tft_print_image565(uint16_t **image, uint16_t x, uint16_t y, uint16_t w,
        uint16_t h) {
    uint32_t width = (tft_orientation % 2) ? MAX_HEIGHT : MAX_WIDTH;
    uint32_t height = (tft_orientation % 2) ? MAX_WIDTH : MAX_HEIGHT;
    if (!image || x >= width || y >= height || !w || !h) return;
    if (w > width - x) w = width - x;
    if (h > height - y) h = height - y;
    uint8_t row[MAX_HEIGHT * PIXEL_BYTES];
    for (uint16_t j = 0; j < h; ++j) {
        for (uint16_t i = 0; i < w; ++i) {
            tft_buffer_pixel(&row[i * PIXEL_BYTES], image[i][j]);
        }
        tft_print_image(row, x, y + j, w, 1);
    }
}

/**
 * @brief Update the screen in certain period
 *
 * @param period time in ms
 * @return state
 */
uint8_t tft_update(uint32_t period) {
    static uint32_t last_update = 0;
    if ((HAL_GetTick() - last_update) < period)
        return 2;
    last_update = HAL_GetTick();

    for (uint8_t j = 0; j < char_max_y; j++) {
        for (uint8_t i = 0; i < char_max_x; i++) {
            if (tft_char_is_changed(tft_screens, i, j)) {
                uint8_t adj_cnt = 1;
                while ((i + adj_cnt < char_max_x)
                        && tft_char_is_changed(tft_screens, i + (adj_cnt), j)
                        && (adj_cnt < THREADED_TFT_BUF_LEN))
                    adj_cnt++;  // Search for diff char

                uint16_t px = 0;
                uint16_t y = 0;
                while (y < CHAR_HEIGHT) {
                    uint8_t char_cnt = 0;
                    while (char_cnt != adj_cnt) {
                        const uint8_t char_ptr = (CHAR_PTR(
                                curr_text_buf[TFT_XY(i + char_cnt, j)]))[y];
                        uint16_t fg = tft_color_palette[curr_text_color_buf[TFT_XY(i + char_cnt, j)]];
                        uint16_t bg = tft_color_palette[curr_bg_color_buf[TFT_XY(i + char_cnt, j)]];
                        for (uint8_t x = CHAR_WIDTH; x > 0; x--) {
                            uint16_t color =
                                    ((char_ptr >> (x - 1)) & 0x01) ? fg : bg;
                            tft_buffer_pixel(&tft_dma_bufs[buf_ptr][px], color);
                            px += PIXEL_BYTES;
                        }
                        char_cnt++;
                    }
                    y++;
                }

                tft_print_image(&tft_dma_bufs[buf_ptr][0], i * CHAR_WIDTH,
                        j * CHAR_HEIGHT, adj_cnt * CHAR_WIDTH,
                        CHAR_HEIGHT);
                buf_ptr ^= 0x1;
                i += adj_cnt - 1;
            }
        }
    }

    // Swap pointers
    curr_screen = !curr_screen;

    tft_clear();

    return 0;
}

uint8_t tft_update2(uint32_t period) {
    static enum TFT_UPDATE_STATE {
        TFT_IDLE, TFT_BUFFERING_PIXELS, TFT_WAITING_DMA,
    } state = 0;

    static uint8_t chari = 0, charj = 0;
    static uint8_t adj_cnt;
    static uint32_t last_update = 0;
    switch (state) {
    default:
    case TFT_IDLE:
        if ((HAL_GetTick() - last_update) < period) {
            return 2;
        } else {
            state = TFT_BUFFERING_PIXELS;
            last_update += period;
            return 0;
        }
        // Fall-through
    case TFT_BUFFERING_PIXELS:
        for (; charj < char_max_y; charj++) {
            for (; chari < char_max_x; chari++) {
                if (tft_char_is_changed(tft_screens, chari, charj)) {
                    adj_cnt = 1;
                    while ((chari + adj_cnt < char_max_x)
                            && tft_char_is_changed(tft_screens,
                                    chari + (adj_cnt), charj)
                            && (adj_cnt < THREADED_TFT_BUF_LEN))
                        adj_cnt++;  // Search for diff char

                    uint16_t px = 0;
                    uint16_t y = 0;
                    while (y < CHAR_HEIGHT) {
                        uint8_t char_cnt = 0;
                        while (char_cnt != adj_cnt) {
                            const uint8_t char_ptr =
                                    (CHAR_PTR(
                                            curr_text_buf[TFT_XY(chari + char_cnt, charj)]))[y];
                            uint16_t fg = tft_color_palette[curr_text_color_buf[TFT_XY(chari + char_cnt, charj)]];
                            uint16_t bg = tft_color_palette[curr_bg_color_buf[TFT_XY(chari + char_cnt, charj)]];
                            for (uint8_t x = CHAR_WIDTH; x > 0; x--) {
                                uint16_t color =
                                        ((char_ptr >> (x - 1)) & 0x01) ?
                                                fg : bg;
                                tft_buffer_pixel(&tft_dma_bufs[buf_ptr][px],
                                        color);
                                px += PIXEL_BYTES;
                            }
                            char_cnt++;
                        }
                        y++;
                    }

                    state = TFT_WAITING_DMA;
                    break;
                }
            }
            if (state == TFT_WAITING_DMA)
                break;
            else
                chari = 0;
        }
        if (state != TFT_WAITING_DMA) {
            chari = 0;
            charj = 0;
            curr_screen ^= 0x1;
            tft_clear();
            state = TFT_IDLE;
            return 3;
        }
        // Fall-through
    case TFT_WAITING_DMA:
        if (HAL_SPI_GetState(&TFT_SPI) == HAL_SPI_STATE_READY) {
            tft_print_image(&tft_dma_bufs[buf_ptr][0], chari * CHAR_WIDTH,
                    charj * CHAR_HEIGHT, adj_cnt * CHAR_WIDTH, CHAR_HEIGHT);
            buf_ptr ^= 0x1;
            chari += adj_cnt;
            state = TFT_BUFFERING_PIXELS;
            return 1;
        } else
            return 1;
    }
    return 1;
}
