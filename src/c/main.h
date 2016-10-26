#include <pebble.h>
#include "chipdefs.h"

void update_chip(Layer *layer, GContext *ctx);
void win_chip_load(Window *window);
void win_chip_unload(Window *window);

void chip_select_callback(int index, void *ctx);
void win_select_load(Window *window);
void win_select_unload(Window *window);

Window * win_main;
Window * win_select;
Window * win_chip;

Layer * lay_canvas;
Layer * lay_title;
SimpleMenuLayer * lay_main_menu;
SimpleMenuLayer * lay_menu;
SimpleMenuSection main_menu_sections[1];
SimpleMenuItem main_menu_items[MAX_CAT];
SimpleMenuSection menu_items_sections[1];

SimpleMenuItem menu_items_chips[40];        // Enough for now
uint8_t menu_chip_id[40];

uint8_t c, count;
int cat_id, chip_id;
char buff_str[MAX_CAT][16];    // Ugly, gen at compile time
