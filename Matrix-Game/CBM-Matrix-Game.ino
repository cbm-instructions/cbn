
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library
#include <avr/pgmspace.h>

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define OE  9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3
RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);

#define UP 50
#define DOWN 51
#define LEFT 52
#define RIGHT 53
#define START 49

byte labyrinth[16 * 16] = {
  1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 1, 0, 0, 0, 0, 1,  1, 1, 0, 0, 0, 0, 1, 1,
  1, 0, 1, 0, 1, 1, 0, 2,  0, 0, 0, 1, 1, 0, 0, 1,
  1, 0, 1, 0, 0, 1, 1, 1,  1, 1, 0, 0, 1, 1, 0, 1,
  1, 0, 1, 1, 0, 0, 1, 1,  1, 1, 1, 1, 1, 0, 0, 1,
  1, 0, 0, 1, 1, 0, 1, 0,  1, 0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 1, 1,  1, 1, 0, 1, 1, 0, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 0, 1, 1, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 0, 1,  1, 1, 0, 1, 1, 1, 0, 1,
  1, 0, 1, 1, 0, 1, 1, 1,  1, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 0, 1,  1, 1, 0, 1, 0, 1, 1, 1,
  1, 0, 1, 1, 1, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 1, 0, 1,  1, 1, 1, 1, 0, 1, 0, 1,
  1, 2, 1, 0, 1, 0, 0, 0,  2, 0, 0, 0, 0, 1, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
};

