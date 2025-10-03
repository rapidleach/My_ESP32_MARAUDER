#pragma once
#ifndef configs_h
#define configs_h

#define MARAUDER_V4
#define MARAUDER_VERSION "v1.8.7"

// ==================== MARAUDER_V4 CONFIG ====================

#ifdef MARAUDER_V4
  // --- Hardware features ---
#undef MENU_FONT
#define MENU_FONT NULL
#define HAS_TOUCH
#define HAS_BATTERY
#define HAS_BT
#define HAS_NEOPIXEL_LED
#define HAS_SCREEN
#define HAS_FULL_SCREEN
#define HAS_SD
#define USE_SD
#define HAS_TEMP_SENSOR
#define HAS_GPS
#define HARDWARE_NAME "Marauder v4"

// --- SD card ---
#define SD_CS 12

// --- Display definitions ---
#define SCREEN_CHAR_WIDTH 40
#define BANNER_TEXT_SIZE 2
#define TFT_WIDTH 240
#define TFT_HEIGHT 320
#define TFT_SHIELD
#define SCREEN_ORIENTATION 0
#define CHAR_WIDTH 12
#define SCREEN_WIDTH TFT_WIDTH
#define SCREEN_HEIGHT TFT_HEIGHT
#define TEXT_HEIGHT 16
#define BOT_FIXED_AREA 0
#define TOP_FIXED_AREA 48
#define YMAX 320
#define GRAPH_VERT_LIM (TFT_HEIGHT/2)
#define BUTTON_SCREEN_LIMIT 12
#define BUTTON_ARRAY_LEN BUTTON_SCREEN_LIMIT
#define STATUS_BAR_WIDTH 16
#define LVGL_TICK_PERIOD 6

// --- Menu definitions ---
#define BANNER_TIME 100
#define COMMAND_PREFIX "!"
#define KEY_X 120
#define KEY_Y 50
#define KEY_W 240
#define KEY_H 22
#define KEY_SPACING_X 0
#define KEY_SPACING_Y 1
#define KEY_TEXTSIZE 1
#define ICON_W 22
#define ICON_H 22
#define BUTTON_PADDING 22

// --- GPS pins ---
#define GPS_SERIAL_INDEX 2
#define GPS_TX 4
#define GPS_RX 13

// --- Battery I²C pins ---
#define I2C_SDA 33
#define I2C_SCL 22

// --- Title bytes ---
#define MARAUDER_TITLE_BYTES 13578

// --- Memory / buffer ---
#define MEM_LOWER_LIM 10000
#define BUF_SIZE 3 * 1024
#define SNAP_LEN 2324

// --- NeoPixel LED ---
#define PIN 25

#endif
// ==================== END MARAUDER_V4 CONFIG ====================

#endif // configs_h
