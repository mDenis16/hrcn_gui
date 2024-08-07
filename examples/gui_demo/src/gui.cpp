#include <blend2d.h>
#include "gui.h"
#include <base/app.hpp>
#include <base/app_context.hpp>
#include <base/state.hpp>
#include <base/effect.hpp>h
#include <base/style/style_manager.hpp>
#include <base/transitions/transitions_manager.hpp>
#include <base/transitions/transitions_manager.hpp>
#include <base/transitions/transition_margin.hpp>
#include <base/input_context.hpp>
#include <base/events/mouse_move_event.hpp>
#include <base/events/types.hpp>
#include <base/node.hpp>
#include <base/yg_enums.hpp>
#include <base/font.hpp>
#include <base/font_face.hpp>


c_gui::c_gui(int width, int height)
{
    this->width = width;
    this->height = height;
    app = new c_app(width, height);

}

c_gui::~c_gui()
{
}


void c_gui::setup()
{
    app = new c_app(width, height);
    input_context = new c_input_context();

    c_app_context::set_current(app->ctx);

    auto body = new c_node();
    body->style()
        .width(1280)
        .height(720)
        .set_flex_wrap(e_wrap::wrap);

    body->set_node_identifier<"Root">();
    app->set_root(body);

    auto window = new c_node();
    body->add_child(window);

    window->style()
        .display(e_display::flex)
        .height(600.f)

        .flex_direction(e_flex_direction::column)
        .position_type(e_position::position_type_absolute)
        .gap(e_gutter::all, 4)
        .background_color(c_color(25, 12, 123, 255));

    body->add_child(window);
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

bool c_gui::swap_buffer(std::vector<uint8_t> &buffer)
{
    app->ctx->execute();
    if (app->ctx->render())
    {
        memcpy(buffer.data(), app->ctx->get_image_buffer().data(), app->ctx->get_image_buffer().size());
        return true;
    }

    return false;
}