byte labyrinthPool[5][2][16 * 16] = {
  {
    { // 1 Lab
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 9, 0, 0, 0, 0, 9,  9, 9, 0, 0, 0, 0, 9, 1,
      1, 0, 1, 0, 1, 1, 0, 2,  0, 0, 0, 1, 1, 0, 0, 1,
      1, 0, 9, 0, 0, 9, 9, 9,  9, 9, 0, 0, 9, 9, 0, 1,
      1, 0, 1, 1, 0, 0, 1, 1,  1, 1, 1, 1, 1, 0, 0, 1,
      1, 0, 0, 9, 9, 0, 9, 0,  9, 0, 0, 0, 0, 0, 9, 1,
      1, 1, 0, 0, 0, 0, 1, 1,  1, 1, 0, 1, 1, 0, 0, 1,
      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 2, 9, 9, 9, 9, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 0, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 9,  9, 9, 0, 9, 9, 9, 0, 1,
      1, 0, 1, 1, 0, 1, 1, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 9, 0, 0, 0, 9,  9, 9, 0, 9, 0, 9, 9, 1,
      1, 0, 1, 1, 1, 1, 0, 1,  0, 1, 0, 1, 0, 0, 0, 1,
      1, 0, 0, 0, 9, 9, 0, 9,  9, 9, 9, 9, 0, 9, 0, 1,
      1, 2, 1, 0, 1, 0, 0, 0,  2, 0, 0, 0, 0, 1, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 1, 0, 0, 0, 0, 1,  1, 1, 0, 0, 0, 0, 1, 1,
      1, 0, 9, 0, 9, 9, 0, 2,  0, 0, 0, 9, 9, 0, 0, 1,
      1, 0, 1, 0, 0, 1, 1, 1,  1, 1, 0, 0, 1, 1, 0, 1,
      1, 0, 9, 9, 0, 0, 9, 9,  9, 9, 9, 9, 9, 0, 0, 1,
      1, 0, 0, 1, 1, 0, 1, 0,  1, 0, 0, 0, 0, 0, 1, 1,
      1, 9, 0, 0, 0, 0, 9, 9,  9, 9, 0, 9, 9, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 2, 1, 1, 1, 1, 1,
      1, 9, 9, 9, 9, 9, 9, 9,  9, 9, 0, 9, 9, 9, 9, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 1, 0, 1, 1, 1, 0, 1,
      1, 0, 9, 9, 0, 9, 9, 9,  9, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 0, 0, 1,  1, 1, 0, 1, 0, 1, 1, 1,
      1, 0, 9, 9, 9, 9, 0, 9,  0, 9, 0, 9, 0, 0, 0, 1,
      1, 0, 0, 0, 1, 1, 0, 1,  1, 1, 1, 1, 0, 1, 0, 1,
      1, 2, 9, 0, 9, 0, 0, 0,  2, 0, 0, 0, 0, 9, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    }
  },
  {
    { // 2 Lab
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 9, 0, 0, 0, 0, 9, 1,
      1, 1, 1, 0, 1, 1, 0, 1,  1, 1, 0, 1, 1, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 9, 9, 0, 1,
      1, 0, 1, 1, 1, 1, 1, 1,  1, 0, 1, 1, 1, 0, 0, 1,
      1, 0, 0, 9, 0, 0, 0, 2,  0, 0, 9, 0, 0, 0, 9, 1,
      1, 1, 0, 0, 0, 1, 1, 1,  1, 1, 1, 0, 1, 0, 0, 1,
      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 9, 2, 9, 9, 9, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 0, 1, 1, 1, 1,
      1, 0, 0, 9, 0, 0, 0, 1,  1, 9, 9, 0, 9, 9, 0, 1,
      1, 0, 1, 1, 1, 0, 1, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 9, 0, 9, 9, 9, 0, 1,
      1, 0, 1, 1, 1, 1, 0, 1,  1, 1, 0, 1, 0, 0, 0, 1,
      1, 0, 0, 9, 0, 9, 0, 0,  2, 0, 9, 9, 0, 9, 0, 1,
      1, 2, 1, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 1, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 1, 0, 0, 0, 0, 1, 1,
      1, 9, 9, 0, 9, 9, 0, 1,  1, 9, 0, 9, 9, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 1, 1, 0, 1,
      1, 0, 9, 9, 9, 9, 9, 1,  1, 0, 9, 9, 9, 0, 0, 1,
      1, 0, 0, 1, 0, 0, 0, 2,  0, 0, 1, 0, 0, 0, 1, 1,
      1, 9, 0, 0, 0, 9, 9, 1,  1, 9, 9, 0, 9, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 2, 1, 1, 1, 1,

      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 9, 0, 9, 9, 9, 1,
      1, 0, 0, 1, 0, 0, 0, 1,  1, 1, 1, 0, 1, 1, 0, 1,
      1, 0, 9, 9, 9, 0, 9, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 0, 0, 0, 0, 0, 1,  1, 1, 0, 1, 1, 1, 0, 1,
      1, 0, 9, 9, 9, 9, 0, 1,  1, 9, 0, 9, 0, 0, 0, 1,
      1, 0, 0, 1, 0, 1, 0, 0,  2, 0, 1, 1, 0, 1, 0, 1,
      1, 2, 9, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 9, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    }
  },
  {
    { // 3 LAB
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 9, 0, 9, 1,  1, 0, 0, 0, 0, 0, 9, 1,
      1, 0, 1, 0, 1, 0, 1, 1,  1, 1, 1, 0, 1, 0, 0, 1,
      1, 0, 9, 0, 0, 0, 0, 1,  1, 9, 9, 0, 9, 9, 0, 1,
      1, 0, 1, 1, 1, 1, 1, 1,  1, 1, 0, 0, 1, 0, 0, 1,
      1, 0, 9, 0, 0, 0, 0, 1,  1, 0, 0, 9, 9, 0, 9, 1,
      1, 0, 0, 0, 1, 1, 0, 2,  0, 0, 1, 1, 0, 0, 0, 1,
      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 9, 9, 2, 9, 9, 1,

      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 0, 1, 1, 1,
      1, 9, 0, 0, 0, 0, 0, 0,  2, 0, 0, 9, 0, 0, 0, 1,
      1, 1, 0, 1, 1, 1, 1, 1,  1, 1, 0, 1, 1, 0, 1, 1,
      1, 9, 0, 0, 0, 0, 0, 1,  1, 9, 0, 0, 0, 0, 9, 1,
      1, 1, 1, 1, 1, 1, 0, 1,  1, 1, 0, 1, 1, 0, 0, 1,
      1, 9, 0, 0, 0, 9, 0, 1,  1, 9, 0, 0, 9, 9, 0, 1,
      1, 2, 0, 1, 0, 0, 0, 1,  1, 1, 1, 0, 1, 1, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 1, 0, 1, 1,  1, 0, 0, 0, 0, 0, 1, 1,
      1, 0, 9, 0, 9, 0, 9, 1,  1, 9, 9, 0, 9, 0, 0, 1,
      1, 0, 1, 0, 0, 0, 0, 1,  1, 1, 1, 0, 1, 1, 0, 1,
      1, 0, 9, 9, 9, 9, 9, 1,  1, 9, 0, 0, 9, 0, 0, 1,
      1, 0, 1, 0, 0, 0, 0, 1,  1, 0, 0, 1, 1, 0, 1, 1,
      1, 0, 0, 0, 9, 9, 0, 2,  0, 0, 9, 9, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 2, 1, 1, 1,

      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 9, 9, 0, 9, 9, 1,
      1, 1, 0, 0, 0, 0, 0, 0,  2, 0, 0, 1, 0, 0, 0, 1,
      1, 9, 0, 9, 9, 9, 9, 1,  1, 9, 0, 9, 9, 0, 9, 1,
      1, 1, 0, 0, 0, 0, 0, 1,  1, 1, 0, 0, 0, 0, 1, 1,
      1, 9, 9, 9, 9, 9, 0, 1,  1, 9, 0, 9, 9, 0, 0, 1,
      1, 1, 0, 0, 0, 1, 0, 1,  1, 1, 0, 0, 1, 1, 0, 1,
      1, 2, 0, 9, 0, 0, 0, 1,  1, 9, 9, 0, 9, 9, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    }
  },
  {
    { // 4 LAB
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 9, 9, 1,  1, 0, 0, 0, 0, 0, 9, 1,
      1, 0, 1, 0, 1, 1, 1, 1,  1, 1, 1, 0, 1, 1, 1, 1,
      1, 0, 9, 0, 9, 0, 0, 2,  0, 0, 0, 0, 9, 9, 0, 1,
      1, 0, 1, 0, 1, 0, 1, 1,  1, 1, 0, 0, 0, 0, 0, 1,
      1, 0, 9, 0, 0, 0, 0, 1,  1, 0, 0, 0, 9, 9, 0, 1,
      1, 0, 0, 0, 1, 1, 0, 1,  1, 0, 1, 0, 0, 0, 0, 1,
      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 9, 9, 9, 9, 2, 1,

      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 0, 1,
      1, 9, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 2, 0, 1, 1, 1, 0, 1,  1, 1, 0, 1, 0, 1, 1, 1,
      1, 9, 0, 9, 0, 9, 0, 1,  1, 9, 0, 9, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 0, 1,  1, 1, 1, 1, 1, 1, 0, 1,
      1, 9, 0, 0, 0, 9, 0, 1,  1, 0, 0, 0, 9, 9, 0, 1,
      1, 1, 0, 1, 0, 0, 0, 0,  2, 0, 1, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 0, 0, 1, 1, 1,  1, 0, 0, 0, 0, 0, 1, 1,
      1, 0, 9, 0, 9, 9, 9, 9,  1, 9, 9, 0, 9, 9, 9, 1,
      1, 0, 1, 0, 1, 0, 0, 2,  0, 0, 0, 0, 1, 1, 0, 1,
      1, 0, 9, 0, 9, 0, 9, 1,  1, 9, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 0, 0, 0, 0, 1,  1, 0, 0, 0, 1, 1, 0, 1,
      1, 0, 0, 0, 9, 9, 0, 1,  1, 0, 9, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 2, 1,

      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 9, 9, 9, 9, 0, 1,
      1, 1, 0, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 2, 0, 9, 9, 9, 0, 1,  1, 9, 0, 9, 0, 9, 9, 1,
      1, 1, 0, 1, 0, 1, 0, 1,  1, 1, 0, 1, 0, 0, 0, 1,
      1, 9, 9, 9, 9, 9, 0, 1,  1, 9, 9, 9, 9, 9, 0, 1,
      1, 1, 0, 0, 0, 1, 0, 1,  1, 0, 0, 0, 1, 1, 0, 1,
      1, 9, 0, 9, 0, 0, 0, 0,  2, 0, 9, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    }
  },
  {
    { // 5 LAB
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 9, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 9, 1,
      1, 0, 1, 1, 0, 1, 0, 1,  1, 1, 1, 0, 1, 0, 0, 1,
      1, 0, 9, 9, 0, 9, 0, 1,  1, 0, 0, 0, 9, 9, 0, 1,
      1, 0, 1, 1, 0, 1, 0, 1,  1, 0, 1, 0, 0, 1, 0, 1,
      1, 0, 9, 9, 0, 9, 0, 2,  0, 0, 9, 9, 9, 9, 0, 1,
      1, 0, 0, 0, 0, 1, 0, 1,  1, 1, 1, 0, 0, 0, 0, 1,
      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 9, 2, 9, 9, 9, 1,

      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 0, 1, 1, 1, 1,
      1, 2, 9, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 1, 1, 0, 1, 0, 1,  1, 1, 1, 1, 1, 1, 0, 1,
      1, 0, 9, 0, 0, 9, 0, 0,  2, 0, 0, 0, 0, 9, 0, 1,
      1, 0, 0, 0, 1, 1, 0, 1,  1, 0, 1, 0, 1, 1, 0, 1,
      1, 0, 9, 0, 0, 9, 0, 1,  1, 0, 9, 0, 9, 9, 0, 1,
      1, 0, 1, 0, 1, 1, 0, 1,  1, 0, 1, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1,
      1, 0, 0, 1, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 1, 1,
      1, 0, 9, 9, 0, 9, 0, 1,  1, 9, 9, 0, 9, 0, 0, 1,
      1, 0, 1, 1, 0, 1, 0, 1,  1, 0, 0, 0, 1, 1, 0, 1,
      1, 0, 9, 9, 0, 9, 0, 1,  1, 0, 9, 0, 0, 9, 0, 1,
      1, 0, 1, 1, 0, 1, 0, 2,  0, 0, 1, 1, 1, 1, 0, 1,
      1, 0, 0, 0, 0, 9, 0, 1,  1, 9, 9, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 2, 1, 1, 1, 1,

      1, 9, 9, 9, 9, 9, 9, 1,  1, 9, 9, 0, 9, 9, 9, 1,
      1, 2, 1, 0, 0, 0, 0, 1,  1, 0, 0, 0, 0, 0, 0, 1,
      1, 0, 9, 9, 0, 9, 0, 1,  1, 9, 9, 9, 9, 9, 0, 1,
      1, 0, 1, 0, 0, 1, 0, 0,  2, 0, 0, 0, 0, 1, 0, 1,
      1, 0, 0, 0, 9, 9, 0, 1,  1, 0, 9, 0, 9, 9, 0, 1,
      1, 0, 1, 0, 0, 1, 0, 1,  1, 0, 1, 0, 1, 1, 0, 1,
      1, 0, 9, 0, 9, 9, 0, 1,  1, 0, 9, 0, 0, 0, 0, 1,
      1, 1, 1, 1, 1, 1, 1, 1,  1, 1, 1, 1, 1, 1, 1, 1
    }
  }
};


