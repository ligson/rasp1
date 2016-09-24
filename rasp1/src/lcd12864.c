/*
 ���У�sudo ./12864 [�ַ�]
 ���룺gcc 12864.c -o 12864 -L lib -l wiringPi (���Ѱ�װwiringPi)
 by��WuSiYu
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h>
#include <iconv.h>

#define LCD_RS 18 //��ʾ��������
#define LCD_RW 24
#define LCD_EN 23

#define D1 25 //��ʾ��������
#define D2 26
#define D3 19
#define D4 13
#define D5 6
#define D6 4
#define D7 17
#define D8 27

char u2g_out[255];

/*===================================================================
 ���ܣ�����ת��
 ���룺UTF8
 �����GB2312
 ====================================================================*/
int code_convert(char *from_charset, char *to_charset, char *inbuf, int inlen,
		char *outbuf, int outlen) {
	iconv_t cd;
	int rc;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
		return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1)
		return -1;
	iconv_close(cd);
	return 0;
}

int u2g(char *inbuf, int inlen, char *outbuf, int outlen) {
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}

/*===================================================================
 ���ܣ�����д��
 ���룺ʮ����������
 �������
 ====================================================================*/
void bus_write(unsigned char data) {
	int t[10];
	int f = 0, i = 0, d = data;

//����ת��
	for (i = 0; i < 8; i++) {
		t[i] = data % 2;
		data = data / 2;
	}

//���
	digitalWrite(D1, t[0]);
	digitalWrite(D2, t[1]);
	digitalWrite(D3, t[2]);
	digitalWrite(D4, t[3]);
	digitalWrite(D5, t[4]);
	digitalWrite(D6, t[5]);
	digitalWrite(D7, t[6]);
	digitalWrite(D8, t[7]);
}
/*===================================================================
 ���ܣ����LCDæ״̬
 ���룺��
 �����lcd_busyΪ1ʱ��æ���ȴ���lcd-busyΪ0ʱ,�У���дָ�������ݡ�
 ====================================================================*/
void chk_busy() { //���æλ
	digitalWrite(LCD_RS, 0);
	digitalWrite(LCD_RW, 1);
	digitalWrite(LCD_EN, 1);
	bus_write(0xff);
	pinMode(D8, INPUT);
	while (digitalRead(D8))
		;
	pinMode(D8, OUTPUT);
	digitalWrite(LCD_EN, 0);
}
/*====================================================================
 ���ܣ�д����
 ���룺8λ����
 �������
 =====================================================================*/
void WriteCmd_LCD12864(unsigned char cmdcode) {
	chk_busy();
	digitalWrite(LCD_RS, 0);
	digitalWrite(LCD_RW, 0);
	digitalWrite(LCD_EN, 1);
	delay(5);
	bus_write(cmdcode);
	digitalWrite(LCD_EN, 0);
	delay(5);
}
/*====================================================================
 ���ܣ�д����
 ���룺8λ����
 �������
 =====================================================================*/
void WriteData_LCD12864(unsigned char Dispdata) {
	chk_busy();
	digitalWrite(LCD_RS, 1);
	digitalWrite(LCD_RW, 0);
	digitalWrite(LCD_EN, 1);
	delay(5);
	bus_write(Dispdata);
	digitalWrite(LCD_EN, 0);
	delay(5);
}
/*==========================================================================
 ���ܣ������ַ���
 ���룺��ַ���ַ���
 �������
 ===========================================================================*/
void WriteWord_LCD12864(unsigned char a, unsigned char *d) { //��LCDָ��λ�÷���һ���ַ���,����64�ַ�֮�ڡ�
	unsigned char *s;
	u2g(d, strlen(d), u2g_out, 255);
	s = u2g_out;
	WriteCmd_LCD12864(a);
	while (*s > 0) {
		WriteData_LCD12864(*s);
		s++;
	}
}
/*==========================================================================
 ���ܣ������ַ���2
 ���룺�ַ���
 �������
 ===========================================================================*/
void WriteWord_LCD12864_2(unsigned char *d) { //��LCD����һ���ַ���,����64�ַ�֮�ڡ�
	int i = 0;
	unsigned char *s;
	u2g(d, strlen(d), u2g_out, 255);
	s = u2g_out;
	WriteCmd_LCD12864(0x80);
	while (*s > 0) {
		WriteData_LCD12864(*s);
		s++;
		i++;
		if (i == 16) {
			WriteCmd_LCD12864(0x90);
		}
		if (i == 32) {
			WriteCmd_LCD12864(0x88);
		}
		if (i == 48) {
			WriteCmd_LCD12864(0x98);
		}
	}
}
/*==========================================================================
 ���ܣ���ʼ��LCD
 ���룺��
 �������
 ===========================================================================*/
void Init_LCD12864(void) { //��ʼ��LCD��
	pinMode(D1, OUTPUT); //����GPIO
	pinMode(D2, OUTPUT);
	pinMode(D3, OUTPUT);
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinMode(D7, OUTPUT);
	pinMode(D8, OUTPUT);

	pinMode(LCD_RS, OUTPUT);
	pinMode(LCD_RW, OUTPUT);
	pinMode(LCD_EN, OUTPUT);

	WriteCmd_LCD12864(0x38); //ѡ��8bit������
	delay(20);
	WriteCmd_LCD12864(0x01); //�����ʾ�������趨��ַָ��Ϊ00H
	delay(20);
	WriteCmd_LCD12864(0x0c); //����ʾ(���αꡢ������)
	delay(20);
}

int main(int args, char *argv[]) {
	wiringPiSetup();
	Init_LCD12864();

	WriteCmd_LCD12864(0x01);
	WriteWord_LCD12864(0x80, "Hello LCD12864");
	if (argv[1]) {
		WriteCmd_LCD12864(0x01);
		WriteCmd_LCD12864(0x80);
		WriteWord_LCD12864_2(argv[1]);
	}
}

