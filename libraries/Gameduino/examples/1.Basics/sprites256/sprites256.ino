//Uncomment your preferred Shield
#define circuit Gameduino_Computing_Shield     //Please note that pressing the "Reset" button on the Computing Shield will reset the FPGA.
//#define circuit Gameduino_LogicStart_Shield  //Important SW0 and SW1 need to be down for this sketch to work. On the Logicstart Shield, SW0 controls the Arduino reset line and SW1 controls the FPGA reset.

//IMPORTANT NOTE: This sketch is too large to load over the USB port. Please use the AVR ISP mode to load this sketch. Here is a link with instructions for using ISP mode:
//http://gadgetfactory.net/learn/2015/01/15/designlab-quickstart-duo-avr/#Load_Sketch_Using_ISP

//For a tutorial on using Gameduino on the Papilio DUO visit:
//http://gadgetfactory.net/learn/2015/06/08/gameduino-on-papilio-duo/

#include <SPI.h>
#include <Gameduino.h>

#include "pickups2.h"
#include "sprites256.h"

struct sprite
{
  int x;
  int y;
  char vx, vy;
} sprites[256];

void plot()
{
  int i;
  for (i = 0; i < 256; i++) {
    GD.sprite(i, sprites[i].x >> 4, sprites[i].y >> 4, i % 47, 0, 0);
  }
}

#define LWALL (0 << 4)
#define RWALL (384 << 4)
#define TWALL (0 << 4)
#define BWALL (284 << 4)

void move()
{
  int i;
  sprite *ps;

  for (i = 256, ps = sprites; i--; ps++) {
    if ((ps->x <= LWALL)) {
      ps->x = LWALL;
      ps->vx = -ps->vx;
    }
    if ((ps->x >= RWALL)) {
      ps->x = RWALL;
      ps->vx = -ps->vx;
    }
    if ((ps->y <= TWALL)) {
      ps->y = TWALL;
      ps->vy = -ps->vy;
    }
    if ((ps->y >= BWALL)) {
      ps->y = BWALL;
      ps->vy = -ps->vy;
    }
    ps->x += ps->vx;
    ps->y += ps->vy;
  }
}

void setup()
{
  int i;
  delay(3000);
  GD.begin();
  
  GD.copy(RAM_PIC, sprites256_pic, sizeof(sprites256_pic));
  GD.copy(RAM_CHR, sprites256_chr, sizeof(sprites256_chr));
  GD.copy(RAM_PAL, sprites256_pal, sizeof(sprites256_pal));

  GD.copy(RAM_SPRIMG, pickups2_img, sizeof(pickups2_img));
  GD.copy(RAM_SPRPAL, pickups2_pal, sizeof(pickups2_pal));

  for (i = 0; i < 256; i++) {
    sprites[i].x = random(400 << 4);
    sprites[i].y = random(300 << 4);
    sprites[i].vx = random(-16,16);
    sprites[i].vy = random(-16,16);
  }
}

void loop()
{
  plot();
  move();
}
