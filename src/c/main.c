#include <pebble.h>
#include "chipdefs.h"

static Window * win_main;
static Window * win_select;
static Window * win_chip;

static Layer * lay_canvas;
static Layer * lay_title;
static SimpleMenuLayer * lay_main_menu;
static SimpleMenuLayer * lay_menu;
static SimpleMenuSection main_menu_sections[1];
static SimpleMenuItem main_menu_items[MAX_CAT];
static SimpleMenuSection menu_items_sections[1];
static SimpleMenuItem menu_items_chips[32];        // Enough for now

uint8_t c, count;
int chip_id;
char buff_str[MAX_CAT][16];    // Ugly, gen at compile time

static void update_proc(Layer *layer, GContext *ctx) {
  GDrawCommandImage *s_command_inside;
  GDrawCommandImage *s_command_image;
  
  GPoint origin = GPoint(0, 24);

  s_command_image = gdraw_command_image_create_with_resource(RESOURCE_ID_PDC_DIP14);
  s_command_inside = gdraw_command_image_create_with_resource(chipdefs[chip_id].schematic);
  
  gdraw_command_image_draw(ctx, s_command_image, origin);
  gdraw_command_image_draw(ctx, s_command_inside, origin);
  
  graphics_context_set_text_color(ctx, GColorBlack);
  GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  graphics_draw_text(ctx, chipdefs[chip_id].ref, font, GRect(0, 0, 144, 18), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  font = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  graphics_draw_text(ctx, chipdefs[chip_id].desc, font, GRect(0, 18, 144, 18), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  
  gdraw_command_image_destroy(s_command_image);
  gdraw_command_image_destroy(s_command_inside);
}

static void win_chip_load(Window *window) {
  Layer * lay_chip = window_get_root_layer(win_chip);
  GRect bounds = layer_get_bounds(lay_chip);
  
  lay_canvas = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  layer_set_update_proc(lay_canvas, update_proc);
  layer_add_child(lay_chip, lay_canvas);
}

static void win_chip_unload(Window *window) {
  layer_destroy(lay_canvas);
}

static void chip_select_callback(int index, void *ctx) {
  chip_id = index;
  
	win_chip = window_create();
  window_set_window_handlers(win_chip, (WindowHandlers) {
    .load = win_chip_load,
    .unload = win_chip_unload,
  });
	window_stack_push(win_chip, true);
}

static void win_select_load(Window *window) {
  Layer * lay_select = window_get_root_layer(win_select);
  GRect bounds = layer_get_bounds(lay_select);
  
  count = 0;
  
  for (c = 0; c < CHIPDEFS; c++) {
    if (chipdefs[c].category == S74) {
      menu_items_chips[count++] = (SimpleMenuItem) {
        .title = chipdefs[c].ref,
        .callback = chip_select_callback,
        .subtitle = chipdefs[c].desc
      };
    }
  }
  
  menu_items_sections[0] = (SimpleMenuSection) {
    .num_items = count,
    .items = menu_items_chips,
  };
  
  lay_menu = simple_menu_layer_create(bounds, win_select, menu_items_sections, 1, NULL);
  layer_add_child(lay_select, simple_menu_layer_get_layer(lay_menu));
}

static void win_select_unload(Window *window) {
  simple_menu_layer_destroy(lay_menu);
}

static void menu_select_callback(int index, void *ctx) {
	win_select = window_create();
  window_set_window_handlers(win_select, (WindowHandlers) {
    .load = win_select_load,
    .unload = win_select_unload,
  });
	window_stack_push(win_select, true);
}

static void update_proc_a(Layer *layer, GContext *ctx) {
  graphics_context_set_text_color(ctx, GColorBlack);
  GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  graphics_draw_text(ctx, "ChipRef", font, GRect(0, -4, 72, 18), GTextOverflowModeWordWrap, GTextAlignmentRight, NULL);
  font = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  graphics_draw_text(ctx, "V0.1", font, GRect(72, -4, 72, 18), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
}

static void win_main_load(Window *window) {
  uint8_t cat;
  void * cb;
  
  Layer * lay_main = window_get_root_layer(win_main);
  GRect bounds = layer_get_bounds(lay_main);
  
  lay_title = layer_create(GRect(0, 0, bounds.size.w, 18));
  layer_set_update_proc(lay_title, update_proc_a);
  layer_add_child(lay_main, lay_title);
  
  for (cat = 0; cat < MAX_CAT; cat++) {
    count = 0;
    for (c = 0; c < CHIPDEFS; c++)
      if (chipdefs[c].category == (category_t)cat) count++;
    
    if (count) {
      snprintf(&buff_str[cat][0], 16, "%u chips", count);
      cb = menu_select_callback;
    } else {
      snprintf(&buff_str[cat][0], 16, "Empty");
      cb = NULL;
    }
    
    main_menu_items[cat] = (SimpleMenuItem) {
      .title = &category_title[cat][0],
      .callback = cb,
      .subtitle = &buff_str[cat][0]
    };
  }
  
  main_menu_sections[0] = (SimpleMenuSection) {
    .num_items = MAX_CAT,
    .items = main_menu_items,
  };
  
  bounds.origin.y = 18;
  bounds.size.h -= 18;
  
  lay_main_menu = simple_menu_layer_create(bounds, win_main, main_menu_sections, 1, NULL);
  layer_add_child(lay_main, simple_menu_layer_get_layer(lay_main_menu));
}

static void win_main_unload(Window *window) {
  simple_menu_layer_destroy(lay_main_menu);
  layer_destroy(lay_title);
}

static void init(void) {
	win_main = window_create();
  window_set_window_handlers(win_main, (WindowHandlers) {
    .load = win_main_load,
    .unload = win_main_unload,
  });
	window_stack_push(win_main, true);
}

static void deinit(void) {
	window_destroy(win_main);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
