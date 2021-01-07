LcdPcfx8 library for Arduino

Control up to 8 (1602)lcd(2 lines, 16 positions each line) with I2C interface using pcf8574p.

 By default, pcf8574 Addresses as follows:
 lcdAdd0=0x20
 lcdAdd1=0x21
 lcdAdd2=0x22
 lcdAdd3=0x23
 lcdAdd4=0x24
 lcdAdd5=0x25
 lcdAdd6=0x26
 lcdAdd7=0x27
 pcf pinout to Lcd (See Datsheet pg.3 DW or N package) as follows:
 P0>D4;P1>D5;P2>D6;P3>D7;P6>Enable;P7>RS

User functions:

Lcdpcfx8(int mnumExp);constructor,number of lcd/pcf8574 combos

void lcdInit();initiallize1602 lcd, 4 bit operation ,5X7 font,2 lines

void sendStrLcd(String myString,byte pcfLcdAdd,boolean line, byte pos);send static string to specified lcd, line and position

void sendDataLcd(String dataVal,byte pcfLcdAdd,boolean line,int pos,int fieldLgth);send variable string to specifed lcd, line, position and specify string maximum field length

boolean readDigital(String action0,String action1,int pinNum,byte pcfLcdAdd,boolean line,int pos);returns value of specifed digital pin,displays one of two states,strings specifed by user