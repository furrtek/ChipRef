#pragma once

#include <pebble.h>
#include "chipdefs.h"

void update_chip(Layer *layer, GContext *ctx);
void win_chip_load(Window *window);
void win_chip_unload(Window *window);

void chip_select_callback(int index, void *ctx);
void win_select_load(Window *window);
void win_select_unload(Window *window);

void win_resistor_load(Window *window);
void win_resistor_unload(Window *window);

Window * win_main;
Window * win_resistor;
Window * win_select;
Window * win_chip;

Layer * lay_title;
ScrollLayer * lay_scroll;
Layer * lay_canvas;
TextLayer * lay_pinnumber;
TextLayer * lay_pininfo;
SimpleMenuLayer * lay_main_menu;
SimpleMenuLayer * lay_menu;
TextLayer * lay_resvalue;
TextLayer * lay_resinfo;
SimpleMenuSection main_menu_sections[1];
SimpleMenuItem main_menu_items[MAX_CAT + 1];
SimpleMenuSection menu_items_sections[1];

SimpleMenuItem menu_items_chips[40];        // Enough for now
uint8_t menu_chip_id[40];

uint8_t c, count;
uint8_t pin_selected, chip_pincount;
int cat_id, chip_id;
char buff_str[MAX_CAT][16];    // Ugly
char buff_info[32];            // For pin infos
char buff_number[5];
uint8_t resvalue[4];
uint8_t edit_idx;
uint8_t cursor;
