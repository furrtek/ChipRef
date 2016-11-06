#include <pebble.h>
#include "main.h"
#include "chipdefs.h"

// Todo: Fix 3-pin, 16-pin and 20-pin package pin drawing "scripts" (all DIP8 and DIP14 are OK)
// Todo: Maybe make BUTTON_ID_BACK go back to "overview mode" in chip display, instead of going back to refs menu
// Todo: Remove pin numbering in pin description view. Show big pin number on the bottom left of display
// Todo: Custom storage format for infos and graphics
// Todo: Split frames (DIP8, DIP14...) and power pin placement (+, -) to avoid data duplication
// Todo: Marking translator ? (chip resistor, color code...)

static void update_title(Layer *layer, GContext *ctx) {
  // Just write version
  graphics_context_set_text_color(ctx, GColorBlack);
  graphics_draw_text(ctx, "ChipRef", fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD), GRect(0, -4, 72, 18),
                     GTextOverflowModeWordWrap, GTextAlignmentRight, NULL);
  graphics_draw_text(ctx, "V0.13", fonts_get_system_font(FONT_KEY_GOTHIC_18), GRect(80, -4, 72, 18),
                     GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
}

static void menu_select_callback(int index, void *ctx) {
  cat_id = index;
  
	win_select = window_create();
  window_set_window_handlers(win_select, (WindowHandlers) {
    .load = win_select_load,
    .unload = win_select_unload,
  });
	window_stack_push(win_select, true);
}

static void win_main_load(Window *window) {
  uint8_t cat;
  void * cb;
  
  Layer * lay_main = window_get_root_layer(win_main);
  GRect bounds = layer_get_bounds(lay_main);
  
  lay_title = layer_create(GRect(0, 0, bounds.size.w, 18));
  layer_set_update_proc(lay_title, update_title);
  layer_add_child(lay_main, lay_title);
  
  // Generate category menu items
  for (cat = 0; cat < MAX_CAT; cat++) {
    count = 0;
    
    // Count chips in category
    for (c = 0; c < CHIPDEFS; c++)
      if (chipdefs[c].category == (category_t)cat) count++;
    
    if (count) {
      snprintf(&buff_str[cat][0], 16, "%u chips", count);
      cb = menu_select_callback;
    } else {
      snprintf(&buff_str[cat][0], 16, "Empty");
      cb = NULL;
    }
    
    // Ugly, would be better if generated at compile time
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
  
  // Put menu layer right below app version text
  bounds.origin.y = 18;
  bounds.size.h -= 18;
  
  lay_main_menu = simple_menu_layer_create(bounds, win_main, main_menu_sections, 1, NULL);
  layer_add_child(lay_main, simple_menu_layer_get_layer(lay_main_menu));
}

static void win_main_unload(Window *window) {
  simple_menu_layer_destroy(lay_main_menu);
  layer_destroy(lay_title);
  window_destroy(win_main);
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
