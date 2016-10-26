#pragma once
#include <pebble.h>

typedef enum {S74 = 0, C4000, ANA, MCU, MISC, MAX_CAT} category_t;
typedef enum {DIP8 = 0, DIP14, DIP14A, DIP16, DIP18, DIP20, MAX_PACKAGES} package_t;

typedef struct pindef {
  const char * str_ptr;
  const uint8_t param;
  // bool polarity;
} pindef_t;

typedef struct packdef {
  const char name[8];
  const uint8_t pincount;
  const uint32_t frame;  // Resource ID
  const char * pinmap;
} packdef_t;

typedef struct chipdef {
  const char ref[8];
  const char desc[16];
  const category_t category;
  const package_t package;
  const uint32_t schematic;  // Resource ID
  const pindef_t * pindef;
} chipdef_t;
