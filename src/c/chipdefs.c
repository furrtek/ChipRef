#include <pebble.h>
#include "packdefs.h"
#include "chipdefs.h"
#include "pindefs.h"

const chipdef_t chipdefs[CHIPDEFS] = {
  {"74xx00",    "Quad 2-NANDs",    S74,   &package_DIP14,   RESOURCE_ID_PDC_74_00,    gates_2_A},
  {"74xx02",    "Quad 2-NORs",     S74,   &package_DIP14,   RESOURCE_ID_PDC_74_02,    gates_2_B},
  {"74xx04",    "Hex inverters",   S74,   &package_DIP14,   RESOURCE_ID_PDC_74_04,    gates_1_A},
  {"74xx08",    "Quad 2-ANDs",     S74,   &package_DIP14,   RESOURCE_ID_PDC_74_08,    gates_2_A},
  {"74xx10",    "Triple 3-NANDs",  S74,   &package_DIP14,   RESOURCE_ID_PDC_74_10,    NULL},
  {"74xx11",    "Triple 3-ANDs",   S74,   &package_DIP14,   RESOURCE_ID_PDC_74_11,    NULL},
  {"74xx20",    "Dual 4-NANDs",    S74,   &package_DIP14,   RESOURCE_ID_PDC_74_20,    NULL},
  {"74xx21",    "Dual 4-ANDs",     S74,   &package_DIP14,   RESOURCE_ID_PDC_74_21,    NULL},
  {"74xx27",    "Triple 3-NORs",   S74,   &package_DIP14,   RESOURCE_ID_PDC_74_27,    NULL},
  {"74xx32",    "Quad 2-ORs",      S74,   &package_DIP14,   RESOURCE_ID_PDC_74_32,    gates_2_A},
  {"74xx74",    "Dual DFF",        S74,   &package_DIP14,   RESOURCE_ID_PDC_74_74,    NULL},
  {"74xx86",    "Quad 2-XORs",     S74,   &package_DIP14,   RESOURCE_ID_PDC_74_86,    gates_2_A},
  {"4001",      "Quad 2-NORs",     C4000, &package_DIP14,   RESOURCE_ID_PDC_4001,     gates_2_C},
  {"4002",      "Dual 4-NORs",     C4000, &package_DIP14,   RESOURCE_ID_PDC_4002,     NULL},
  {"4011",      "Quad 2-NANDs",    C4000, &package_DIP14,   RESOURCE_ID_PDC_4011,     gates_2_C},
  {"4012",      "Dual 4-NANDs",    C4000, &package_DIP14,   RESOURCE_ID_PDC_4012,     NULL},
  {"4013",      "Dual DFF",        C4000, &package_DIP14,   RESOURCE_ID_PDC_4013,     NULL},
  {"4016",      "Quad bi-switch",  C4000, &package_DIP14,   RESOURCE_ID_PDC_4016,     NULL},
  {"4023",      "Triple 3-NANDs",  C4000, &package_DIP14,   RESOURCE_ID_PDC_4023,     NULL},
  {"4025",      "Triple 3-NORs",   C4000, &package_DIP14,   RESOURCE_ID_PDC_4025,     NULL},
  {"4030",      "Quad 2-XORs",     C4000, &package_DIP14,   RESOURCE_ID_PDC_4030,     gates_2_C},
  //{"4049",      "Hex inverters",   C4000, &package_DIP16,   RESOURCE_ID_PDC_4049,     NULL},
  {"4068",      "8-NAND",          C4000, &package_DIP14,   RESOURCE_ID_PDC_4068,     NULL},
  {"NE555",     "Timer",           ANA,   &package_DIP8A,   RESOURCE_ID_PDC_555,      NULL},
  {"LM324",     "Quad OA",         ANA,   &package_DIP14A,  RESOURCE_ID_PDC_LM324,    oa_4_A},
  {"LM741",     "Single OA",       ANA,   &package_DIP8D,   RESOURCE_ID_PDC_LM741,    oa_1_A},
  //{"ATTiny13", "AVR MCU", MCU, DIP8, RESOURCE_ID_PDC_ATTINY13},
  {"Tiny45",    "AVR MCU",         MCU,   &package_DIP8,    RESOURCE_ID_PDC_ATTINYX5, NULL},
  //{"ATTiny2313", "AVR MCU", MCU, DIP20, RESOURCE_ID_PDC_ATTINY2313},
  {"12F675",    "PIC MCU",         MCU,   &package_DIP8B,   RESOURCE_ID_PDC_12F675,   NULL},
  {"2N2222",    "NPN BJT",         TRANS, &package_TO92,    0,                        trans_ebc},
  {"P2N2222",   "NPN BJT",         TRANS, &package_TO92,    0,                        trans_cbe},
  {"2N7000",    "N-Ch MOSFET",     TRANS, &package_TO92,    0,                        trans_sgd},
  {"MC34063",   "Switch. reg.",    REG,   &package_DIP8C,   RESOURCE_ID_PDC_MC34063,  NULL},
  {"78xx",      "Linear reg.",     REG,   &package_TO220,   0,                        reg_igo},
};

const char category_title[MAX_CAT][16] = {
  "74 series", "CMOS 4000", "Analog", "MCUs", "Transistors", "Regulators"
};
