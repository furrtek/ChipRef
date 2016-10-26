#include <pebble.h>
#include "main.h"

void update_chip(Layer *layer, GContext *ctx) {
  uint8_t num_pins, px = 0, py = 0, r, pin_number;
  int8_t add_x, add_y;
  char code;
  char buff_num[3];
  GFont font;
  GDrawCommandImage * draw_command;
  const packdef_t * packdef;
  const chipdef_t * chipdef;
  const char * pinmap;
  
  chipdef = &chipdefs[chip_id];
  packdef = chipdef->packdef;
  if (!packdef->frame) return;    // No package frame, error
  
  GPoint origin = GPoint(0, 24);

  // Draw frame
  draw_command = gdraw_command_image_create_with_resource(packdef->frame);
  gdraw_command_image_draw(ctx, draw_command, origin);
  gdraw_command_image_destroy(draw_command);
  // Draw schematic
  if (chipdef->schematic) {
    draw_command = gdraw_command_image_create_with_resource(chipdef->schematic);
    gdraw_command_image_draw(ctx, draw_command, origin);
    gdraw_command_image_destroy(draw_command);
  }
  
  // Write reference and description
  graphics_context_set_text_color(ctx, GColorBlack);
  font = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  graphics_draw_text(ctx, chipdef->ref, font, GRect(0, 0, 56, 18), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  font = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  graphics_draw_text(ctx, chipdef->desc, font, GRect(56, 0, 88, 18), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  
  // Draw pin numbers
  font = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  //num_pins = packdef->pincount;
  c = 0;
  pin_number = 1;
  pinmap = packdef->pinmap;
  while ((code = pinmap[c++]) != 0xFF) {
    if (!(code & 0x80)) {
      // Origin
      px = code;
      py = pinmap[c++];
    } else {
      // Repeat
      code &= 0x7F;
      add_x = pinmap[c++];
      if (add_x > 0x40) add_x = -(add_x & 0x3F);
      add_y = pinmap[c++];
      if (add_y > 0x40) add_y = -(add_y & 0x3F);
      for (r = 0; r < code; r++) {
        if (pin_number == 10)
            px -= 3;    // Adjust for 2-digit numbers
        snprintf(buff_num, 3, "%u", pin_number);
        graphics_draw_text(ctx, buff_num, font, GRect(px, py, 16, 14), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
        px += add_x;
        py += add_y;
        pin_number++;
      }
    }
  }
}

void win_chip_load(Window *window) {
  Layer * lay_chip = window_get_root_layer(win_chip);
  GRect bounds = layer_get_bounds(lay_chip);
  
  lay_canvas = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  layer_set_update_proc(lay_canvas, update_chip);
  layer_add_child(lay_chip, lay_canvas);
}

void win_chip_unload(Window *window) {
  layer_destroy(lay_canvas);
  window_destroy(win_chip);
}
