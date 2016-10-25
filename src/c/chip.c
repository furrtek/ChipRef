#include <pebble.h>
#include "main.h"

void update_chip(Layer *layer, GContext *ctx) {
  uint32_t res_id;
  uint8_t num_pins, ofx;
  char buff_num[3];
  
  GDrawCommandImage *s_command_package;
  GDrawCommandImage *s_command_inside;
  
  GPoint origin = GPoint(0, 24);

  res_id = package_list[chipdefs[chip_id].package];
  if (res_id)
    s_command_package = gdraw_command_image_create_with_resource(res_id);
  s_command_inside = gdraw_command_image_create_with_resource(chipdefs[chip_id].schematic);
  
  if (res_id)
    gdraw_command_image_draw(ctx, s_command_package, origin);
  gdraw_command_image_draw(ctx, s_command_inside, origin);
  
  graphics_context_set_text_color(ctx, GColorBlack);
  GFont font = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  graphics_draw_text(ctx, chipdefs[chip_id].ref, font, GRect(0, 0, 56, 18), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  font = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  graphics_draw_text(ctx, chipdefs[chip_id].desc, font, GRect(56, 0, 88, 18), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  
  font = fonts_get_system_font(FONT_KEY_GOTHIC_14);
  num_pins = 14;
  ofx = 0;
  for (c = 0; c < num_pins; c++) {
    snprintf(buff_num, 3, "%u", c + 1);
    if (c == 9) ofx = 4;
    if (c < num_pins / 2)
      graphics_draw_text(ctx, buff_num, font, GRect(16 + (c * 18), 144, 16, 14), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
    else
      graphics_draw_text(ctx, buff_num, font, GRect(250 - (c * 18) - ofx, 32, 16, 14), GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
  }

  if (res_id)
    gdraw_command_image_destroy(s_command_package);
  gdraw_command_image_destroy(s_command_inside);
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
}
