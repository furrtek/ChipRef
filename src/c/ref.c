#include <pebble.h>
#include "main.h"

void chip_select_callback(int index, void *ctx) {
  chip_id = menu_chip_id[index];
  
	win_chip = window_create();
  window_set_window_handlers(win_chip, (WindowHandlers) {
    .load = win_chip_load,
    .unload = win_chip_unload,
  });
	window_stack_push(win_chip, true);
}

void win_select_load(Window *window) {
  Layer * lay_select = window_get_root_layer(win_select);
  GRect bounds = layer_get_bounds(lay_select);
  
  count = 0;
  
  for (c = 0; c < CHIPDEFS; c++) {
    if (chipdefs[c].category == (category_t)cat_id) {
      menu_items_chips[count] = (SimpleMenuItem) {
        .title = chipdefs[c].ref,
        .callback = chip_select_callback,
        .subtitle = chipdefs[c].desc
      };
      menu_chip_id[count] = c;
      count++;
    }
  }
  
  menu_items_sections[0] = (SimpleMenuSection) {
    .num_items = count,
    .items = menu_items_chips,
  };
  
  lay_menu = simple_menu_layer_create(bounds, win_select, menu_items_sections, 1, NULL);
  layer_add_child(lay_select, simple_menu_layer_get_layer(lay_menu));
}

void win_select_unload(Window *window) {
  simple_menu_layer_destroy(lay_menu);
}