byte playerPositionX = 1;
byte playerPositionY = 1;
byte currentRound = 0;
byte life = 5;

int maxLabs = 2;
int up;
int down;
int left;
int right;
int start;

char player = 'z';
//char player = 'p';

bool drawwaiting = true;
bool block;
bool gameend = true;
bool newgame = true;
bool waiting = false;
bool gameready = true;

void setup() {

  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(LEFT, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(START, INPUT);
  Serial.begin(9600);
  //Serial.println("drawLab:");
  matrix.begin();

  // draw a pixel in solid white

  matrix.drawPixel(0, 0, matrix.Color333(7, 7, 7));
  //checkRound();

}

void loop() {

  up = digitalRead(UP);
  down = digitalRead(DOWN);
  left = digitalRead(LEFT);
  right = digitalRead(RIGHT);
  start = digitalRead(START);
  //enable game reset after win or lose
  newGameStarts();
  someoneWaits();



  //disable long press button
  if (up == LOW && down == LOW && left == LOW && right == LOW && block) {
    block = false;
  }

  if (player == 'p') {
    if (life == 0 && !gameend && !waiting) {
      drawGameover();
      gameend = true;
    }

    if (life > 0 && !gameend) {
      if (up == HIGH && !block) {
        movePlayer(1);
        block = true;
      }
      if (down == HIGH && !block) {
        movePlayer(2);
        block = true;
      }
      if (left == HIGH && !block) {
        movePlayer(3);
        block = true;
      }
      if (right == HIGH && !block) {
        movePlayer(4);
        block = true;
      }
    }

  } else if (player == 'w') {
    char movement = 'z';
    if (Serial.available()) {
      movement = reciveData();
    }
    if (life == 0 && !gameend && !waiting) {
      drawGameover();
      gameend = true;
    }

    if (life > 0 && !gameend) {
      if (movement == 'u') {
        movePlayer(1);
      }
      if (movement == 'd') {
        movePlayer(2);
      }
      if (movement == 'l') {
        movePlayer(3);
      }
      if (movement == 'r') {
        movePlayer(4);
      }
    }
  } else {
    if (Serial.available()) {
      player = reciveData();
    }
  }
}

void newGameStarts() {
  if (newgame) {
    if(gameready){
      drawGameReady();
      gameready = false;
    }
    if (start == HIGH && !block) {
      block = true;

      Serial.print('s');
      waiting = true;
      player = 'p';
      newgame = false;
      life = 0;
      drawwaiting = true;
      for (int k = 0; k < sizeof(labyrinth); k++) {
        labyrinth[k] -= 5; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
      }
      block = false;
    }
    if (Serial.available()) {
      char data = reciveData();
      if (data == 's') {
        player = 'w';
        newgame = false;
        waiting = true;
        drawwaiting = true;
        life = 0;
        for (int k = 0; k < sizeof(labyrinth); k++) {
          labyrinth[k] -= 5; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        }
      }
    }
  }
}
void drawGameover() {
  byte i = 0;
  while (i < 2) {
    for (int k = 0; k < sizeof(labyrinth); k++) {
      labyrinth[k] = 0; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
    }
    drawLab((byte*) &labyrinth);
    delay(1000);
    matrix.setCursor(5, 9);   // start at top left, with one pixel of spacing
    matrix.setTextSize(1);    // size 1 == 8 pixels high
    matrix.setTextColor(matrix.Color333(7, 0, 0));
    matrix.print('G');
    matrix.print('A');
    matrix.print('M');
    matrix.print('E');
    matrix.setCursor(5, 18);
    matrix.print('O');
    matrix.print('V');
    matrix.print('E');
    matrix.print('R');
    delay(1000);
    i += 1;
  }
  newgame = true;
  gameready = true;
}

void drawGameReady() {
  for (int k = 0; k < sizeof(labyrinth); k++) {
    labyrinth[k] = 0; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
  }
  drawLab((byte*) &labyrinth);
  matrix.setCursor(5, 9);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1); // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(0, 0, 7));
  matrix.print('G');
  matrix.print('A');
  matrix.print('M');
  matrix.print('E');
  matrix.setCursor(2, 18);
  matrix.print('R');
  matrix.print('E');
  matrix.print('A');
  matrix.print('D');
  matrix.print('Y');
  player = 'z';
}

