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
  di.hline(40,40,20);
  di.vline(40,40,20);
  di.rectangle(5,46,15,11);
  di.box(107,46,15,11);  // Draw a solid box
  di.rcPos(3,4);
  di.print("4 Box Counter");
  di.xyPix(0, 0, 1); // Change a single pixel
  // di.fill(B00000001); // First row on, all others off
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
    di.colour(1); // Print the bottom left box text in inverted colors
    di.print(count);
    di.colour(0);
    

    if(count==99) count = 0;
    count++;

    delay(500);
    //di.backlight(0);  // Flash backlight
    delay(100);
    //di.backlight(1);
  } 
}

