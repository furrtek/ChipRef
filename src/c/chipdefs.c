#include <pebble.h>
#include "chipdefs.h"

const chipdef_t chipdefs[CHIPDEFS] = {
  {"74xx00", "Quad 2-NANDs", S74, DIP14, RESOURCE_ID_PDC_74_00},
  {"74xx04", "Hex inverters", S74, DIP14, RESOURCE_ID_PDC_74_04},
  {"74xx08", "Quad 2-ANDs", S74, DIP14, RESOURCE_ID_PDC_74_08},
  {"74xx10", "Triple 3-NANDs", S74, DIP14, RESOURCE_ID_PDC_74_10},
  {"74xx11", "Triple 3-ANDs", S74, DIP14, RESOURCE_ID_PDC_74_11},
  {"74xx20", "Dual 4-NANDs", S74, DIP14, RESOURCE_ID_PDC_74_20},
  {"74xx21", "Dual 4-ANDs", S74, DIP14, RESOURCE_ID_PDC_74_21},
  {"74xx32", "Quad 2-ORs", S74, DIP14, RESOURCE_ID_PDC_74_32}
};

const char category_title[MAX_CAT][16] = {
  "74 series", "CMOS 4000", "Misc."
};
