#include <pebble.h>
#include "pindefs.h"

const char str_nc[] = {"Not connected"};
const char str_gnd[] = {"GND"};
const char str_vcc[] = {"VCC"};
const char str_b[] = {"Base"};
const char str_e[] = {"Emitter"};
const char str_c[] = {"Collector"};
const char str_g[] = {"Gate"};
const char str_d[] = {"Drain"};
const char str_s[] = {"Source"};
const char str_vp[] = {"Power (+)"};
const char str_vn[] = {"Power (-)"};
const char str_inAn[] = {"Input %uA"};
const char str_inBn[] = {"Input %uB"};
const char str_inCn[] = {"Input %uC"};
const char str_inDn[] = {"Input %uD"};
const char str_outn[] = {"Output %u"};
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
const char str_trig[] = {"Trigger"};
const char str_thres[] = {"Threshold"};
const char str_vctrl[] = {"Control voltage"};
const char str_miso[] = {"SPI MISO"};
const char str_mosi[] = {"SPI MOSI"};
const char str_sda[] = {"I²C SDA"};
const char str_scl[] = {"I²C SCL"};
const char str_osci[] = {"Oscillator in"};
const char str_osco[] = {"Oscillator out"};
const char str_addrn[] = {"Address A%u"};
const char str_portAn[] = {"Port A pin %u"};
const char str_portBn[] = {"Port B pin %u"};
const char str_portCn[] = {"Port C pin %u"};
const char str_portDn[] = {"Port C pin %u"};
const char str_a[] = {"Anode"};
const char str_k[] = {"Cathode"};
const char str_adj[] = {"Adjust"};
const char str_vref[] = {"Voltage reference"};
const char str_timecap[] = {"Timing capacitor"};
const char str_isense[] = {"Current sense"};
const char str_drive[] = {"Drive supply"};
const char str_gpn[] = {"GPIO %u"};
const char str_din[] = {"Data in"};
const char str_outin[] = {"Inverted output %u"};
const char str_inoutn[] = {"Input/Output %u"};
const char str_outinn[] = {"Output/Input %u"};
const char str_ctrln[] = {"Control %u"};

const pindef_t trans_ebc[3] = { {str_e, 0}, {str_b, 0}, {str_c, 0} };
const pindef_t trans_cbe[3] = { {str_c, 0}, {str_b, 0}, {str_e, 0} };
const pindef_t trans_ecb[3] = { {str_e, 0}, {str_c, 0}, {str_b, 0} };
const pindef_t trans_bce[3] = { {str_b, 0}, {str_c, 0}, {str_e, 0} };
const pindef_t trans_sgd[3] = { {str_s, 0}, {str_g, 0}, {str_d, 0} };
const pindef_t trans_gds[3] = { {str_g, 0}, {str_d, 0}, {str_s, 0} };
const pindef_t reg_igo[3] = { {str_vp, 0}, {str_gnd, 0}, {str_out, 0} };  // +V
const pindef_t reg_ogi[3] = { {str_out, 0}, {str_gnd, 0}, {str_vp, 0} };  // +V
const pindef_t reg_gio[3] = { {str_gnd, 0}, {str_vn, 0}, {str_out, 0} };  // -V
const pindef_t reg_goi[3] = { {str_gnd, 0}, {str_out, 0}, {str_vp, 0} };  // 1117
const pindef_t reg_aio[3] = { {str_adj, 0}, {str_vp, 0}, {str_out, 0} };  // 317

const pindef_t tl431[3] = { {str_vref, 0}, {str_a, 0}, {str_k, 0} };

// Single - OA with offset
const pindef_t oa_1_A[8] = {
  {str_offset, 0}, {str_innn, 1}, {str_innp, 1}, {str_vn, 0},
  {str_offset, 0}, {str_out, 0}, {str_vp, 1}, {str_nc, 0},
};

// NE555 - Unique
const pindef_t ne555[8] = {
  {str_gnd, 0}, {str_trig, 0}, {str_out, 0}, {str_reset, 0},
  {str_vctrl, 0}, {str_thres, 0}, {str_dis, 0}, {str_vcc, 0},
};

// ATTiny - Model A
const pindef_t tiny_A[8] = {
  {str_reset, 0}, {str_portBn, 3}, {str_portBn, 4}, {str_gnd, 0},
  {str_portBn, 0}, {str_portBn, 1}, {str_portBn, 2}, {str_vcc, 0},
};

// ATTiny - Model B
const pindef_t tiny_B[20] = {
  {str_reset, 0},
  {str_portDn, 0}, {str_portDn, 1},
  {str_portAn, 1}, {str_portAn, 0},
  {str_portDn, 2}, {str_portDn, 3}, {str_portDn, 4}, {str_portDn, 5},
  {str_gnd, 0},
  {str_portDn, 6},
  {str_portBn, 0}, {str_portBn, 1}, {str_portBn, 2}, {str_portBn, 3},
  {str_portBn, 4}, {str_portBn, 5}, {str_portBn, 6}, {str_portBn, 7},
  {str_vcc, 0}
};

