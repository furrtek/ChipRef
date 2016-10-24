#pragma once

#define CHIPDEFS 8

typedef enum {DIP14 = 0, DIP16, DIP20} package_t;
typedef enum {S74 = 0, CMOS4000, MISC, MAX_CAT} category_t;

typedef struct chipdef {
  char ref[8];
  char desc[16];
  category_t category;
  package_t package;
  uint32_t schematic;  // Resource ID
} chipdef_t;

const chipdef_t chipdefs[CHIPDEFS];
const const char category_title[MAX_CAT][16];
