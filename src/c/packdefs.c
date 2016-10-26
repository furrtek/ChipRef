#include <pebble.h>
#include "packdefs.h"
#include "pindefs.h"

const char pinmap_DIP8[] = {
  42, 142,                  // Origin
  0x80 | 4, 18, 0,          // Repeat 4 times, X+18
  97, 32,                   // Origin
  0x80 | 4, 0x40 | 18, 0,   // Repeat 4 times, X-18
  255
};

const packdef_t package_DIP8 = {
  "DIP8",  8,  RESOURCE_ID_PDC_DIP8, pinmap_DIP8
};
const packdef_t package_DIP8A = {
  "DIP8",  8,  RESOURCE_ID_PDC_DIP8A, pinmap_DIP8
};
const packdef_t package_DIP8B = {
  "DIP8",  8,  RESOURCE_ID_PDC_DIP8B, pinmap_DIP8
};
const packdef_t package_DIP8C = {
  "DIP8",  8,  RESOURCE_ID_PDC_DIP8C, pinmap_DIP8
};
const packdef_t package_DIP8D = {
  "DIP8",  8,  RESOURCE_ID_PDC_DIP8D, pinmap_DIP8
};

const char pinmap_DIP14[] = {
  16, 142,                  // Origin
  0x80 | 7, 18, 0,          // Repeat 7 times, X+18
  124, 32,                  // Origin
  0x80 | 7, 0x40 | 18, 0,   // Repeat 7 times, X-18
  255
};

const packdef_t package_DIP14 = {
  "DIP14",  14,  RESOURCE_ID_PDC_DIP14, pinmap_DIP14
};
const packdef_t package_DIP14A = {
  "DIP14",  14,  RESOURCE_ID_PDC_DIP14A, pinmap_DIP14
};
