#include <bv4512.h>
#include <Wire.h>

BV4512 di(0x21); // 0x42 I2C address (8 bit)

void setup()
{
  di.reset(); // Helps avoid screen not updating without a cold reset (power + USB disconnected)
  di.colour(0); // default is 0, set to 1 for invert
  di.cls(); // clear display
  di.rectangle(5,6,15,11);
  di.rectangle(107,6,15,11);
  di.rectangle(5,46,15,11);
  di.rectangle(107,46,15,11);
  di.rcPos(3,4);
  di.print("4 Box Counter");
}

void loop()
{
// simple demo
  int count=0;
  while(1) {
    // top left
    di.rcPos(1,1);
    di.print(count);
    // top right
    di.rcPos(1,18);
    di.print(count);
    // bottom left
    di.rcPos(6,1);
    di.print(count);
    // bottom right
    di.rcPos(6,18);
    di.print(count);

    if(count==99) count = 0;
    count++;
    delay(100);
  } 
}

