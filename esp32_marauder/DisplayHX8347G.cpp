// esp32_marauder/DisplayHX8347G.cpp
#include "DisplayHX8347G.h"

DisplayHX8347G::DisplayHX8347G()
    : _tft(HX8347G, 27, 4, 5, 33, 32), _cursorX(0), _cursorY(0), _datum(0), _wrap(false) {
}

bool DisplayHX8347G::begin() {
    _tft.Init_LCD();
    _tft.Fill_Screen(0xF800); delay(200);
    _tft.Fill_Screen(0x07E0); delay(200);
    _tft.Fill_Screen(0x001F); delay(200);
    _tft.Set_Text_Mode(0);
    _tft.Set_Text_Back_colour(0x0000);
    _tft.Set_Text_colour(0xFFFF);
    _tft.Set_Text_Size(2);
    _tft.Print_String((char*)"Marauder HX8347G", 10, 10);
    return true;
}

void DisplayHX8347G::init() { begin(); }

void DisplayHX8347G::setRotation(uint8_t r) { _tft.Set_Rotation(r & 3); }
uint8_t DisplayHX8347G::getRotation() const { return _tft.Get_Rotation(); }

uint16_t DisplayHX8347G::width() const { return (uint16_t)_tft.Get_Width(); }
uint16_t DisplayHX8347G::height() const { return (uint16_t)_tft.Get_Height(); }

void DisplayHX8347G::fillScreen(uint16_t c) { _tft.Fill_Screen(c); }

void DisplayHX8347G::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c) {
    if (w <= 0 || h <= 0) return;
    _tft.Set_Draw_color(c);
    _tft.Fill_Rectangle(x, y, x + w - 1, y + h - 1);
}

void DisplayHX8347G::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t c) {
    if (w <= 0 || h <= 0) return;
    _tft.Set_Draw_color(c);
    _tft.Draw_Rectangle(x, y, x + w - 1, y + h - 1);
}

void DisplayHX8347G::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t c) {
    if (w <= 0) return;
    _tft.Set_Draw_color(c);
    _tft.Draw_Fast_HLine(x, y, w);
}

void DisplayHX8347G::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t c) {
    if (h <= 0) return;
    _tft.Set_Draw_color(c);
    _tft.Draw_Fast_VLine(x, y, h);
}

void DisplayHX8347G::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t c) {
    _tft.Set_Draw_color(c);
    _tft.Draw_Line(x0, y0, x1, y1);
}

void DisplayHX8347G::setTextColor(uint16_t fg) { _tft.Set_Text_colour(fg); }
void DisplayHX8347G::setTextColor(uint16_t fg, uint16_t bg) { _tft.Set_Text_colour(fg); _tft.Set_Text_Back_colour(bg); }
void DisplayHX8347G::setTextSize(uint8_t s) { _tft.Set_Text_Size(s ? s : 1); }
void DisplayHX8347G::setCursor(int16_t x, int16_t y) { _cursorX = x; _cursorY = y; }
void DisplayHX8347G::setTextWrap(bool enable) { _wrap = enable; (void)_wrap; }
void DisplayHX8347G::setFreeFont(const void* /*f*/) {}

void DisplayHX8347G::setTextDatum(uint8_t datum) { _datum = datum; }

void DisplayHX8347G::print(const String& s) {
    _tft.Print_String((char*)s.c_str(), _cursorX, _cursorY);
}

void DisplayHX8347G::println(const String& s) {
    _tft.Print_String((char*)s.c_str(), _cursorX, _cursorY);
    _cursorY += 12 * _tft.Get_Text_Size(); // simple line advance
}

void DisplayHX8347G::drawString(const char* t, int16_t x, int16_t y) {
    if (!t) return;
    _tft.Print_String((char*)t, x, y);
}

void DisplayHX8347G::drawCentreString(const char* t, int16_t x, int16_t y, int /*font*/) {
    if (!t) return;
    uint8_t s = _tft.Get_Text_Size();
    int16_t w = (int16_t)(strlen(t) * 6 * s);
    int16_t cx = x - w / 2;
    _tft.Print_String((char*)t, cx, y);
}

void DisplayHX8347G::drawXBitmap(int16_t x, int16_t y, const uint8_t* bitmap, int16_t w, int16_t h, uint16_t color) {
    if (!bitmap || w <= 0 || h <= 0) return;
    _tft.Set_Draw_color(color);
    int16_t byteWidth = (w + 7) / 8;
    for (int16_t j = 0; j < h; j++) {
        for (int16_t i = 0; i < w; i++) {
            uint8_t byte = bitmap[j * byteWidth + i / 8];
            if (byte & (0x80 >> (i & 7))) {
                _tft.Draw_Pixe(x + i, y + j, color);
            }
        }
    }
}

void DisplayHX8347G::pushImage(int16_t x, int16_t y, int16_t w, int16_t h, const uint16_t* d) {
    if (w <= 0 || h <= 0 || !d) return;
    _tft.Set_Addr_Window(x, y, x + w - 1, y + h - 1);
    _tft.Push_Any_Color((uint16_t*)d, w * h, true, 0);
}

