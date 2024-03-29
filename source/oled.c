/*
 * oled.c
 *
 *  Created on: 09.02.2019
 *      Author: daniel
 */


#include "oled.h"
#include <math.h>

I2C_Type *I2C_base=NULL;

const unsigned char LogoKI [] = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x60, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0xF0, 0xF8, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0xC0, 0xE0, 0xF0, 0xFC, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x1F, 0x0F, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x1F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0xF8, 0xF0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x1F, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF8, 0xF0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x0F, 0x3F, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xF8, 0xF0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x7F, 0x3F, 0x1F, 0x0F, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

};
const unsigned char FontSystem5x8[]=
{
		0x00,0x00,0x00,0x00,0x00, /* Space */
		0x00,0x00,0x4f,0x00,0x00, /* ! */
		0x00,0x07,0x00,0x07,0x00, /* " */
		0x14,0x7f,0x14,0x7f,0x14, /* # */
		0x24,0x2a,0x7f,0x2a,0x12, /* 0x */
		0x23,0x13,0x08,0x64,0x62, /* % */
		0x36,0x49,0x55,0x22,0x20, /* & */
		0x00,0x05,0x03,0x00,0x00, /* ' */
		0x00,0x1c,0x22,0x41,0x00, /* ( */
		0x00,0x41,0x22,0x1c,0x00, /* ) */
		0x14,0x08,0x3e,0x08,0x14, /* // */
		0x08,0x08,0x3e,0x08,0x08, /* + */
		0x50,0x30,0x00,0x00,0x00, /* , */
		0x08,0x08,0x08,0x08,0x08, /* - */
		0x00,0x60,0x60,0x00,0x00, /* . */
		0x20,0x10,0x08,0x04,0x02, /* / */
		0x3e,0x51,0x49,0x45,0x3e, /* 0 */
		0x00,0x42,0x7f,0x40,0x00, /* 1 */
		0x42,0x61,0x51,0x49,0x46, /* 2 */
		0x21,0x41,0x45,0x4b,0x31, /* 3 */
		0x18,0x14,0x12,0x7f,0x10, /* 4 */
		0x27,0x45,0x45,0x45,0x39, /* 5 */
		0x3c,0x4a,0x49,0x49,0x30, /* 6 */
		0x07,0x71,0x09,0x05,0x03, /* 7 */
		0x36,0x49,0x49,0x49,0x36, /* 8 */
		0x06,0x49,0x49,0x29,0x1e, /* 9 */
		0x00,0x36,0x36,0x00,0x00, /* : */
		0x00,0x56,0x36,0x00,0x00, /* ; */
		0x08,0x14,0x22,0x41,0x00, /* < */
		0x14,0x14,0x14,0x14,0x14, /* = */
		0x00,0x41,0x22,0x14,0x08, /* > */
		0x02,0x01,0x51,0x09,0x06, /* ? */
		0x3e,0x41,0x5d,0x55,0x1e, /* @ */
		0x7e,0x11,0x11,0x11,0x7e, /* A */
		0x7f,0x49,0x49,0x49,0x36, /* B */
		0x3e,0x41,0x41,0x41,0x22, /* C */
		0x7f,0x41,0x41,0x22,0x1c, /* D */
		0x7f,0x49,0x49,0x49,0x41, /* E */
		0x7f,0x09,0x09,0x09,0x01, /* F */
		0x3e,0x41,0x49,0x49,0x7a, /* G */
		0x7f,0x08,0x08,0x08,0x7f, /* H */
		0x00,0x41,0x7f,0x41,0x00, /* I */
		0x20,0x40,0x41,0x3f,0x01, /* J */
		0x7f,0x08,0x14,0x22,0x41, /* K */
		0x7f,0x40,0x40,0x40,0x40, /* L */
		0x7f,0x02,0x0c,0x02,0x7f, /* M */
		0x7f,0x04,0x08,0x10,0x7f, /* N */
		0x3e,0x41,0x41,0x41,0x3e, /* O */
		0x7f,0x09,0x09,0x09,0x06, /* P */
		0x3e,0x41,0x51,0x21,0x5e, /* Q */
		0x7f,0x09,0x19,0x29,0x46, /* R */
		0x26,0x49,0x49,0x49,0x32, /* S */
		0x01,0x01,0x7f,0x01,0x01, /* T */
		0x3f,0x40,0x40,0x40,0x3f, /* U */
		0x1f,0x20,0x40,0x20,0x1f, /* V */
		0x3f,0x40,0x38,0x40,0x3f, /* W */
		0x63,0x14,0x08,0x14,0x63, /* X */
		0x07,0x08,0x70,0x08,0x07, /* Y */
		0x61,0x51,0x49,0x45,0x43, /* Z */
		0x00,0x7f,0x41,0x41,0x00, /* [ */
		0x02,0x04,0x08,0x10,0x20, /* \ */
		0x00,0x41,0x41,0x7f,0x00, /* ] */
		0x04,0x02,0x01,0x02,0x04, /* ^ */
		0x40,0x40,0x40,0x40,0x40, /* _ */
		0x00,0x00,0x03,0x05,0x00, /* ` */
		0x20,0x54,0x54,0x54,0x78, /* a */
		0x7F,0x44,0x44,0x44,0x38, /* b */
		0x38,0x44,0x44,0x44,0x44, /* c */
		0x38,0x44,0x44,0x44,0x7f, /* d */
		0x38,0x54,0x54,0x54,0x18, /* e */
		0x04,0x04,0x7e,0x05,0x05, /* f */
		0x08,0x54,0x54,0x54,0x3c, /* g */
		0x7f,0x08,0x04,0x04,0x78, /* h */
		0x00,0x44,0x7d,0x40,0x00, /* i */
		0x20,0x40,0x44,0x3d,0x00, /* j */
		0x7f,0x10,0x28,0x44,0x00, /* k */
		0x00,0x41,0x7f,0x40,0x00, /* l */
		0x7c,0x04,0x7c,0x04,0x78, /* m */
		0x7c,0x08,0x04,0x04,0x78, /* n */
		0x38,0x44,0x44,0x44,0x38, /* o */
		0x7c,0x14,0x14,0x14,0x08, /* p */
		0x08,0x14,0x14,0x14,0x7c, /* q */
		0x7c,0x08,0x04,0x04,0x00, /* r */
		0x48,0x54,0x54,0x54,0x24, /* s */
		0x04,0x04,0x3f,0x44,0x44, /* t */
		0x3c,0x40,0x40,0x20,0x7c, /* u */
		0x1c,0x20,0x40,0x20,0x1c, /* v */
		0x3c,0x40,0x30,0x40,0x3c, /* w */
		0x44,0x28,0x10,0x28,0x44, /* x */
		0x0c,0x50,0x50,0x50,0x3c, /* y */
		0x44,0x64,0x54,0x4c,0x44, /* z */
		0x08,0x36,0x41,0x41,0x00, /* { */
		0x00,0x00,0x77,0x00,0x00, /* | */
		0x00,0x41,0x41,0x36,0x08, /* } */
		0x08,0x08,0x2a,0x1c,0x08, /* <- */
		0x08,0x1c,0x2a,0x08,0x08, /* -> */
		0xff,0xff,0xff,0xff,0xff, /*  */
};
/*--------------------------------------------------------------------------------*/
static uint8_t s_chDispalyBuffer[128][8];
static uint8_t cmd_buff[2];
/*--------------------------------------------------------------------------------*/
void OLED_Write_Byte(uint8_t chData, uint8_t chCmd)
{
	cmd_buff[0] = chCmd ? 0x40 : 0x80;
	cmd_buff[1]=chData;
	if (kStatus_Success == I2C_MasterStart(I2C_base, I2C_MASTER_SLAVE_ADDR_7BIT, kI2C_Write))
		I2C_MasterWriteBlocking(I2C_base, &cmd_buff[0], 2, kI2C_TransferDefaultFlag);
}
/*--------------------------------------------------------------------------------*/
void OLED_Display_On(void)
{
	OLED_Write_Byte(0x8D, OLED_CMD);
	OLED_Write_Byte(0x14, OLED_CMD);
	OLED_Write_Byte(0xAF, OLED_CMD);
}
/*--------------------------------------------------------------------------------*/
void OLED_Display_Off(void)
{
	OLED_Write_Byte(0x8D, OLED_CMD);
	OLED_Write_Byte(0x10, OLED_CMD);
	OLED_Write_Byte(0xAE, OLED_CMD);
}
/*--------------------------------------------------------------------------------*/
void OLED_Refresh_Gram(void)
{
	for (uint8_t i = 0; i < 8; i ++) {
		OLED_Write_Byte(0xB0 + i, OLED_CMD);
		__SET_COL_START_ADDR();
		for (uint8_t j = 0; j < OLED_WIDTH; j ++) {
			OLED_Write_Byte(s_chDispalyBuffer[j][i], OLED_DAT);
		}
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Clear_Screen(uint8_t chFill)
{
	for (uint8_t i = 0; i < 8; i ++) {
		OLED_Write_Byte(0xB0 + i, OLED_CMD);
		__SET_COL_START_ADDR();
		for (uint8_t j = 0; j < OLED_WIDTH; j ++) {
			s_chDispalyBuffer[j][i] = chFill;
		}
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Draw_Point(uint8_t chXpos, uint8_t chYpos, uint8_t chPoint)
{
	uint8_t chPos, chBx, chTemp = 0;

	if (chXpos >= OLED_WIDTH || chYpos >= OLED_HEIGHT) {
		return;
	}
	chPos = chYpos / 8;
	chBx  = chYpos % 8;
	chTemp = 1 << (chBx);
	if (chPoint) {
		s_chDispalyBuffer[chXpos][chPos] |= chTemp;
	} else {
		s_chDispalyBuffer[chXpos][chPos] &= ~chTemp;
	}
}
/*--------------------------------------------------------------------------------*/
uint8_t OLED_Get_Point(uint8_t chXpos, uint8_t chYpos)
{
	uint8_t chPos, chBx, chTemp = 0;

	chPos = chYpos / 8;
	chBx  = chYpos % 8;
	chTemp = 1 << (chBx);

	return (s_chDispalyBuffer[chXpos][chPos] & chTemp) ? 1 : 0;
}
/*--------------------------------------------------------------------------------*/
void OLED_Draw_Line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t  x, y;
	int16_t addx, addy, dx, dy, P;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	x = x1;
	y = y1;
	addx = (x1 > x2) ? -1 : 1;
	addy = (y1 > y2) ? -1 : 1;

	if(dx >= dy){
		P = 2*dy - dx;
		for(int16_t i=0; i<=dx; i++){
			OLED_Draw_Point(x,y,1);
			if(P < 0){
				P += 2*dy;
				x += addx;
			}else{
				P += 2*(dy - dx);
				x += addx;
				y += addy;
			}
		}
	}else{
		P = 2*dx - dy;
		for(int16_t i=0; i<=dy; i++){
			OLED_Draw_Point(x,y,1);
			if(P < 0){
				P += 2*dx;
				y += addy;
			}else{
				P += 2*(dx - dy);
				x += addx;
				y += addy;
			}
		}
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Draw_Dotline(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	uint8_t  x, y;
	int16_t addx, addy, dx, dy, P;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);
	x = x1;
	y = y1;
	addx = (x1 > x2) ? -1 : 1;
	addy = (y1 > y2) ? -1 : 1;

	if(dx >= dy){
		P = 2*dy - dx;
		for(int16_t i=0; i<=dx; i++){
			OLED_Draw_Point(x,y,i%2);
			if(P < 0){
				P += 2*dy;
				x += addx;
			}else{
				P += 2*(dy - dx);
				x += addx;
				y += addy;
			}
		}
	}else{
		P = 2*dx - dy;
		for(int16_t i=0; i<=dy; i++){
			OLED_Draw_Point(x,y,i%2);
			if(P < 0){
				P += 2*dx;
				y += addy;
			}else{
				P += 2*(dx - dy);
				x += addx;
				y += addy;
			}
		}
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Draw_Circle(uint8_t x0, uint8_t y0, uint8_t radius)
{
	int16_t x = radius-1;
	int16_t y = 0;
	int16_t dx = 1;
	int16_t dy = 1;
	int16_t err = dx - (radius << 1);

	while (x >= y)
	{
		OLED_Draw_Point(x0 + x, y0 + y, 1);
		OLED_Draw_Point(x0 + y, y0 + x, 1);
		OLED_Draw_Point(x0 - y, y0 + x, 1);
		OLED_Draw_Point(x0 - x, y0 + y, 1);
		OLED_Draw_Point(x0 - x, y0 - y, 1);
		OLED_Draw_Point(x0 - y, y0 - x, 1);
		OLED_Draw_Point(x0 + y, y0 - x, 1);
		OLED_Draw_Point(x0 + x, y0 - y, 1);

		if (err <= 0)
		{
			y++;
			err += dy;
			dy += 2;
		}
		else
		{
			x--;
			dx += 2;
			err += dx - (radius << 1);
		}
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Draw_Circle2(uint8_t x0, uint8_t y0, uint8_t radius)
{
	int n=6.28*radius;
	for(int i=0; i<2*n;i++){

		OLED_Draw_Point(x0 + radius*sin(i/6.28), y0 + radius*cos(i/6.28), 1);
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Draw_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t chPoint)
{
	for (uint8_t i = x0; i <= x1; i++) {

		OLED_Draw_Point(i, y0, chPoint);
		OLED_Draw_Point(i, y1, chPoint);
	}
	for (uint8_t i = y0; i <= y1; i++) {

		OLED_Draw_Point(x0, i, chPoint);
		OLED_Draw_Point(x1, i, chPoint);
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Draw_Fill_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t chPoint)
{
	for (uint8_t i = x0; i <= x1; i++) {
		for (uint8_t j = y0; j <= y1; j++) {

			OLED_Draw_Point(i,j, chPoint);
		}
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Invert_Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	for (uint8_t i = x0; i <= x1; i++) {
		for (uint8_t j = y0; j <= y1; j++) {

			OLED_Draw_Point(i,j, !OLED_Get_Point(i, j));
		}
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Draw_Bitmap(const uint8_t *pchBmp)
{
	for (uint8_t i = 0; i < 8; i ++) {
		for (uint8_t j = 0; j < OLED_WIDTH; j ++) {
			s_chDispalyBuffer[j][i] = *pchBmp++;
		}
	}
	OLED_Refresh_Gram();
}
/*--------------------------------------------------------------------------------*/
void OLED_Puts(uint8_t x, uint8_t y, char *text)
{
	uint8_t i,j=0;
	char c;

	while(text[j] && j<21)
	{
		c=text[j]-32;
		for (i = 0; i < 5; i ++) {
			s_chDispalyBuffer[x+i+(6*j)][y] = FontSystem5x8[5*c+i];
		}
		s_chDispalyBuffer[x+i+(6*j)][y]=0;
		j++;
	}
}
/*--------------------------------------------------------------------------------*/
void OLED_Init(I2C_Type *base)
{
	I2C_base=base;
	// wait
	for(volatile int i=0; i<1000000; i++);


#if defined(SSD_1306)
	OLED_Write_Byte(0xAE, OLED_CMD);//--turn off oled panel
	OLED_Write_Byte(0x00, OLED_CMD);//--set low column address
	OLED_Write_Byte(0x10, OLED_CMD);//--set high column address
	OLED_Write_Byte(0x40, OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Write_Byte(0x20, OLED_CMD);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_Write_Byte(0x02, OLED_CMD);//
	OLED_Write_Byte(0x81, OLED_CMD);//--set contrast control register
	OLED_Write_Byte(0xCF, OLED_CMD);//--set SEG Output Current Brightness
	OLED_Write_Byte(0xA1, OLED_CMD);//--set SEG/Column Mapping
	OLED_Write_Byte(0xC8, OLED_CMD);//--set COM/Row Scan Direction (C0h / C8h)
	OLED_Write_Byte(0xA6, OLED_CMD);//--set normal display
	OLED_Write_Byte(0xA8, OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_Write_Byte(0x3F, OLED_CMD);//--set 1/64 duty
	OLED_Write_Byte(0xD3, OLED_CMD);//--set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Write_Byte(0x00, OLED_CMD);//-not offset
	OLED_Write_Byte(0xD5, OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_Write_Byte(0x80, OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_Write_Byte(0xD9, OLED_CMD);//--set pre-charge period
	OLED_Write_Byte(0xF1, OLED_CMD);//--set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write_Byte(0xDA, OLED_CMD);//--set com pins hardware configuration
	OLED_Write_Byte(0x12, OLED_CMD);
	OLED_Write_Byte(0xDB, OLED_CMD);//--set vcomh
	OLED_Write_Byte(0x40, OLED_CMD);//--set VCOM Deselect Level
	OLED_Write_Byte(0x8D, OLED_CMD);//--set Charge Pump enable/disable
	OLED_Write_Byte(0x14, OLED_CMD);//--set(0x10) disable
	OLED_Write_Byte(0xA4, OLED_CMD);// Disable Entire Display On (0xa4/0xa5)
	OLED_Write_Byte(0xA6, OLED_CMD);// Disable Inverse Display On (0xa6/a7)
	//OLED_Write_Byte(0xAF, OLED_CMD);//--turn on oled panel
#endif

#if defined(SH_1106)
	OLED_Write_Byte(0xAE, OLED_CMD);//--turn off oled panel
	OLED_Write_Byte(0x02, OLED_CMD);//--set low column address
	OLED_Write_Byte(0x10, OLED_CMD);//--set high column address
	OLED_Write_Byte(0x40, OLED_CMD);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_Write_Byte(0xB0, OLED_CMD);//--set page address
	OLED_Write_Byte(0x81, OLED_CMD);//--set contrast control register
	OLED_Write_Byte(0xFF, OLED_CMD);//--set SEG Output Current Brightness
	OLED_Write_Byte(0xA1, OLED_CMD);//--set SEG/Column Mapping
	OLED_Write_Byte(0xC8, OLED_CMD);//--set COM/Row Scan Direction (C0h / C8h)
	OLED_Write_Byte(0xA8, OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_Write_Byte(0x3F, OLED_CMD);//--set 1/64 duty
	OLED_Write_Byte(0xD3, OLED_CMD);//--set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_Write_Byte(0x00, OLED_CMD);//-not offset
	OLED_Write_Byte(0xD5, OLED_CMD);//--set display clock divide ratio/oscillator frequency
	OLED_Write_Byte(0x80, OLED_CMD);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_Write_Byte(0xD9, OLED_CMD);//--set pre-charge period
	OLED_Write_Byte(0x1F, OLED_CMD);//--set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_Write_Byte(0xDA, OLED_CMD);//--set com pins hardware configuration
	OLED_Write_Byte(0x12, OLED_CMD);
	OLED_Write_Byte(0xDB, OLED_CMD);//--set vcomh
	OLED_Write_Byte(0x40, OLED_CMD);//--set VCOM Deselect Level
	OLED_Write_Byte(0xAD, OLED_CMD);//--set Charge Pump enable/disable
	OLED_Write_Byte(0x8B, OLED_CMD);//--set external VCC
	//OLED_Write_Byte(0xAF, OLED_CMD);//--turn on oled panel
#endif

	OLED_Clear_Screen(0x00);
	OLED_Refresh_Gram();
	OLED_Display_On();

}

/*--------------------------------------------------------------------------------*/
void OLED_Progressbar_Frame(uint8_t x0, uint8_t y0, uint8_t width, bool mode)
{
	uint8_t x1=x0+width-1, y1=y0+5, xc=x0+(width/2);

	OLED_Draw_Line(x0, y0, x1, y0);
	OLED_Draw_Line(x0, y1, x1, y1);
	OLED_Draw_Line(x0, y0, x0, y1);
	OLED_Draw_Line(x1, y0, x1, y1);

	if(mode)
		OLED_Draw_Line(xc, y0, xc, y1);
}
/*--------------------------------------------------------------------------------*/
void OLED_Progressbar_Value(uint8_t x0, uint8_t y0, uint8_t width, bool mode, float value)
{
	uint8_t w2, v, color;

	x0+=2;
	y0+=2;

	width-=4;
	w2=width/2;

	v= mode ? ((value+1)*w2) : (value*width);

	for(int i=0; i<width; i++)
	{
		if(mode)
			color=((i<=w2 && v<=i) || (i>=w2 && v>=i)) ? 1 : 0;
		else
			color= (i<v) ? 1 : 0;

		OLED_Draw_Point(x0+i, y0 , color);
		OLED_Draw_Point(x0+i, y0+1, color);
	}
}
/*--------------------------------------------------------------------------------*/
