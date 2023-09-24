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

#ifndef _H_bv4512_h
#define _H_bv4512_h

//#include "Wire.h"
#include "I2c_bv.h"
#include "Arduino.h"



class BV4512 : public I2c_bv
{
    public:
        BV4512(char i2adr);
        void colour(char colour);
        void cls();
        void activate(char onn); // 1
        void direct(char value); // 2
        void writeData(char value); // 3
        char readData(); // 4
        void reset(); // 5
        void backlight(char onn); // 6    
        void xPosition(char xpos); // 7
        void rPosition(char rpos); // 8
        void xrPosition(char xpos, char rpos, char data); // 9
        void xyPosition(char xpos, char ypos, char data); // 0xa
        void fill(char value); // 0x10
        void xyPix(char xpos, char rpos, char data); // 0x11
        void hline(char xpos, char ypos, char length); // 0x12 & 0x13
        void vline(char xpos, char ypos, char length); // 0x14 & 0x15
        void rectangle(char xpos, char ypos, char xlength, char ylength); // 0x16 & 0x17
        void box(char xpos, char ypos, char xlength, char ylength); // 0x18 & 0x19
        void d_putchar(char value); // 0x20 & 0x21
            void print(char value);
            void print(char *b);
            void print(int value);
        void e_putchar(char value); // 0x22 & 0x23
        void rcPos(char rpos, char cpos); // 0x25
        char getx(); // 0x27
        char getr(); // 0x28                
    private:    
        int i2_16bit();
        char _colour;
        char _i2adr;
};

#endif
