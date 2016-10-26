#include <pebble.h>
#include "packdefs.h"
#include "pindefs.h"

const char pinmap_DIP14[] = {
  16, 142,                  // Origin
  0x80 | 7, 18, 0,          // Repeat 7 times, X+18
  124, 32,                  // Origin
  0x80 | 7, 0x40 | 18, 0,   // Repeat 7 times, X-18
  255
};

const packdef_t package_DIP14 = {
  "DIP14",  14,  RESOURCE_ID_PDC_DIP14,  pinmap_DIP14
};

const packdef_t package_DIP14A = {
  "DIP14",  14,  RESOURCE_ID_PDC_DIP14A,  pinmap_DIP14
};

const packdef_t * package_list[MAX_PACKAGES] = {
  0, &package_DIP14, &package_DIP14A, 0, 0, 0
};
