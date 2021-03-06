#include <pebble.h>
#include "main.h"

void update_chip(Layer *layer, GContext *ctx) {
  uint8_t px = 0, py = 0, r, pin_number;
  int8_t add_x, add_y, txt_x, txt_y, txt_ofsx;
  int8_t code;
  uint32_t pin_shape;
  char buff_num[3];
  GFont font;
  GDrawCommandImage * draw_command;
  GDrawCommandImage * draw_command_normal;
  GDrawCommandImage * draw_command_select;
  const packdef_t * packdef;
  const chipdef_t * chipdef;
  const int8_t * pinmap;
  uint8_t mode;
  
  chipdef = &chipdefs[chip_id];
  packdef = chipdef->packdef;
  if (!packdef->frame) return;    // No package frame, error
  
  GPoint origin = GPoint(0, 20);

  // Draw frame
  draw_command = gdraw_command_image_create_with_resource(packdef->frame);
  gdraw_command_image_draw(ctx, draw_command, origin);
  gdraw_command_image_destroy(draw_command);
  // Draw schematic if available
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
  graphics_context_set_stroke_color(ctx, GColorBlack);
  mode = 0;  // Start with "set origin"
  c = 0;
  pin_number = 1;
  txt_ofsx = 0;
  pinmap = packdef->pinmap;
  while ((code = pinmap[c++]) != -1) {
    if (!mode) {
      // Set origin
      px = code;
      py = pinmap[c++] + origin.y;
      mode = 1;
    } else {
      // Repeat and draw
      add_x = pinmap[c++];
      add_y = pinmap[c++];
      txt_x = pinmap[c++];
      txt_y = pinmap[c++];
      pin_shape = pin_shapes[pinmap[c++]];
      if (pin_shape) {
        draw_command_normal = gdraw_command_image_create_with_resource(pin_shape);
        draw_command_select = gdraw_command_image_create_with_resource(pin_shape + 1);
      }
      for (r = 0; r < code; r++) {
        
        if (pin_number == 10)
          txt_ofsx = -3;    // Adjust text alignment for 2-digit numbers
        
        if (!pin_selected) {
          // Overview mode: show pin numbers
          snprintf(buff_num, 3, "%u", pin_number);
          graphics_draw_text(ctx, buff_num, font, GRect(px + txt_x + txt_ofsx, py + txt_y, 16, 14),
                             GTextOverflowModeWordWrap, GTextAlignmentLeft, NULL);
          // Draw pin shape
          if (pin_shape) gdraw_command_image_draw(ctx, draw_command_normal, GPoint(px, py));
        } else {
          // Draw pin shape
          if (pin_shape) {
            if (pin_selected != pin_number)
              gdraw_command_image_draw(ctx, draw_command_normal, GPoint(px, py));
            else
              gdraw_command_image_draw(ctx, draw_command_select, GPoint(px, py));
          }
        }
        
        px += add_x;
        py += add_y;
        pin_number++;
      }
      gdraw_command_image_destroy(draw_command_normal);
      gdraw_command_image_destroy(draw_command_select);
      mode = 0;
    }
  }
}

void refresh_pininfo() {
  const pindef_t * pindef;
  
  if (pin_selected) {    // Just to be sure
    
    snprintf(buff_number, 3, "%u", pin_selected);
    text_layer_set_text(lay_pinnumber, buff_number);
    
    if (!chipdefs[chip_id].pindef) {
      text_layer_set_text(lay_pininfo, "No pinout, sorry :(");  // No pindef yet :(
      return;
    }
    
    pindef = &chipdefs[chip_id].pindef[pin_selected - 1];
    
    snprintf(buff_info, 32, pindef->str_ptr, pindef->param);
    text_layer_set_text(lay_pininfo, buff_info);
  }
}

void pin_info_mode(bool state) {
  if (state) {
    pin_selected = 1;
    layer_set_hidden(text_layer_get_layer(lay_pinnumber), false);
    layer_set_hidden(text_layer_get_layer(lay_pininfo), false);
    refresh_pininfo();
    scroll_layer_set_content_offset(lay_scroll, GPoint(0, -24), true);
  } else {
    pin_selected = 0;
    layer_set_hidden(text_layer_get_layer(lay_pinnumber), true);
    layer_set_hidden(text_layer_get_layer(lay_pininfo), true);
    scroll_layer_set_content_offset(lay_scroll, GPoint(0, 0), true);
  }
}

void win_chip_click_up(ClickRecognizerRef recognizer, void *context) {
  if (!pin_selected) {
    pin_info_mode(true);
    layer_mark_dirty(lay_canvas);
  } else {
    if (pin_selected < chip_pincount) {
      pin_selected++;
      refresh_pininfo();
    } else
      pin_info_mode(false);
  }
  
  layer_mark_dirty(lay_canvas);
}

void win_chip_click_down(ClickRecognizerRef recognizer, void *context) {
  if (!pin_selected) {
    pin_info_mode(true);
  } else {
    if (pin_selected > 1) {
      pin_selected--;
      refresh_pininfo();
    } else
      pin_info_mode(false);
  }
  
  layer_mark_dirty(lay_canvas);
}

void win_chip_click_setup(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, win_chip_click_up);
  window_single_click_subscribe(BUTTON_ID_DOWN, win_chip_click_down);
}

void win_chip_load(Window *window) {
  Layer * lay_chip = window_get_root_layer(win_chip);
  GRect bounds = layer_get_bounds(lay_chip);

  chip_pincount = chipdefs[chip_id].packdef->pincount;
  pin_selected = 0;    // Default view
  
  lay_scroll = scroll_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  scroll_layer_set_content_size(lay_scroll, GSize(bounds.size.w, 192));
  
  lay_canvas = layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  layer_set_update_proc(lay_canvas, update_chip);
  
  lay_pinnumber = text_layer_create(GRect(2, 142, 38, 50));
  text_layer_set_font(lay_pinnumber, fonts_get_system_font(FONT_KEY_LECO_32_BOLD_NUMBERS));
  text_layer_set_text_alignment(lay_pinnumber, GTextAlignmentRight);
  layer_set_hidden(text_layer_get_layer(lay_pinnumber), true);
  lay_pininfo = text_layer_create(GRect(40, 142, bounds.size.w - 40, 50));
  text_layer_set_font(lay_pininfo, fonts_get_system_font(FONT_KEY_GOTHIC_18));
  layer_set_hidden(text_layer_get_layer(lay_pininfo), true);
  
  layer_add_child(lay_chip, scroll_layer_get_layer(lay_scroll));
  scroll_layer_add_child(lay_scroll, lay_canvas);
  scroll_layer_add_child(lay_scroll, text_layer_get_layer(lay_pinnumber));
  scroll_layer_add_child(lay_scroll, text_layer_get_layer(lay_pininfo));
  
  window_set_click_config_provider(window, win_chip_click_setup);
}

void win_chip_unload(Window *window) {
  layer_destroy(lay_canvas);
  text_layer_destroy(lay_pinnumber);
  text_layer_destroy(lay_pininfo);
  scroll_layer_destroy(lay_scroll);
  window_destroy(win_chip);
}
