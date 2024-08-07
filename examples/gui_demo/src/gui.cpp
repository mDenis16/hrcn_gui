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
#include <blend2d/fonttagdata_p.h>
#include <sstream>
c_gui::c_gui(int width, int height) {
   app = new c_app(width, height);
   input_context = new c_input_context();
   c_app_context::set_current(app->ctx);
   this->width =width;
   this->height = height;

}
c_gui::~c_gui() {


}
enum class e_colors : uint8_t
{
    blue_100,
    blue_200,
    blue_300,
    blue_400,
    blue_500,
    blue_600,
    blue_700,
    blue_800,
    blue_800_20,
    blue_800_40,
    blue_850,
    blue_900,
    blue_900_70,
    blue_900_75,
    blue_900_80,
    blue_900_85,
    blue_900_90,
    blue_900_95,
    blue_950,
    blue_950_50,
    blue_950_70,
    blue_950_80,
    blue_950_90,
    blue_975,
    blue_1000,
    blue_1000_75,
    blue_1000_80,
    blue_1000_85,
    blue_1000_90,
    blue_1000_95,
    danger
};

std::unordered_map<e_colors, c_color> colors_map =
{
    { e_colors::blue_100, c_color(235, 242, 248, 255) },
    { e_colors::blue_200, c_color(215, 229, 241, 255) },
    { e_colors::blue_300, c_color(195, 217, 233, 255) },
    { e_colors::blue_400, c_color(175, 204, 226, 255) },
    { e_colors::blue_500, c_color(155, 191, 219, 255) },
    { e_colors::blue_600, c_color(100, 156, 199, 255) },
    { e_colors::blue_700, c_color(65, 118, 159, 255) },
    { e_colors::blue_800, c_color(55, 99, 134, 255) },
    { e_colors::blue_800_20, c_color(55, 99, 134, 51) },
    { e_colors::blue_800_40, c_color(55, 99, 134, 102) },
    { e_colors::blue_850, c_color(30, 59, 82, 255) },
    { e_colors::blue_900, c_color(20, 40, 55, 255) },
    { e_colors::blue_900_70, c_color(20, 40, 55, 0.7 * 255) },
    { e_colors::blue_900_75, c_color(20, 40, 55, 0.75 * 255) },
    { e_colors::blue_900_80, c_color(20, 40, 55, 0.8 * 255) },
    { e_colors::blue_900_85, c_color(20, 40, 55, 0.85 * 255) },
    { e_colors::blue_900_90, c_color(20, 40, 55, 0.9 * 255) },
    { e_colors::blue_900_95, c_color(20, 40, 55, 0.95 * 255) },
    { e_colors::blue_950, c_color(15, 30, 41, 255) },
    { e_colors::blue_950_50, c_color(15, 30, 41, 0.5 * 255) },
    { e_colors::blue_950_70, c_color(15, 30, 41, 0.7 * 255) },
    { e_colors::blue_950_80, c_color(15, 30, 41, 0.8 * 255) },
    { e_colors::blue_950_90, c_color(15, 30, 41, 0.9 * 255) },
    { e_colors::blue_975, c_color(12, 24, 34, 255) },
    { e_colors::blue_1000, c_color(10, 20, 28, 255) },
    { e_colors::blue_1000_75, c_color(10, 20, 28, 0.75 * 255) },
    { e_colors::blue_1000_80, c_color(10, 20, 28, 0.8 * 255) },
    { e_colors::blue_1000_85, c_color(10, 20, 28, 0.85 * 255) },
    { e_colors::blue_1000_90, c_color(10, 20, 28, 0.9 * 255) },
    { e_colors::blue_1000_95, c_color(10, 20, 28, 0.95 * 255) },
    { e_colors::danger, c_color(236, 120, 120, 255) }
};
void c_gui::setup() {


   auto sfns_font_face = new c_font_face();
   sfns_font_face->from_file("/Users/denistopor/Library/Fonts/SpaceGrotesk-Bold.ttf");



   auto sfns_font = new c_font(sfns_font_face, 18 );
   c_node::default_font = sfns_font;



 //  BLFontVariationSettings settings;
   //settings.setValue(bl::FontTagData::variationIdToTagTable[4], BL_FONT_WEIGHT_EXTRA_BOLD   );

   //sfns_font->_font.setVariationSettings(settings);

   std::cout << "  sfns_font->_font " <<   sfns_font->_font.variationSettings().getValue(bl::FontTagData::variationIdToTagTable[4]);
   auto some_text = new c_text();
   some_text->set_string(create_secure_string_runtime("Grupul Industrial HURRACAN SI Compania AXE SOFTWARE"));
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
      .display(e_display::flex)
   .justify_content(e_justify::center)
   .align_items(e_align::center)
      .background_color(c_color(255, 0, 0,255))
      .display(e_display::flex);


  auto sampel = new c_node();
   sampel->style()
   .display(e_display::flex)
   .justify_content(e_justify::center)
   .align_items(e_align::center)
   .background_color(colors_map[e_colors::blue_300])


   .border_width(e_edge::right, 5.f)
   .border_width(e_edge::top, 5.f)

   .border_radius(e_corner::right_top,50.f)
   .border_radius(e_corner::left_top,50.f)
   .border_radius(e_corner::left_bottom,50.f)
   .border_radius(e_corner::right_bottom,50.f)


   .border_color(e_edge::top, c_color(0,255,0,255))
   .border_color(e_edge::left, c_color(0,0,255,255))
   .border_color(e_edge::bottom, c_color(0,255,0,255))
   .border_color(e_edge::right, c_color(0,0,255,255))
   .width(500)
   .height(500);

   sampel->add_event_listener(e_node_event_type::mouse_down_event, [sampel](c_node_event* event) {

      static bool samp = false;
      samp = !samp;
      sampel->transitions(1000).border_color(e_edge::all, samp ? c_color(255,0,0,255) :  c_color(0,255,0,255));

   });

   auto teletext = new c_text();
   teletext->set_font(sfns_font);
   teletext->set_string(create_secure_string_runtime("Grupul Industrial HURRACAN"));
   teletext->style().color(colors_map[e_colors::blue_800]);

   sampel->add_child(teletext);
   body->add_child(sampel);
   return;
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
