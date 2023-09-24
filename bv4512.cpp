/*
  BV4512 (I2C) 128x64 Display controller from ByVac
  Copyright (c) 2011 Jim Spence.  All right reserved.
  www.byvac.com - see terms and conditions for using hardware
  
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

#include "Arduino.h"
#include "bv4512.h"
 
// **************************************************************
// **************************************************************
BV4512::BV4512(char i2adr):I2c_bv(i2adr)
{
  _i2adr=i2adr; 
  _colour=0; 
}

// ==============================================================
// I2C 128 x 64 display, 2 colour, white and dark
// ==============================================================
// ==============================================================

// **************************************************************
// set colour normal (white), inverse (dark)
// normal, default is 0 = white 
// *************************************************************
void BV4512::colour(char colour)
{
    _colour=colour;
}

// **************************************************************
// clears screen to the set colour
// **************************************************************
void BV4512::cls()
{
  Wire.beginTransmission(_i2adr);
  Wire.write(0x10);
  if(_colour==0) Wire.write(0);
  else Wire.write(0xff);
  Wire.endTransmission();
  delay(500);
}

// **************************************************************
// command 1
// Turns on / off display, send 1 to turn on, 0 for off
// **************************************************************
void BV4512::activate(char onn)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  Wire.write(1);  // command
  Wire.write(onn);
  Wire.endTransmission();
} 

// **************************************************************
// Ccommand 2
// direct command to KS0108 controller
// **************************************************************
void BV4512::direct(char value)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  Wire.write(2); 
  Wire.write(value);
  Wire.endTransmission();
} 

// **************************************************************
// Ccommand 3
// write byte
// **************************************************************
void BV4512::writeData(char value)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  Wire.write(3); 
  Wire.write(value);
  Wire.endTransmission();
} 

// **************************************************************
// Ccommand 4
// read byte
// **************************************************************
char BV4512::readData()
{ 
char rv;
  Wire.beginTransmission(_i2adr);
  Wire.write(4); 
  Wire.requestFrom(_i2adr, 1); // returns 1 byte
  rv=Wire.read();
  Wire.endTransmission();
  return rv;
} 

// **************************************************************
// Command 5
// reset
// **************************************************************
void BV4512::reset()
{ 
  // 
  Wire.beginTransmission(_i2adr);
  Wire.write(5); 
  Wire.endTransmission();
  delay(500);
} 

// **************************************************************
// command 6
// backlight on / off send 1 to turn on, 0 for off
// **************************************************************
void BV4512::backlight(char onn)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  Wire.write(6);  // command
  Wire.write(onn);
  Wire.endTransmission();
} 

// **************************************************************
// Command 7
// set x position
// **************************************************************
void BV4512::xPosition(char xpos)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(xpos > 127) xpos=127;
  if(xpos < 0) xpos=0;
  Wire.write(7); 
  Wire.write(xpos);
  Wire.endTransmission();
} 

// **************************************************************
// Command 8
// set r position
// **************************************************************
void BV4512::rPosition(char rpos)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(rpos > 7) rpos=7;
  if(rpos < 0) rpos=0;
  Wire.write(8); 
  Wire.write(rpos);
  Wire.endTransmission();
} 

// **************************************************************
// Command 9
// set x and r position and send data
// **************************************************************
void BV4512::xrPosition(char xpos, char rpos, char data)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(xpos > 127) xpos=127;
  if(xpos < 0) xpos=0;
  if(rpos > 7) rpos=7;
  if(rpos < 0) rpos=0;
  Wire.write(9); 
  Wire.write(xpos);
  Wire.write(rpos);
  Wire.write(data);
  Wire.endTransmission();
} 

// **************************************************************
// Command 0xa
// set x and y position and send data
// **************************************************************
void BV4512::xyPosition(char xpos, char ypos, char data)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(xpos > 127) xpos=127;
  if(xpos < 0) xpos=0;
  if(ypos > 64) ypos=64;
  if(ypos < 0) ypos=0;
  Wire.write(0xa); 
  Wire.write(xpos);
  Wire.write(ypos);
  Wire.write(data);
  Wire.endTransmission();
} 

// **************************************************************
// Command 10
// filles screen with a particular byte
// **************************************************************
void BV4512::fill(char value)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  Wire.write(0x10); 
  Wire.write(value);
  Wire.endTransmission();
} 

// **************************************************************
// Command 11
// set x and y position and turn on / off pixel, data=0 for off
// **************************************************************
void BV4512::xyPix(char xpos, char rpos, char data)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(xpos > 127) xpos=127;
  if(xpos < 0) xpos=0;
  if(rpos > 7) rpos=7;
  if(rpos < 0) rpos=0;
  Wire.write(0x11); 
  Wire.write(xpos);
  Wire.write(rpos);
  Wire.write(data);
  Wire.endTransmission();
} 

// **************************************************************
// Command 12 & 13
// draw a horizontal line
// **************************************************************
void BV4512::hline(char xpos, char ypos, char length)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(xpos > 127) xpos=127;
  if(xpos < 0) xpos=0;
  if(ypos > 64) ypos=64;
  if(ypos < 0) ypos=0;
  if(_colour==0) Wire.write(0x12);
  else Wire.write(0x13); 
  Wire.write(xpos);
  Wire.write(ypos);
  Wire.write(length);
  Wire.endTransmission();
} 

// **************************************************************
// Command 14 & 15
// draw a vertical line
// **************************************************************
void BV4512::vline(char xpos, char ypos, char length)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(xpos > 127) xpos=127;
  if(xpos < 0) xpos=0;
  if(ypos > 64) ypos=64;
  if(ypos < 0) ypos=0;
  if(_colour==0) Wire.write(0x14);
  else Wire.write(0x15); 
  Wire.write(xpos);
  Wire.write(ypos);
  Wire.write(length);
  Wire.endTransmission();
} 

// **************************************************************
// Command 16 & 17
// draws box no fill
// **************************************************************
void BV4512::rectangle(char xpos, char ypos, char xlength, char ylength)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(xpos > 127) xpos=127;
  if(xpos < 0) xpos=0;
  if(ypos > 64) ypos=64;
  if(ypos < 0) ypos=0;
  if(_colour==0) Wire.write(0x16);
  else Wire.write(0x17); 
  Wire.write(xpos);
  Wire.write(ypos);
  Wire.write(xlength);
  Wire.write(ylength);
  Wire.endTransmission();
} 

// **************************************************************
// Command 18 & 19
// draws box with fill
// **************************************************************
void BV4512::box(char xpos, char ypos, char xlength, char ylength)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(xpos > 127) xpos=127;
  if(xpos < 0) xpos=0;
  if(ypos > 64) ypos=64;
  if(ypos < 0) ypos=0;
  if(_colour==0) Wire.write(0x18);
  else Wire.write(0x19); 
  Wire.write(xpos);
  Wire.write(ypos);
  Wire.write(xlength);
  Wire.write(ylength);
  Wire.endTransmission();
} 

// **************************************************************
// Command 20 & 21
// places char at current position, set by command 0x25
// **************************************************************
void BV4512::d_putchar(char value)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(_colour==0) Wire.write(0x20);
  else Wire.write(0x21); 
  Wire.write(value);
  Wire.endTransmission();
} 

// ==============================================================
// General purpose print
// 
// **************************************************************
// Single byte
void BV4512::print(char value)
{
    d_putchar(value);
}
// String
void BV4512::print(char *b)
{
    while(*b) 
        d_putchar(*(b++));
}
// Integer
void BV4512::print(int value)
{
char buf[15], *b=buf;
    sprintf(buf,"%d",value);
    while(*b) 
        d_putchar(*(b++));
}


// **************************************************************
// Command 22 & 23
// places char at current position, set by command 0x25, char
// defined in eeprom
// **************************************************************
void BV4512::e_putchar(char value)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(value > 34) value=34;
  if(value < 0) value = 0;
  if(_colour==0) Wire.write(0x22);
  else Wire.write(0x23); 
  Wire.write(value);
  Wire.endTransmission();
} 

// **************************************************************
// Command 25
// moves cursor position
// **************************************************************
void BV4512::rcPos(char rpos, char cpos)
{ 
  // 
  Wire.beginTransmission(_i2adr);
  if(rpos > 7) rpos=7;
  if(rpos < 0) rpos=0;
  if(cpos > 20) cpos=20;
  if(cpos < 0) cpos=0;
  Wire.write(0x25); 
  Wire.write(rpos);
  Wire.write(cpos);
  Wire.endTransmission();
} 

// **************************************************************
// Command 27
// get x position
// **************************************************************
char BV4512::getx()
{ 
char rv;
  Wire.beginTransmission(_i2adr);
  Wire.write(0x27); 
  Wire.requestFrom(_i2adr, 1); // returns 1 byte
  rv=Wire.read();
  Wire.endTransmission();
  return rv;
} 

// **************************************************************
// Command 28
// get r position
// **************************************************************
char BV4512::getr()
{ 
char rv;
  Wire.beginTransmission(_i2adr);
  Wire.write(0x28); 
  Wire.requestFrom(_i2adr, 1); // returns 1 byte
  rv=Wire.read();
  Wire.endTransmission();
  return rv;
} 



