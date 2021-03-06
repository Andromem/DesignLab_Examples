//Uncomment your preferred Shield
#define circuit Gameduino_Computing_Shield     //Please note that pressing the "Reset" button on the Computing Shield will reset the FPGA.
//#define circuit Gameduino_LogicStart_Shield  //Important SW0 and SW1 need to be down for this sketch to work. On the Logicstart Shield, SW0 controls the Arduino reset line and SW1 controls the FPGA reset.

//For a tutorial on using Gameduino on the Papilio DUO visit:
//http://gadgetfactory.net/learn/2015/06/08/gameduino-on-papilio-duo/

#include <SPI.h>
#include <Gameduino.h>

void spr(int x, int y, byte pal)
{
  static int sprnum = 0;
  GD.sprite(sprnum++, x, y, 0, pal, 0);
}

static unsigned int random_color()
{
  return RGB(64 + random(192), 64 + random(192), 64 + random(192));
}

void setup()
{
  int i;

  GD.begin();
  GD.ascii();
  GD.putstr(0, 0,"Sprite palettes");

  for (i = 0; i < 256; i++)
    GD.wr(RAM_SPRIMG + i, i);

  // Fill all the palettes with random colors
  for (i = 0; i < (4 * 256); i++)
    GD.wr16(RAM_SPRPAL + (i << 1), random_color());
  for (i = 0; i < 16; i++) {
    GD.wr16(PALETTE16A + (i << 1), random_color());
    GD.wr16(PALETTE16B + (i << 1), random_color());
  }
  for (i = 0; i < 4; i++) {
    GD.wr16(PALETTE4A + (i << 1), random_color());
    GD.wr16(PALETTE4B + (i << 1), random_color());
  }
  
  GD.putstr(0, 8, "Four 256-color palettes");
  for (i = 0; i < 4; i++)
    spr(200 + 20 * i, (8 * 8), i);

  GD.putstr(0, 12, "Two 16-color palettes");
  for (i = 0; i < 2; i++) {
    spr(200 + 20 * i, (8 * 12),      0x4 | i);
    spr(200 + 20 * i, (8 * 12) + 20, 0x6 | i);
  }

  GD.putstr(0, 18, "Two 4-color palettes");
  for (i = 0; i < 2; i++) {
    spr(200 + 20 * i, (8 * 18),      0x8 | i);
    spr(200 + 20 * i, (8 * 18) + 20, 0xa | i);
    spr(200 + 20 * i, (8 * 18) + 40, 0xc | i);
    spr(200 + 20 * i, (8 * 18) + 60, 0xe | i);
  }
}

void loop()
{
}