void someoneWaits() {
  if (waiting) {
    if(drawwaiting){
    drawSomeoneWaits();
    drawwaiting = false;
    }
    if (start == HIGH && !block && player != 'p') {
      block = true;
      Serial.print('w');
      gameend = false;
      playerPositionX = 1;
      playerPositionY = 1;
      currentRound = 0;
      life = 5;
      waiting = false;
      int labNr = random(0, maxLabs + 1);
      Serial.print(labNr);
      for (int k = 0; k < sizeof(labyrinth); k++) {
        labyrinth[k] = labyrinthPool[labNr][0][k];
      }
      block = false;
      checkRound();
    }


    if (Serial.available()) {
      char startcode = reciveData();
      if (startcode == 'a') {
        gameend = false;
        playerPositionX = 1;
        playerPositionY = 1;
        currentRound = 0;
        life = 5;
        waiting = false;
        while (Serial.available() == 0) {
        }
        if (Serial.available()) {
          int incomingByte = reciveData();
          int labNr = (incomingByte - '0');
          for (int k = 0; k < sizeof(labyrinth); k++) {
            labyrinth[k] = labyrinthPool[labNr][1][k];
          }
        }
        checkRound();
      }
    }
  }
}

void drawSomeoneWaits() {
  for (int k = 0; k < sizeof(labyrinth); k++) {
    labyrinth[k] = 0; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
  }
  drawLab((byte*) &labyrinth);
  matrix.setCursor(5, 8);   // start at top left, with one pixel of spacing
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(matrix.Color333(0, 7, 0));
  matrix.print('W');
  matrix.print('A');
  matrix.print('I');
  matrix.print('T');
  matrix.setCursor(7, 18);
  matrix.print('I');
  matrix.print('N');
  matrix.print('G');
}


