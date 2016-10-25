#pragma once

#define CHIPDEFS 23

typedef struct pindef {
  const char * str_ptr;
  const uint8_t param;
  // bool polarity;
} pindef_t;

typedef enum {DIP8 = 0, DIP14, DIP14A, DIP16, DIP18, DIP20, MAX_PACKAGES} package_t;
typedef enum {S74 = 0, C4000, ANA, MCU, MISC, MAX_CAT} category_t;

typedef struct chipdef {
  const char ref[8];
  const char desc[16];
  const category_t category;
  package_t package;
  const uint32_t schematic;  // Resource ID
  const pindef_t * pindef;
} chipdef_t;

const chipdef_t chipdefs[CHIPDEFS];
const const char category_title[MAX_CAT][16];
const uint32_t package_list[MAX_PACKAGES];
