/*
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <Lcdpcfx8.h>
#include <Arduino.h>

Lcdpcfx8::Lcdpcfx8(int mnumExp)
{

numExp=mnumExp;
# define lcdAdd0 0x20
# define lcdAdd1 0x21
# define lcdAdd2 0x22
# define lcdAdd3 0x23
# define lcdAdd4 0x24
# define lcdAdd5 0x25
# define lcdAdd6 0x26
# define lcdAdd7 0x27

}

void Lcdpcfx8::lcdInit()
{
  Serial.begin(9600);
  Wire.begin();
  delay(500);
 
  for(int j=0;j<numExp;j++)
  { 
     for( int a=0;a<4;a++)
  {
   write4Bite(B00100000,addExp[j]);//4 bit op
    delay(10);
  }
     write4Bite(B00101000,addExp[j]);//func set
     write4Bite(B00001100,addExp[j]);//display on/off and cursor
  write4Bite(B00000110,addExp[j]);//entry set
write4Bite(B00000001,addExp[j]);//clear display;
  delayMicroseconds(3000);
   // Serial.println(addExp[j],HEX);
  }
}

void Lcdpcfx8::displayString(String myString,byte pcfLcdAdd)
{
   
    int strSize=0;
    int baseStrSize=0;
    char letter=' ';
   strSize=myString.length();
   baseStrSize=strSize;
   while(strSize)
   {
   letter=myString.charAt(baseStrSize-strSize);
   letter=letter|B10000000;
   write4Bite(letter,pcfLcdAdd);
   strSize--;
}
 }

void Lcdpcfx8::setCursor(boolean line,byte pos, byte pcfLcdAdd)
{
  byte linePos=B10000000;
  byte nibHi=B0;
  byte nibLo=B0;
  
  bitWrite(linePos,6,line);
  linePos=linePos|pos;
 
  nibHi=(linePos&B11110000)>>4;
  nibLo=linePos&B1111;
 
   expWrite(nibHi,pcfLcdAdd);
  expWrite(nibLo,pcfLcdAdd);


}

void Lcdpcfx8::write4Bite(byte dataByte,byte pcfLcdAdd)
{
 byte hiNib=B0;
  byte loNib=B0;
 boolean mrs=0;
  mrs=bitRead(dataByte,7);
  if(mrs==1)
  {
    dataByte=dataByte&B01111111;
  }
  hiNib=(dataByte&B11110000)>>4;
  loNib=dataByte&B00001111;
  bitWrite(hiNib,7,mrs);
  bitWrite(loNib,7,mrs);
  expWrite(hiNib,pcfLcdAdd);
  expWrite(loNib,pcfLcdAdd);
  
}

void Lcdpcfx8::expWrite(byte nib,byte pcfLcdAdd)
{ 
   Wire.beginTransmission(pcfLcdAdd);
       Wire.write(nib|B01000000);
        Wire.write(nib|B00000000);
  Wire.endTransmission();
  delayMicroseconds(60);
}

void Lcdpcfx8::sendStrLcd(String myString,byte pcfLcdAdd,boolean line,byte pos)
{
  int strLth=0;
int  addLine=0; 
 addLine=(pcfLcdAdd*2)+line;

 switch(addLine)
 {
  case 64:
   strArray[0]=myString;
    setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[0],pcfLcdAdd);
  
  break;
   
case 65:

   strArray[1]=myString;
   setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[1],pcfLcdAdd);

break;

case 66:
    strArray[2]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[2],pcfLcdAdd);
 
break;

case 67:
   strArray[3]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[3],pcfLcdAdd);

break;

case 68:
   strArray[4]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[4],pcfLcdAdd);

break;

case 69:
   strArray[5]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[5],pcfLcdAdd);

break;

case 70:
   strArray[6]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[6],pcfLcdAdd);

break;

case 71:
   strArray[7]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[7],pcfLcdAdd);

break;

case 72:
   strArray[8]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[8],pcfLcdAdd);

break;

case 73:
   strArray[9]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[9],pcfLcdAdd);

break;

case 74:
   strArray[10]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[10],pcfLcdAdd);

break;

case 75:
   strArray[11]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[11],pcfLcdAdd);

break;

case 76:
   strArray[12]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[12],pcfLcdAdd);

break;

case 77:
   strArray[13]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[13],pcfLcdAdd);

break;

case 78:
   strArray[14]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[14],pcfLcdAdd);

break;

case 79:
   strArray[15]=myString;
     setCursor(line,pos,pcfLcdAdd);
   displayString(strArray[15],pcfLcdAdd);

break;
 }
}

void Lcdpcfx8::sendDataLcd(String dataVal,byte pcfLcdAdd, boolean line,int pos, int fieldLgth)
{
  String emptyStr="";
 char emptyChar=' ';
  for(int t=0;t<fieldLgth;t++)
  {
  emptyStr+=emptyChar;
  }
   
  sendStrLcd(emptyStr,pcfLcdAdd,line,pos);
     sendStrLcd(dataVal,pcfLcdAdd,line,pos);
 }


boolean Lcdpcfx8::readDigital(String action0,String action1,int pinNum,byte pcfLcdAdd,boolean line, int pos)
{
 int act0StrLgth=action0.length();
 int  act1StrLgth=action1.length();

    String emptyStr1="";
 char emptyChar=' ';
  for(int t=0;t<act1StrLgth;t++)
  {
  emptyStr1+=emptyChar;
  }
    String emptyStr0="";

  for(int t=0;t<act0StrLgth;t++)
  {
  emptyStr0+=emptyChar;
  }

 boolean switchState=digitalRead(pinNum);
  if(switchState==0&& lastSwitchState==HIGH)
  {
    sendStrLcd(emptyStr0,pcfLcdAdd,line,pos);
    sendStrLcd(action1,pcfLcdAdd,line,pos);
 lastSwitchState=switchState;
  }
 
  else if(switchState==HIGH)
    {
       sendStrLcd(emptyStr1,pcfLcdAdd,line,pos);
        sendStrLcd(action0,pcfLcdAdd,line,pos);
     lastSwitchState=switchState;
    }
    return switchState;
}

void Lcdpcfx8::clearDisplay(byte pcfLcdAdd,boolean line,int pos0,int pos1,boolean clearAll)
{
 char space=' ';
  String emptyStr="                ";
  String partEmptyStr="";
if(clearAll==true)
{
  setCursor(0,0,pcfLcdAdd);
  displayString(emptyStr,pcfLcdAdd);
   setCursor(1,0,pcfLcdAdd);
  displayString(emptyStr,pcfLcdAdd);
  setCursor(0,0,pcfLcdAdd);
   setCursor(1,0,pcfLcdAdd);
}
else
{
  int emptyStrLgth=(pos1-pos0)+1;
  for(int h=0;h<emptyStrLgth;h++)
  {
    partEmptyStr+=space;
  }
  setCursor(line,pos0,pcfLcdAdd);
  displayString(partEmptyStr,pcfLcdAdd);
}
} 