void draw(byte x, byte y, byte tmp ) {
  x *= 2;
  y *= 2;
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;

  if (tmp == 1) {
    r = 10;
    g = 0;
    b = 50;
  } else if (tmp == 2) {
    r = 214;
    g = 204;
    b = 32;
  } else if (tmp == 3) {
    r = 172;
    g = 163;
    b = 14;
  } else if (tmp == 4) {
    g = 250;
  } else if (tmp == 5) {
    r = 140;
    g = 140;
    b = 14;
  }

  matrix.drawPixel(x, y, matrix.Color888(r, g, b));
  matrix.drawPixel(x, y + 1, matrix.Color888(r, g, b));
  matrix.drawPixel(x + 1, y, matrix.Color888(r, g, b));
  matrix.drawPixel(x + 1, y + 1, matrix.Color888(r, g, b));
}

void drawLab(byte *lab) {

  for (int e = 0; e < 16 * 16; e++) {
    byte tmp = *(lab + e);
    int j = e % 16;
    int i = e / 16;
    draw(j, i, tmp);
  }
  displayLife();
}

void displayLife() {
  if (life > 0) {
    for (int i = 0; i < life + 1; i++) {
      matrix.drawPixel(i, 0, matrix.Color888(10, 0, 50));
    }
  }

  for (int i = 0; i < life; i++) {
    matrix.drawPixel(i, 0, matrix.Color888(255, 0, 0));
  }

  if (gameend) {
    for (int i = 0; i < life + 1; i++) {
      matrix.drawPixel(i, 0, matrix.Color888(0, 0, 0));
    }
  }
}


