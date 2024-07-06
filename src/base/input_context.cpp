//
// Created by Denis Topor on 01.07.2024.
//

#include "input_context.hpp"
#include <iostream>

#include "mouse_event.hpp"
#include "scroll_event.hpp"

c_input_context::c_input_context(c_window* _window) {
    window = _window;
}
c_input_context::~c_input_context() {

}

void c_input_context::cursor_callback(int x, int y) {
    /*cursor = BLPointI(x, y);
    c_mouse_event mouse_event;
    mouse_event.position = cursor;
    mouse_event.mouse_event_type = e_mouse_event_type::onmousemove;
    mouse_event.type = e::mouse;
    window->handle_event(&mouse_event);*/

}
void c_input_context::keyboard_callback(int key, int scancode, int action) {
   std::cout << "action " << action << std::endl;
}
void c_input_context::mouse_callback(int button, int action)
{

    /*std::cout << "mouse_callback " << " action " << action << " button " << button << std::endl;

    c_mouse_event mouse_event;
    mouse_event.position = cursor;
    mouse_event.mouse_event_type = action == 1 ?  e_mouse_event_type::onclick : e_mouse_event_type::onmouseup;
    mouse_event.ev_type = e_event_type::mouse;
    window->handle_event(&mouse_event);*/
}

void c_input_context::scroll_callback(float offsetX, float offsetY) {
    /*std::cout << "scroll_callback " << " offsetX " << offsetX << " offsetY " << offsetY << std::endl;

    c_scroll_event scroll_event;
    scroll_event.offset.x = offsetX;
    scroll_event.offset.y = offsetY;

    scroll_event.mouse_pos = cursor;



    window->on_event(&scroll_event);*/
}