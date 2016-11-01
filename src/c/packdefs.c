#include <pebble.h>
#include "packdefs.h"

const char pinmap_TO92[] = {
  48, 116,                  // Origin
  0x80 | 3, 21, 0,          // Repeat 3 times, X+21
  255
};

const packdef_t package_TO92 = {
  "TO92",  3,  RESOURCE_ID_PDC_TO92, pinmap_TO92
};

const char pinmap_TO220[] = {
  46, 122,                  // Origin
  0x80 | 3, 21, 0,          // Repeat 3 times, X+21
  255
};

const packdef_t package_TO220 = {
  "TO220",  3,  RESOURCE_ID_PDC_TO220, pinmap_TO220
};

const char pinmap_DIP8[] = {
  42, 118,                  // Origin
  0x80 | 4, 18, 0,          // Repeat 4 times, X+18
  96, 8,                    // Origin
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
  15, 118,                  // Origin
  0x80 | 7, 18, 0,          // Repeat 7 times, X+18
  123, 8,                   // Origin
  0x80 | 7, 0x40 | 18, 0,   // Repeat 7 times, X-18
  255
};

const packdef_t package_DIP14 = {
  "DIP14",  14,  RESOURCE_ID_PDC_DIP14, pinmap_DIP14
};
const packdef_t package_DIP14A = {
  "DIP14",  14,  RESOURCE_ID_PDC_DIP14A, pinmap_DIP14
};

const char pinmap_DIP16[] = {
  13, 118,                  // Origin
  0x80 | 8, 16, 0,          // Repeat 8 times, X+16
  126, 8,                   // Origin
  0x80 | 8, 0x40 | 16, 0,   // Repeat 8 times, X-16
  255
};

const packdef_t package_DIP16 = {
  "DIP16",  16,  RESOURCE_ID_PDC_DIP16, pinmap_DIP16
};

const packdef_t package_DIP16A = {
  "DIP16",  16,  RESOURCE_ID_PDC_DIP16A, pinmap_DIP16
};

const char pinmap_DIP20[] = {
  13, 118,                  // Origin
  0x80 | 10, 12, 0,         // Repeat 10 times, X+12
  124, 8,                   // Origin
  0x80 | 10, 0x40 | 13, 0,  // Repeat 10 times, X-13
  255
};

const packdef_t package_DIP20 = {
  "DIP20",  20,  RESOURCE_ID_PDC_DIP20, pinmap_DIP20
};