const pindef_t reg_34063[8] = {
  {str_c, 0}, {str_e, 0}, {str_timecap, 0}, {str_gnd, 0},
  {str_innn, 1}, {str_vcc, 0}, {str_isense, 0}, {str_drive, 0},
};

const pindef_t pic12f675[8] = {
  {str_vcc, 0}, {str_gpn, 5}, {str_gpn, 4}, {str_reset, 0},
  {str_gpn, 2}, {str_gpn, 1}, {str_gpn, 0}, {str_gnd, 0},
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

// Triple - Everyone looks to the right
const pindef_t gates_3_A[14] = {
  {str_inAn, 1}, {str_inBn, 1},
  {str_inAn, 2}, {str_inBn, 2}, {str_inCn, 2}, {str_outn, 2},
  {str_gnd, 0},
  {str_outn, 3}, {str_inAn, 3}, {str_inBn, 3}, {str_inCn, 3},
  {str_outn, 1}, {str_inCn, 1},
  {str_vcc, 0},
};

// Triple - Everyone looks at each other
const pindef_t gates_3_B[14] = {
  {str_inAn, 1}, {str_inBn, 1},
  {str_inAn, 2}, {str_inBn, 2}, {str_inCn, 2}, {str_outn, 2},
  {str_gnd, 0},
  {str_inCn, 1}, {str_outn, 1},
  {str_outn, 3}, {str_inAn, 3}, {str_inBn, 3}, {str_inCn, 3},
  {str_vcc, 0},
};

// Dual - Everyone looks to the right
const pindef_t gates_4_A[14] = {
  {str_inAn, 1}, {str_inBn, 1}, {str_nc, 0}, {str_inCn, 1}, {str_inDn, 1}, {str_outn, 1},
  {str_gnd, 0},
  {str_outn, 2}, {str_inAn, 2}, {str_inBn, 2}, {str_nc, 0}, {str_inCn, 2}, {str_inDn, 2},
  {str_vcc, 0},
};

// Dual - Everyone looks at each other
const pindef_t gates_4_B[14] = {
  {str_outn, 1}, {str_inAn, 1}, {str_inBn, 1}, {str_inCn, 1}, {str_inDn, 1}, {str_nc, 0},
  {str_gnd, 0},
  {str_nc, 0}, {str_inAn, 2}, {str_inBn, 2}, {str_inCn, 2}, {str_inDn, 2}, {str_outn, 2},
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

// Quad - DFF
const pindef_t dff_A[14] = {
  {str_reset, 1}, {str_din, 1}, {str_clk, 1}, {str_set, 1}, {str_outn, 1}, {str_outin, 1},
  {str_gnd, 0},
  {str_outin, 2}, {str_outn, 2}, {str_set, 2}, {str_clk, 2}, {str_din, 2}, {str_reset, 2},
  {str_vcc, 0}
};

// Quad - DFF
const pindef_t dff_B[14] = {
  {str_outn, 1}, {str_outin, 1}, {str_clk, 1}, {str_reset, 1}, {str_din, 1}, {str_set, 1},
  {str_gnd, 0},
  {str_set, 2}, {str_din, 2}, {str_reset, 2}, {str_clk, 2}, {str_outin, 2}, {str_outn, 2},
  {str_vcc, 0}
};

// Quad - Switches
const pindef_t switch_2_A[14] = {
  {str_inoutn, 1}, {str_outinn, 1}, {str_outinn, 2}, {str_inoutn, 2}, {str_ctrln, 2}, {str_ctrln, 3},
  {str_gnd, 0},
  {str_inoutn, 3}, {str_outinn, 3}, {str_outinn, 4}, {str_inoutn, 4}, {str_ctrln, 4}, {str_ctrln, 1},
  {str_vcc, 0}
};

// Single - 8-NAND
const pindef_t gates_8[14] = {
  {str_nc, 0},
  {str_inAn, 1}, {str_inAn, 2}, {str_inAn, 3}, {str_inAn, 4},
  {str_nc, 0},
  {str_gnd, 0},
  {str_nc, 0},
  {str_inAn, 5}, {str_inAn, 6}, {str_inAn, 7}, {str_inAn, 8},
  {str_out, 1}, 
  {str_vcc, 0}
};

// Hex - Everyone looks to the left
const pindef_t gates_1_B[16] = {
  {str_vcc, 0},
  {str_outn, 1}, {str_inAn, 1},
  {str_outn, 2}, {str_inAn, 2},
  {str_outn, 3}, {str_inAn, 3},
  {str_gnd, 0},
  {str_inAn, 4}, {str_outn, 4},
  {str_inAn, 4}, {str_outn, 4},
  {str_nc, 0},
  {str_inAn, 4}, {str_outn, 4},
  {str_nc, 0}
};
