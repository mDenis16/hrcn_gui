#include <base/app_context.hpp>
#include <base/node.hpp>
#include <base/transitions/transition.hpp>
#include <base/event_listener.hpp>
#include <base/events/mouse_move_event.hpp>
#include <base/events/mouse_enter_event.hpp>
#include <base/events/mouse_exit_event.hpp>
#include <base/events/mouse_down_event.hpp>
#include <base/events/mouse_up_event.hpp>
#include <base/events/types.hpp>
#include <iostream>
c_app_context::c_app_context()
{
}
c_app_context::~c_app_context()
{
}

void c_app_context::execute()
{

    process_events();

    for (auto &transition : _transitions)
    {
        if (transition->executed)
        {
            _transitions.erase(std::remove_if(_transitions.begin(), _transitions.end(), [transition](c_transition *_t)
                                              {
       if ( transition == _t)
        {
           delete transition;
            return true;
        }
        return false; }),
                               _transitions.end());

            continue;
        }
        transition->run();
    }
}

void c_app_context::process_events()
{
    std::lock_guard<std::recursive_mutex> lock(_context_mutext);
    while (!_events.empty())
    {
        auto event = _events.front();
        _events.pop_front();
        process_event(event);
    }
}
void c_app_context::push_event(c_node_event *_event)
{
    std::lock_guard<std::recursive_mutex> lock(_context_mutext);
    _events.push_back(_event);
}

void c_app_context::process_event(c_node_event *event)
{
    if (event->type == e_node_event_type::mouse_move_event)
    {

        c_mouse_move_event *mouse_move_event = event->as<c_mouse_move_event>();
        auto cursor = mouse_move_event->position;

        for (int i = 0; i < _event_listeners.size(); i++)
        {
            auto &listener = _event_listeners.at(i);
            {
                if (listener->node)
                {

                    auto &box = listener->node->box;
                    if (cursor.x > box.x && cursor.y > box.y && cursor.x < box.x + box.w && cursor.y < box.y + box.h)
                    {
                        if (listener->type == e_node_event_type::mouse_move_event)
                        {
                            auto ev = new c_mouse_move_event();
                            ev->position = cursor;
                            ev->target = listener->node;

                            listener->callback((c_node_event *)ev);
                        }
                        else if (listener->type == e_node_event_type::mouse_enter_event && !listener->node->hovering)
                        {
                            auto ev = new c_mouse_enter_event();
                            ev->target = listener->node;

                            listener->callback((c_node_event *)ev);
                            listener->node->hovering = true;
                        }
                    }
                    else
                    {
                        if (listener->type == e_node_event_type::mouse_exit_event && listener->node->hovering)
                        {
                            auto ev = new c_mouse_exit_event();
                            ev->target = listener->node;

                            listener->callback((c_node_event *)ev);
                            listener->node->hovering = false;
                        }
                    }
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < _event_listeners.size(); i++)
        {
            auto &listener = _event_listeners.at(i);
            if (event->type == listener->type)
            {
                if (listener->node)
                {
                    event->target = listener->node;
                    auto &box = listener->node->box;

                    if (listener->type == e_node_event_type::mouse_down_event)
                    {
                        auto cursor = event->as<c_mouse_down_event>()->position;
                        if (cursor.x > box.x && cursor.y > box.y && cursor.x < box.x + box.w && cursor.y < box.y + box.h)
                        {
                            std::cout << "calling listener " << (void *)listener << std::endl;
                            listener->callback(event);
                        }
                    }
                    else if (listener->type == e_node_event_type::mouse_up_event)
                    {
                        auto cursor = event->as<c_mouse_up_event>()->position;
                        if (cursor.x > box.x && cursor.y > box.y && cursor.x < box.x + box.w && cursor.y < box.y + box.h)
                        {
                            std::cout << "calling listener " << (void *)listener << std::endl;
                            listener->callback(event);
                        }
                    }
                }
                if (event->_stop_propagation)
                    break;
            }
        }
    }
}

void c_app_context::add_event_listener(c_node *node, c_event_listener *listener)
{
    std::cout << "add_event_listener " << listener << std::endl;
    _event_listeners.push_back(listener);
}

void c_app_context::remove_transitions_for_node(c_node *node) {
     _transitions.erase(std::remove_if(_transitions.begin(), _transitions.end(), [node](c_transition *transition)
                                          {
       if ( transition->node == node)
        {
              delete transition;
            return true;
        }
        return false; }),
                           _transitions.end());
}
void c_app_context::remove_event_listeners_for_node(c_node *node)
{
    std::cout << " remove_event_listeners_for_node called " << std::endl;
    _event_listeners.erase(std::remove_if(_event_listeners.begin(), _event_listeners.end(), [node](c_event_listener *listener)
                                          {
       if ( listener->node == node)
        {
          //  delete listener;
            return true;
        }
        return false; }),
                           _event_listeners.end());
}
void c_app_context::remove_event_listener(c_event_listener *listener)
{
    _event_listeners.erase(std::remove_if(_event_listeners.begin(), _event_listeners.end(), [listener](c_event_listener *list)
                                          {
        if ( listener == list)
        {
            delete listener;
            return true;
        }
        return false; }),
                           _event_listeners.end());
}
