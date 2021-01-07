#include <Wire.h>
#include <Arduino.h>
#ifndef Lcdpcfx8_h
#define Lcdpcfx8_h

class Lcdpcfx8
{
private:
 String strArray[16]={"","","","","","","","","","","","","","","",""};
int numExp=0;
int mnumExp=0;
 boolean lastSwitchState=0;

void displayString(String myString,byte pcfLcdAdd);
void setCursor(boolean line,byte pos,byte pcfLcdAdd);
void write4Bite(byte dataByte,byte pcfLcdAdd);
void expWrite(byte nib,byte pcfLcdAdd);

public:
Lcdpcfx8(int mnumExp);
void lcdInit();
void sendStrLcd(String myString,byte pcfLcdAdd,boolean line, byte pos);
void sendDataLcd(String dataVal,byte pcfLcdAdd,boolean line,int pos,int fieldLgth);
void clearDisplay(byte pcfLcdAdd,boolean line,int pos0,int pos1,boolean clearAll);
boolean readDigital(String action0,String action1,int pinNum,byte pcfLcdAdd,boolean line,int pos);

# define lcdAdd0 0x20
# define lcdAdd1 0x21
# define lcdAdd2 0x22
# define lcdAdd3 0x23
# define lcdAdd4 0x24
# define lcdAdd5 0x25
# define lcdAdd6 0x26
# define lcdAdd7 0x27
byte addExp[8]={lcdAdd0,lcdAdd1,lcdAdd2,lcdAdd3,lcdAdd4,lcdAdd5,lcdAdd6,lcdAdd7};
};
#endif