void checkRound() {
  bool win = 0;
  switch (currentRound) {
    case 0:
      for (int i = 8; i < 16; i++) {
        labyrinth[i] -= 3; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        labyrinth[i + 16] -= 3;
        labyrinth[i + 32] -= 3;
        labyrinth[i + 48] -= 3;
        labyrinth[i + 64] -= 3;
        labyrinth[i + 80] -= 3;
        labyrinth[i + 96] -= 3;
      }
      for (int i = 120; i < sizeof(labyrinth); i++) {
        labyrinth[i] -= 3;
      }
      break;
    case 1:
      for (int i = 8; i < 16; i++) {
        labyrinth[i] += 3; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        labyrinth[i + 16] += 3;
        labyrinth[i + 32] += 3;
        labyrinth[i + 48] += 3;
        labyrinth[i + 64] += 3;
        labyrinth[i + 80] += 3;
        labyrinth[i + 96] += 3;
        labyrinth[i + 112] += 3;
      }
      *(labyrinth + (playerPositionY * 16) + playerPositionX) = 0;
      break;
    case 2:
      for (int k = 136; k < 144; k++) {
        labyrinth[k] += 3; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        labyrinth[k + 16] += 3;
        labyrinth[k + 32] += 3;
        labyrinth[k + 48] += 3;
        labyrinth[k + 64] += 3;
        labyrinth[k + 80] += 3;
        labyrinth[k + 96] += 3;
        labyrinth[k + 112] += 3;
      }

      *(labyrinth + (playerPositionY * 16) + playerPositionX) = 0;
      break;
    case 3:
      for (int k = 128; k < 136; k++) {
        labyrinth[k] += 3; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
        labyrinth[k + 16] += 3;
        labyrinth[k + 32] += 3;
        labyrinth[k + 48] += 3;
        labyrinth[k + 64] += 3;
        labyrinth[k + 80] += 3;
        labyrinth[k + 96] += 3;
        labyrinth[k + 112] += 3;
      }
      *(labyrinth + (playerPositionY * 16) + playerPositionX) = 0;
      break;
    case 4:
      win = true;
      break;
  }

  if (!win) {
    drawLab((byte*) &labyrinth);
    draw(playerPositionX, playerPositionY, 4);
  } else {
    byte i = 0;
    while (i < 2) {
      for (int k = 0; k < sizeof(labyrinth); k++) {
        labyrinth[k] = 0; // 1 wird zu -2; 0 wird zu -3, Info ob 1 oder 0 bleibt erhalten
      }
      drawLab((byte*) &labyrinth);
      delay(1000);
      gameend = true;
      matrix.setCursor(7, 11);   // start at top left, with one pixel of spacing
      matrix.setTextSize(1);    // size 1 == 8 pixels high
      matrix.setTextColor(matrix.Color333(0, 7, 0));
      matrix.print('W');
      matrix.print('I');
      matrix.print('N');
      delay(1000);
      i += 1;
    }
    newgame = true;
    gameready = true;
  }

}


