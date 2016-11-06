#include <pebble.h>
#include "main.h"

const char resistor_symbols[23] = { 0, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                                    'R', 'A', 'B', 'C', 'D', 'E', 'F', 'H', 'S', 'X', 'Y', 'Z' };

const uint16_t eia_lut[96] = { 100, 102, 105, 107, 110, 113, 115, 118, 121, 124, 127, 130, 133, 137, 140, 143, 147,
                               150, 154, 158, 162, 165, 169, 174, 178, 182, 187, 191, 196, 200, 205, 210, 215, 221,
                               226, 232, 237, 243, 249, 255, 261, 267, 274, 280, 287, 294, 301, 309, 316, 324, 332,
                               340, 348, 357, 365, 374, 383, 392, 402, 412, 422, 432, 442, 453, 464, 475, 487, 499,
                               511, 523, 536, 549, 562, 576, 590, 604, 619, 634, 649, 665, 681, 698, 715, 732, 750,
                               768, 787, 806, 825, 845, 866, 887, 909, 931, 953, 976 };

bool is_digit(uint8_t v) {
  if (resvalue[v] < 11)
    return true;
  else
    return false;
}

void refresh_display(Layer *layer, GContext *ctx) {
  
  // Erase cursor
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, GRect(32, 58, 112, 4), 0, GCornerNone);
  
  // Draw cursor
  if (cursor) {
    graphics_context_set_fill_color(ctx, GColorBlack);
    graphics_fill_rect(ctx, GRect(32 + (edit_idx * 10), 58, 10, 4), 0, GCornerNone);
  }
  
}

void update_value() {
  uint16_t val;
  
  for (c = 0; c < 4; c++) {
    buff_number[c] = resistor_symbols[resvalue[c]];
    if (!buff_number[c]) break;
  }
  
  if ((c == 1) && is_digit(0)) {
    snprintf(buff_info, 32, "%u ohms", resvalue[0] - 1);
  } else if ((c == 2) && is_digit(0) && is_digit(1)) {
    snprintf(buff_info, 32, "%u ohms", (resvalue[0] - 1) * 10 + (resvalue[1] - 1));
  } else if ((c == 3) && is_digit(0) && !is_digit(1) && is_digit(2)) {
    snprintf(buff_info, 32, "%u.%u ohms", resvalue[0] - 1, resvalue[2] - 1);      // xRy
  } else if ((c == 3) && is_digit(0) && is_digit(1) && !is_digit(2)) {
    // EIA-96 code
    val = (resvalue[0] - 1) * 10 + (resvalue[1] - 1);
    if ((val == 0) || (val > 96)) {
      snprintf(buff_info, 32, "Invalid !");
    } else {
      val = eia_lut[val - 1];
      if (resvalue[2] == 12)  // A
        snprintf(buff_info, 32, "%u ohms", val);
      else if ((resvalue[2] == 13) || (resvalue[2] == 18))  // B or H
        snprintf(buff_info, 32, "%u.%u kohms", val / 100, val % 100);
      else if ((resvalue[2] == 14))                         // C
        snprintf(buff_info, 32, "%u.%u kohms", val / 10, val % 10);
      else if ((resvalue[2] == 15))                         // D
        snprintf(buff_info, 32, "%u kohms", val);
      else if ((resvalue[2] == 16))                         // E
        snprintf(buff_info, 32, "%u.%u Mohms", val / 100, val % 100);
      else if ((resvalue[2] == 17))                         // F
        snprintf(buff_info, 32, "%u.%u Mohms", val / 10, val % 10);
      else if ((resvalue[2] == 19) || (resvalue[2] == 20))  // S or X
        snprintf(buff_info, 32, "%u.%u ohms", val / 10, val % 10);
      else if ((resvalue[2] == 11) || (resvalue[2] == 21))  // R or Y
        snprintf(buff_info, 32, "%u.%u ohms", val / 100, val % 100);
      else if ((resvalue[2] == 11) || (resvalue[2] == 21))  // Z
        snprintf(buff_info, 32, "%u mohms", val);
    }
  } else if ((c == 3) && is_digit(0) && is_digit(1) && is_digit(2)) {
    val = (resvalue[0] - 1) * 10 + (resvalue[1] - 1);
    if ((resvalue[2] - 1) == 0) {
      snprintf(buff_info, 32, "%u ohms", val);
    } else if ((resvalue[2] - 1) == 1) {
      snprintf(buff_info, 32, "%u ohms", val * 10);
    } else if ((resvalue[2] - 1) == 2) {
      snprintf(buff_info, 32, "%u.%u kohms", val / 10, val % 10);
    } else if ((resvalue[2] - 1) == 3) {
      snprintf(buff_info, 32, "%u kohms", val);
    } else if ((resvalue[2] - 1) == 4) {
      snprintf(buff_info, 32, "%u kohms", val * 10);
    } else if ((resvalue[2] - 1) == 5) {
      snprintf(buff_info, 32, "%u.%u Mohms", val / 10, val % 10);
    } else if ((resvalue[2] - 1) == 6) {
      snprintf(buff_info, 32, "%u Mohms", val);
    } else if ((resvalue[2] - 1) == 7) {
      snprintf(buff_info, 32, "%u Mohms", val * 10);
    } else if ((resvalue[2] - 1) == 8) {
      snprintf(buff_info, 32, "%u.%u Gohms", val / 10, val % 10);
    } else {
      snprintf(buff_info, 32, "Too damn high !");
    }
  } else if ((c == 4) && is_digit(0) && !is_digit(1) && is_digit(2) && is_digit(3)) {
    snprintf(buff_info, 32, "%u.%u ohms", resvalue[0] - 1, (resvalue[2] - 1) * 10 + (resvalue[3] - 1));      // xRyz
  } else if ((c == 4) && is_digit(0) && is_digit(1) && !is_digit(2) && is_digit(3)) {
    snprintf(buff_info, 32, "%u.%u ohms",  (resvalue[0] - 1) * 10 + (resvalue[1] - 1), resvalue[3] - 1);      // xyRz
  } else if ((c == 4) && is_digit(0) && is_digit(1) && is_digit(2) && is_digit(3)) {
    val = (resvalue[0] - 1) * 100 + (resvalue[1] - 1) * 10 + (resvalue[2] - 1);
    if ((resvalue[3] - 1) == 0) {
      snprintf(buff_info, 32, "%u ohms", val);                        // 9990: 999 ohms
    } else if ((resvalue[3] - 1) == 1) {
      snprintf(buff_info, 32, "%u.%u kohms", val / 100, val % 100);   // 9991: 9990 ohms = 9.99 kohms
    } else if ((resvalue[3] - 1) == 2) {
      snprintf(buff_info, 32, "%u.%u kohms", val / 10, val % 10);     // 9992: 99900 ohms = 99.9 kohms
    } else if ((resvalue[3] - 1) == 3) {
      snprintf(buff_info, 32, "%u kohms", val);                       // 9993: 999000 ohms = 999 kohms
    } else if ((resvalue[3] - 1) == 4) {
      snprintf(buff_info, 32, "%u.%u Mohms", val / 100, val % 100);   // 9994: 9990000 ohms = 9.99 Mohms
    } else if ((resvalue[3] - 1) == 5) {
      snprintf(buff_info, 32, "%u.%u Mohms", val / 10, val % 10);     // 9995: 99900000 ohms = 99.9 Mohms
    } else if ((resvalue[3] - 1) == 6) {
      snprintf(buff_info, 32, "%u Mohms", val);                       // 9996: 999000000 ohms = 999 Mohms
    } else if ((resvalue[3] - 1) == 7) {
      snprintf(buff_info, 32, "%u.%u Gohms", val / 100, val % 100);   // 9997: 9990000000 ohms = 9.99 Gohms
    } else {
      snprintf(buff_info, 32, "Too damn high !");
    }
  } else {
    snprintf(buff_info, 32, "...");
  }
  
  text_layer_set_text(lay_resvalue, buff_number);
  text_layer_set_text(lay_resinfo, buff_info);
  
  layer_mark_dirty(lay_canvas);
}

