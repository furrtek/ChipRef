#include <pebble.h>
#include "pindefs.h"

const char str_nc[] = {"NC"};
const char str_gnd[] = {"GND"};
const char str_vcc[] = {"VCC"};
const char str_b[] = {"Base"};
const char str_e[] = {"Emitter"};
const char str_c[] = {"Collector"};
const char str_g[] = {"Grid"};
const char str_d[] = {"Drain"};
const char str_s[] = {"Source"};
const char str_vp[] = {"Power (+)"};
const char str_vn[] = {"Power (-)"};
const char str_inAn[] = {"In A%u"};
const char str_inBn[] = {"In B%u"};
const char str_outn[] = {"Out %u"};
const char str_set[] = {"Set"};
const char str_reset[] = {"Reset"};
const char str_clk[] = {"Clock"};
const char str_oe[] = {"Output enable"};
const char str_dir[] = {"Direction"};
const char str_innp[] = {"Input %u (+)"};
const char str_innn[] = {"Input %u (-)"};
const char str_out[] = {"Output"};
const char str_offset[] = {"Offset"};
const char str_dis[] = {"Discharge"};
const char str_thres[] = {"Threshold"};
const char str_miso[] = {"MISO"};
const char str_mosi[] = {"MOSI"};
const char str_sda[] = {"SDA"};
const char str_scl[] = {"SCL"};
const char str_osci[] = {"Osc. in"};
const char str_osco[] = {"Osc. out"};
const char str_addrn[] = {"Address A%u"};

// Single - OA with offset
const pindef_t oa_1_A[8] = {
  {str_offset, 0}, {str_innn, 1}, {str_innp, 1}, {str_vn, 0},
  {str_offset, 0}, {str_out, 0}, {str_vp, 1}, {str_nc, 0},
};

// Quad - Everyone looks to the right
const pindef_t gates_2_A[14] = {
  {str_inAn, 1}, {str_inBn, 1}, {str_outn, 1},
  {str_inAn, 2}, {str_inBn, 2}, {str_outn, 2},
  {str_gnd, 0},
  {str_outn, 3}, {str_inAn, 3}, {str_inBn, 3},
  {str_outn, 4}, {str_inAn, 4}, {str_inBn, 4},
  {str_vcc, 0},
};

// Quad - Everyone looks to the left
const pindef_t gates_2_B[14] = {
  {str_outn, 1}, {str_inAn, 1}, {str_inBn, 1},
  {str_outn, 2}, {str_inAn, 2}, {str_inBn, 2},
  {str_gnd, 0},
  {str_inAn, 3}, {str_inBn, 3}, {str_outn, 3},
  {str_inAn, 4}, {str_inBn, 4}, {str_outn, 4},
  {str_vcc, 0},
};

// Quad - Everyone looks at each other
const pindef_t gates_2_C[14] = {
  {str_inAn, 1}, {str_inBn, 1}, {str_outn, 1},
  {str_outn, 2}, {str_inAn, 2}, {str_inBn, 2},
  {str_gnd, 0},
  {str_inAn, 3}, {str_inBn, 3}, {str_outn, 3},
  {str_outn, 4}, {str_inAn, 4}, {str_inBn, 4},
  {str_vcc, 0},
};

// Hex - Everyone looks to the right
const pindef_t gates_1_A[14] = {
  {str_inAn, 1}, {str_outn, 1},
  {str_inAn, 2}, {str_outn, 2},
  {str_inAn, 3}, {str_outn, 3},
  {str_gnd, 0},
  {str_outn, 4}, {str_inAn, 4},
  {str_outn, 5}, {str_inAn, 5},
  {str_outn, 6}, {str_inAn, 6},
  {str_vcc, 0},
};

// Quad - OA
const pindef_t oa_4_A[14] = {
  {str_outn, 1}, {str_innn, 1}, {str_innp, 1},
  {str_vp, 0},
  {str_innp, 2}, {str_innn, 2}, {str_outn, 2},
  {str_outn, 3}, {str_innn, 3}, {str_innp, 3},
  {str_vn, 0},
  {str_innp, 4}, {str_innn, 4}, {str_outn, 4},
};

const pindef_t trans_ebc[3] = { {str_e, 0}, {str_b, 0}, {str_c, 0} };
const pindef_t trans_cbe[3] = { {str_c, 0}, {str_b, 0}, {str_e, 0} };
const pindef_t trans_sgd[3] = { {str_s, 0}, {str_g, 0}, {str_d, 0} };
const pindef_t reg_igo[3] = { {str_vp, 0}, {str_gnd, 0}, {str_out, 0} };
