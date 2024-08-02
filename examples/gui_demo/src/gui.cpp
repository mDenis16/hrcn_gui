//
// Created by Denis Topor on 31.07.2024.
//

#include "gui.h"
#include <base/base.hpp>
#include <base/app.hpp>
#include <base/app_context.hpp>
#include <base/font_face.hpp>
#include <base/font.hpp>
#include <components/c_text.hpp>

#include "../components/checkbox.h"
#include "../components/combobox.h"
#include <sstream>
c_gui::c_gui() {
   app = new c_app(1280, 720);
   input_context = new c_input_context();
   c_app_context::set_current(app->ctx);


}
c_gui::~c_gui() {


}

void c_gui::setup() {


   auto sfns_font_face = new c_font_face();
   sfns_font_face->from_file("/System/Library/Fonts/SFNS.ttf");

   auto sfns_font = new c_font(sfns_font_face, 16);

   auto some_text = new c_text();
   some_text->set_string(create_secure_string_runtime("Merge"));
   some_text->set_font(sfns_font);
   some_text->style().color(c_color(255,255,255,255));


   auto body = new c_node();

   body->set_node_identifier<"Root">();
   app->set_root(body);


   std::cout << "node sizze after set root " << app->ctx->_nodes.size() << std::endl;

   body->set_debug_descriptor("Body node");
   body->style()
      .width(1280)
      .height(720)
      .background_color(c_color(255,0,0,255))
      .border_color(c_color(0,255,0,255))
      .display(e_display::flex)
   .align_items(e_align::center)
   .justify_content(e_justify::center);

   auto checkbox = new c_checkbox();

   std::vector<runtime_secure_string> items;

   for (int i = 0; i < 30; ++i) {
      std::stringstream ss;
      ss << "Item " << i;

      const char* s =ss.str().c_str();
      items.push_back( create_secure_string_runtime(s));

   }
   auto combo = new c_combobox(sfns_font,
      items);

   body->add_child(combo);
   std::cout << "node sizze after set add child " << app->ctx->_nodes.size() << std::endl;
   body->add_child(checkbox);
   std::cout << "node sizze after set add child " << app->ctx->_nodes.size() << std::endl;
   body->add_child(some_text);
   std::cout << "node sizze after set add child " << app->ctx->_nodes.size() << std::endl;
}

bool c_gui::swap_buffer(std::vector<uint8_t>& buff) {

   app->ctx->execute();
   if (app->ctx->render()) {
      buff = app->ctx->get_image_buffer();
      return  true;
   }
   return  true;
}

void c_gui::cursor_callback(int x, int y)
{
   input_context->cursor_callback(x, y);
}

void c_gui::keyboard_callback(int key, int scancode, int action)
{
   input_context->keyboard_callback(key, scancode, action);
}

void c_gui::mouse_callback(int button, int action)
{
   input_context->mouse_callback(button, action);
}

void c_gui::scroll_callback(float offsetX, float offsetY)
{
   input_context->scroll_callback(offsetX, offsetY);
}