void movePlayer(byte direction) {
  draw(playerPositionX, playerPositionY, *(labyrinth + (playerPositionX + 16 * playerPositionY)));
  //byte temp = labyrinth[playerPositionY-1][playerPositionX];

  byte above = *(labyrinth + (playerPositionY * 16) + playerPositionX - 16);
  byte below = *(labyrinth + (playerPositionY * 16) + playerPositionX + 16);
  byte left = *(labyrinth + (playerPositionY * 16) + playerPositionX - 1);
  byte right = *(labyrinth + (playerPositionY * 16) + playerPositionX + 1);
  /*Serial.print("above: ");
    Serial.println(above);
    Serial.print("below: ");
    Serial.println(below);
    Serial.print("left: ");
    Serial.println(left);
    Serial.print("right: ");
    Serial.println(right);*/
  switch (direction) {
    case 1:
      if ( above == 1 || above == 9) {
        life -= 1;
        displayLife();
        Serial.print('u');
      } else {
        playerPositionY -= 1;
        Serial.print('u');
      }
      break;
    case 2:
      if (  below == 1 || below == 9) {
        life -= 1;
        displayLife();
        Serial.print('d');
      } else {
        playerPositionY += 1;
        Serial.print('d');
      }
      break;
    case 3:
      if (left == 1 || left == 9) {
        life -= 1;
        displayLife();
        Serial.print('l');
      } else {
        playerPositionX -= 1;
        Serial.print('l');
      }
      break;
    case 4:
      if (right == 1 || right == 9) {
        life -= 1;
        displayLife();
        Serial.print('r');
      } else {
        playerPositionX += 1;
        Serial.print('r');
      }
      break;
  }

  draw(playerPositionX, playerPositionY, 4);
  if (*(labyrinth + (playerPositionY * 16) + playerPositionX) == 2) {
    currentRound += 1;
    checkRound();
  }

}

char reciveData() {
  char incomingByte = Serial.read();
  return char(incomingByte);

}

