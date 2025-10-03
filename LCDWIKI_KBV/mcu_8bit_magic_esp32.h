#pragma once
#include <Arduino.h>

// D0..D7, CS, RS(CD), WR, RD, RST
static const int LCD_D[8] = { 13,14,16,17,21,22,25,26 };
static const int LCD_CS = 27;
static const int LCD_RS = 4;
static const int LCD_WR = 5;
static const int LCD_RD = 33;
static const int LCD_RST = 32;

#define CS_ACTIVE   digitalWrite(LCD_CS, LOW)
#define CS_IDLE     digitalWrite(LCD_CS, HIGH)
#define CD_COMMAND  digitalWrite(LCD_RS, LOW)
#define CD_DATA     digitalWrite(LCD_RS, HIGH)
#define WR_ACTIVE   digitalWrite(LCD_WR, LOW)
#define WR_IDLE     digitalWrite(LCD_WR, HIGH)
#define RD_ACTIVE   digitalWrite(LCD_RD, LOW)
#define RD_IDLE     digitalWrite(LCD_RD, HIGH)

#define WR_STROBE   do{ WR_ACTIVE; WR_IDLE; }while(0)
#define RD_STROBE   do{ RD_ACTIVE; RD_IDLE; }while(0)

static inline void setWriteDir() {
	for (int i = 0; i < 8; ++i) pinMode(LCD_D[i], OUTPUT);
	pinMode(LCD_CS, OUTPUT); pinMode(LCD_RS, OUTPUT);
	pinMode(LCD_WR, OUTPUT); pinMode(LCD_RD, OUTPUT);
	if (LCD_RST >= 0) pinMode(LCD_RST, OUTPUT);
	CS_IDLE; CD_DATA; WR_IDLE; RD_IDLE;
}

static inline void setReadDir() {
	for (int i = 0; i < 8; ++i) pinMode(LCD_D[i], INPUT);
	pinMode(LCD_RD, OUTPUT);
}

static inline void write8(uint8_t d) {
	for (int i = 0; i < 8; ++i) digitalWrite(LCD_D[i], (d >> i) & 1);
	WR_STROBE;
}

static inline void read8(uint8_t& d) {
	RD_ACTIVE; uint8_t v = 0;
	for (int i = 0; i < 8; ++i) v |= (digitalRead(LCD_D[i]) ? 1 : 0) << i;
	RD_IDLE; d = v;
}

#define write16(d)           do{ write8((uint8_t)((d)>>8)); write8((uint8_t)(d)); }while(0)
#define writeCmd8(x)         do{ CD_COMMAND; write8((uint8_t)(x)); CD_DATA; }while(0)
#define writeData8(x)        do{ CD_DATA; write8((uint8_t)(x)); }while(0)
#define writeCmd16(x)        do{ CD_COMMAND; write16((uint16_t)(x)); CD_DATA; }while(0)
#define writeData16(x)       do{ CD_DATA; write16((uint16_t)(x)); }while(0)
#define writeCmdData8(a,d)   do{ CD_COMMAND; write8((uint8_t)(a)); CD_DATA; write8((uint8_t)(d)); }while(0)
#define writeCmdData16(a,d)  do{ CD_COMMAND; write16((uint16_t)(a)); CD_DATA; write16((uint16_t)(d)); }while(0)

static inline void read16(uint16_t& d) {
	uint8_t hi, lo; read8(hi); read8(lo); d = (uint16_t(hi) << 8) | lo;
}