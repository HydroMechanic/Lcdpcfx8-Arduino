/* By default,set last 4 bits of lcd address(A0,A1,A2;A0LSB) pcf8574p Addresses 
  as follows:
 eg. pick lcdAdd2 A0>gnd;A1>+5v;A2>gnd on pcf8574p
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
*/

#include <Wire.h>
#include <Lcdpcfx8.h>
Lcdpcfx8 myLcd(3);//myLcd(number of lcd)
#define inputPin0 2
#define inputPin1 3
#define ledPin 7
long timeStamp=0;
long lastTimeStamp=0;

void setup()
{
 Wire.begin();
 myLcd.lcdInit();
 pinMode(inputPin0,INPUT_PULLUP);
 pinMode(inputPin1,INPUT_PULLUP);
 pinMode(ledPin,OUTPUT);
}
 void loop()
 {
  int pot0Val=(analogRead(A0));
   int pot1Val=analogRead(A1);
    int pot2Val=analogRead(A2);
 

  myLcd.sendStrLcd("Red LED:",lcdAdd2,0,0);
myLcd.sendStrLcd("Pot2 Value:",lcdAdd2,1,0);
myLcd.sendDataLcd(String(pot2Val),lcdAdd2,1,11,4);
myLcd.sendStrLcd("lcd1 line1",lcdAdd1,1,3);
myLcd.sendStrLcd("ANA VOLTS:",lcdAdd1,0,0);
myLcd.sendStrLcd("lcd0 line0",lcdAdd0,0,3);
myLcd.sendStrLcd("pot0 Val:",lcdAdd0,1,0);

if(pot0Val<=800)//part of flash value feature
{
 myLcd.sendDataLcd(String(pot0Val),lcdAdd0,1,9,4);
}
  float voltsA1=(pot1Val/1023.)*5.;
  myLcd.sendDataLcd(String(voltsA1)+'V',lcdAdd1,0,10,4);
  boolean switchState0=myLcd.readDigital("Off","On",inputPin0,lcdAdd2,0,9);

  if (switchState0==0)
  {
    digitalWrite(ledPin,HIGH);
  }
  else
  {
    digitalWrite(ledPin,LOW);
  }
     timeStamp=millis();
     
  //flash display if over certain value   
     if ((pot0Val)>800)
     {
   
if ((timeStamp-lastTimeStamp)<500)
{
 myLcd.clearDisplay(lcdAdd0,1,9,15,false);

}

else if ((timeStamp-lastTimeStamp)>500&&(timeStamp-lastTimeStamp)<1000)
{
  myLcd.sendDataLcd(String(pot0Val),lcdAdd0,1,9,4);
} 
 if(timeStamp-lastTimeStamp>1000)
 {
   lastTimeStamp=timeStamp;
 }
}
 }
