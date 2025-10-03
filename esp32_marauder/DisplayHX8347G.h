// esp32_marauder/DisplayHX8347G.h
#pragma once
#include <Arduino.h>
#include <LCDWIKI_KBV.h>

#ifndef HX8347G
#define HX8347G 4
#endif

class DisplayHX8347G {
public:
	DisplayHX8347G();
	bool begin();
	void init();                         // TFT_eSPI compat

	void setRotation(uint8_t r);
	uint8_t getRotation() const;         // TFT_eSPI compat

	uint16_t width() const;
	uint16_t height() const;

	void fillScreen(uint16_t c);
	void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
	void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c);
	void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c);
	void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t c);
	void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t c);

	void setTextColor(uint16_t fg);
	void setTextColor(uint16_t fg, uint16_t bg);
	void setTextSize(uint8_t s);
	void setCursor(int16_t x, int16_t y);
	void setTextWrap(bool enable);       // TFT_eSPI compat (no-op)
	void setFreeFont(const void* f);     // TFT_eSPI compat (no-op)
	void setTextDatum(uint8_t datum);    // TFT_eSPI compat (stores, used by drawCentreString)

	// Text APIs used by Marauder
	void print(const String& s);
	void println(const String& s);
	void drawString(const char* t, int16_t x, int16_t y);
	void drawCentreString(const char* t, int16_t x, int16_t y, int /*font*/);

	// Bitmap + image
	void drawXBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color);
	void pushImage(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t* d);

private:
	LCDWIKI_KBV _tft;
	int16_t _cursorX, _cursorY;
	uint8_t _datum;
	bool _wrap;
};