void win_resistor_click_select(ClickRecognizerRef recognizer, void *context) {
  if ((resvalue[edit_idx]) && (edit_idx < 3)) {
    edit_idx++;
    update_value();
  }
}

void win_resistor_click_back(ClickRecognizerRef recognizer, void *context) {
  if (edit_idx > 0) {
    resvalue[edit_idx] = 0;
    edit_idx--;
    update_value();
  } else {
  	window_stack_pop(true);
  }
}

void win_resistor_click_up(ClickRecognizerRef recognizer, void *context) {
  if (resvalue[edit_idx] < 23) {
    resvalue[edit_idx]++;
    update_value();
  }
}

void win_resistor_click_down(ClickRecognizerRef recognizer, void *context) {
  if (resvalue[edit_idx] > 1) {
    resvalue[edit_idx]--;
    update_value();
  }
}

void win_resistor_click_setup(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, win_resistor_click_up);
  window_single_click_subscribe(BUTTON_ID_DOWN, win_resistor_click_down);
  window_single_click_subscribe(BUTTON_ID_SELECT, win_resistor_click_select);
  window_single_click_subscribe(BUTTON_ID_BACK, win_resistor_click_back);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  cursor ^= 1;
  layer_mark_dirty(lay_canvas);
}

void win_resistor_load(Window *window) {
  Layer * lay_resistor = window_get_root_layer(win_resistor);
  GRect bounds = layer_get_bounds(lay_resistor);
  
  lay_canvas = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  
  lay_resvalue = text_layer_create(GRect(32, 32, 80, 26));
  text_layer_set_font(lay_resvalue, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  lay_resinfo = text_layer_create(GRect(16, 68, 128, 26));
  
  layer_add_child(lay_resistor, lay_canvas);
  layer_add_child(lay_canvas, text_layer_get_layer(lay_resvalue));
  layer_add_child(lay_canvas, text_layer_get_layer(lay_resinfo));
  layer_set_update_proc(lay_canvas, refresh_display);
  
  window_set_click_config_provider(window, win_resistor_click_setup);
  
  for (c = 0; c < 4; c++)
    resvalue[c] = 0;

  edit_idx = 0;
  
  cursor = 0;
  
  tick_timer_service_subscribe(SECOND_UNIT, &tick_handler);
}

void win_resistor_unload(Window *window) {
  tick_timer_service_unsubscribe();
  layer_destroy(lay_canvas);
  text_layer_destroy(lay_resvalue);
  text_layer_destroy(lay_resinfo);
  window_destroy(win_resistor);
}
