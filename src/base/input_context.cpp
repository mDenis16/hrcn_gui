//
// Created by Denis Topor on 01.07.2024.
//

#include "input_context.hpp"
#include <iostream>

#include <base/app_context.hpp>

#include "mouse_event.hpp"
#include <base/event_listener.hpp>
#include <base/events/mouse_move_event.hpp>
#include <base/events/mouse_enter_event.hpp>
#include <base/events/mouse_exit_event.hpp>
#include <base/events/mouse_down_event.hpp>
#include <base/events/mouse_up_event.hpp>
#include <base/events/types.hpp>

c_input_context::c_input_context(c_window *_window)
{
    window = _window;
}
c_input_context::~c_input_context()
{
}

void c_input_context::cursor_callback(int x, int y)
{
    cursor = BLPointI(x, y);

    auto ev = new c_mouse_move_event();
    ev->position = cursor;
    c_app_context::get_current()->push_event(ev);

    // std::lock_guard<std::mutex> guard(c_event_listener::_mtx);
    // for (auto &listener : c_event_listener::_listeners)
    // {
    //     if (listener->node)
    //     {
    //         auto &box = listener->node->box;
    //         if (cursor.x > box.x && cursor.y > box.y && cursor.x < box.x + box.w && cursor.y < box.y + box.h)
    //         {
    //             if (listener->type == e_node_event_type::mouse_move_event)
    //             {
    //                 auto ev = new c_mouse_move_event();
    //                 ev->position = cursor;
    //                 ev->target = listener->node;

    //                 listener->callback((c_node_event *)ev);
    //             }
    //             else if (listener->type == e_node_event_type::mouse_enter_event && !listener->node->hovering)
    //             {
    //                 auto ev = new c_mouse_enter_event();
    //                 ev->target = listener->node;

    //                 listener->callback((c_node_event *)ev);
    //                 listener->node->hovering = true;
    //             }
    //         }
    //         else
    //         {
    //             if (listener->type == e_node_event_type::mouse_exit_event && listener->node->hovering)
    //             {
    //                 auto ev = new c_mouse_exit_event();
    //                 ev->target = listener->node;

    //                 listener->callback((c_node_event *)ev);
    //                 listener->node->hovering = false;
    //             }
    //         }
    //     }
    // }
}
void c_input_context::keyboard_callback(int key, int scancode, int action)
{
    std::cout << "action " << action << std::endl;
}
void c_input_context::mouse_callback(int button, int action)
{

    if (action == 1)
    {
        std::cout << "mouse_callback c_mouse_down_event " << std::endl;
        auto ev = new c_mouse_down_event();
        ev->position = cursor;
        c_app_context::get_current()->push_event(ev);
    }
    else
    {
        auto ev = new c_mouse_up_event();
        ev->position = cursor;
        c_app_context::get_current()->push_event(ev);
    }
}

void c_input_context::scroll_callback(float offsetX, float offsetY)
{
    /*std::cout << "scroll_callback " << " offsetX " << offsetX << " offsetY " << offsetY << std::endl;

    c_scroll_event scroll_event;
    scroll_event.offset.x = offsetX;
    scroll_event.offset.y = offsetY;

    scroll_event.mouse_pos = cursor;



    window->on_event(&scroll_event);*/
}