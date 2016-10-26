#pragma once
#include <pebble.h>

typedef enum {S74 = 0, C4000, ANA, MCU, MISC, MAX_CAT} category_t;

typedef struct {
  const char * str_ptr;
  const uint8_t param;
  // bool polarity;
} pindef_t;

typedef struct {
  const char name[8];
  const uint8_t pincount;
  const uint32_t frame;  // Resource ID
  const char * pinmap;
} packdef_t;

typedef struct {
  const char ref[8];
  const char desc[16];
  const category_t category;
  const packdef_t * packdef;
  const uint32_t schematic;  // Resource ID
  const pindef_t * pindef;
} chipdef_t;
