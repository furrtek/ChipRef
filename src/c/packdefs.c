#include <pebble.h>
#include "packdefs.h"

const uint32_t pin_shapes[5] = {
  0,                                // 0: Don't draw pin
  RESOURCE_ID_PDC_PINDIP_L_DOWN,    // 1
  RESOURCE_ID_PDC_PINDIP_L_DOWN_S,  // 2
  RESOURCE_ID_PDC_PINDIP_L_UP,      // 3
  RESOURCE_ID_PDC_PINDIP_L_UP_S,    // 4
};

const int8_t pinmap_TO92[] = {
  48, 116,               // Origin
  3, 21, 0, 0, 0, 0      // Repeat 3 times, X+=21, Y+=0, text offset, pin shape ID
  -1                     // End
};

const packdef_t package_TO92 = {
  "TO92",  3,  RESOURCE_ID_PDC_TO92, pinmap_TO92
};

const int8_t pinmap_TO220[] = {
  46, 122,               // Origin
  3, 21, 0, 0, 0, 0      // Repeat 3 times, X+=21, Y+=0, text offset, pin shape ID
  -1                     // End
};

const packdef_t package_TO220 = {
  "TO220",  3,  RESOURCE_ID_PDC_TO220, pinmap_TO220
};

const int8_t pinmap_DIP8[] = {
  38, 108,               // Origin
  4, 18, 0, 3, 10, 1,    // Repeat 4 times, X+=18, Y+=0, text offset, pin shape ID
  92, 23,                // Origin
  4, -18, 0, 3, -15, 3,  // Repeat 4 times, X-=18, Y+=0, text offset, pin shape ID
  -1                     // End
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

const int8_t pinmap_DIP14[] = {
  12, 108,               // Origin
  7, 18, 0, 3, 10, 1,    // Repeat 7 times, X+=18, Y+=0, text offset, pin shape ID
  120, 23,               // Origin
  7, -18, 0, 3, -15, 3,  // Repeat 7 times, X-=18, Y+=0, text offset, pin shape ID
  -1                     // End
};

const packdef_t package_DIP14 = {
  "DIP14",  14,  RESOURCE_ID_PDC_DIP14, pinmap_DIP14
};
const packdef_t package_DIP14A = {
  "DIP14",  14,  RESOURCE_ID_PDC_DIP14A, pinmap_DIP14
};

const int8_t pinmap_DIP16[] = {
  12, 108,               // Origin
  8, 16, 0, 3, 10, 1,    // Repeat 8 times, X+=16, Y+=0, text offset, pin shape ID
  126, 8,                // Origin
  8, -16, 0, 3, -15, 3,  // Repeat 8 times, X-=16, Y+=0, text offset, pin shape ID
  -1                     // End
};

const packdef_t package_DIP16 = {
  "DIP16",  16,  RESOURCE_ID_PDC_DIP16, pinmap_DIP16
};

const packdef_t package_DIP16A = {
  "DIP16",  16,  RESOURCE_ID_PDC_DIP16A, pinmap_DIP16
};

const int8_t pinmap_DIP20[] = {
  11, 118,               // Origin
  10, 12, 0, 3, 10, 1,   // Repeat 10 times, X+=12, text offset, pin shape ID
  124, 8,                // Origin
  12, -13, 0, 3, -15, 3, // Repeat 10 times, X-=13, text offset, pin shape ID
  -1                     // End
};

const packdef_t package_DIP20 = {
  "DIP20",  20,  RESOURCE_ID_PDC_DIP20, pinmap_DIP20
};
