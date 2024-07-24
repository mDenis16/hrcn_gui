#include <base/app_context.hpp>

#include <base/transitions/transition.hpp>
#include <base/event_listener.hpp>
#include <base/events/mouse_move_event.hpp>
#include <base/events/mouse_enter_event.hpp>
#include <base/events/mouse_exit_event.hpp>
#include <base/events/mouse_down_event.hpp>
#include <base/events/mouse_up_event.hpp>
#include <base/events/types.hpp>
#include <base/yg_enums.hpp>
#include <base/style/style_manager.hpp>
#include <base/node.hpp>
#include <iostream>
#include <algorithm>

c_app_context::c_app_context()
{
    texture = BLImage(1920, 1080, BL_FORMAT_PRGB32);
    image_buffer.resize(1920 * 1080 * 4);
}
c_app_context::~c_app_context()
{
}

void c_app_context::execute()
{

    for (size_t i = 0; i < c_app_context::get_current()->_nodes.size(); i++)
    {
        auto node = c_app_context::get_current()->_nodes.at(i);
        if (node == nullptr)
            continue;
        node->check_for_state_changes();
    }

    for (auto &transition : _transitions)
    {
        if (transition->executed || transition->node == nullptr)
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
    process_events();
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
void c_app_context::process_mouse_move(c_mouse_move_event *event)
{
    for (int i = 0; i < _event_listeners.size(); i++)
    {
        auto &listener = _event_listeners.at(i);
        {
            if (listener->node)
            {
                auto &cursor = event->position;
                auto &box = listener->node->box;
                if (cursor.x > box.x && cursor.y > box.y && cursor.x < box.x + box.w && cursor.y < box.y + box.h)
                {
                    bool overflow = false;
                    if (listener->node->parent)
                    {
                        auto parent_box = listener->node->parent->box;

                        overflow = !(box.y > parent_box.y && box.y + box.h < (parent_box.y + parent_box.h));
                    }

                    if (listener->type == e_node_event_type::mouse_enter_event && !listener->node->hovering)
                    {
                        auto ev = new c_mouse_enter_event();
                        std::cout << "c_mouse_enter_event " << std::endl;
                        ev->target = listener->node;

                        listener->callback((c_node_event *)ev);
                        listener->node->hovering = true;
                    }
                    else if (listener->type == e_node_event_type::mouse_move_event)
                    {
                        auto ev = new c_mouse_move_event();
                        ev->position = cursor;
                        ev->target = listener->node;

                        listener->callback((c_node_event *)ev);
                    }
                }
                else
                {
                    if (listener->type == e_node_event_type::mouse_exit_event && listener->node->hovering)
                    {
                        auto ev = new c_mouse_exit_event();
                        ev->target = listener->node;
                        std::cout << "c_mouse_exit_event " << std::endl;
                        listener->callback((c_node_event *)ev);
                        listener->node->hovering = false;
                    }
                }
            }
        }
    }
}

void c_app_context::process_event(c_node_event *event)
{

    if (event->type == e_node_event_type::mouse_move_event)
        process_mouse_move(event->as<c_mouse_move_event>());
    else
    {
        std::vector<c_event_listener *> absolute_listenrs;

        for (auto &listener : _event_listeners)
        {
            if (listener->absolute)
                absolute_listenrs.push_back(listener);
        }
        std::sort(absolute_listenrs.begin(), absolute_listenrs.end(), [](const c_event_listener *a, const c_event_listener *b)
                  { return a->z_index > b->z_index; });

        process_event_for_listeners(event, absolute_listenrs, true);

        if (event->_stop_propagation)
            return;

        process_event_for_listeners(event, _event_listeners);
    }
}
void c_app_context::process_event_for_listeners(c_node_event *event, std::vector<c_event_listener *> listeners, bool absolute)
{
    for (int i = 0; i < listeners.size(); i++)
    {
        auto &listener = listeners.at(i);
        if (event->type == listener->type)
        {
            if (listener->node == nullptr)
                continue;

            if (event->_stop_propagation)
                continue;

            if (listener->node->absolute && !absolute)
                continue;

            event->target = listener->node;
            auto &box = listener->node->box;
            auto &cursor = event->position;

            bool overflow = false;
            if (listener->node->parent)
            {
                auto parent_box = listener->node->parent->box;

                overflow = (box.y > parent_box.y + parent_box.h) || box.y + box.h < parent_box.y;
            }

            if (!overflow && (cursor.x > box.x && cursor.y > box.y && cursor.x < box.x + box.w && cursor.y < box.y + box.h))
            {

                listener->callback(event);
            }

            if (event->_stop_propagation)
                break;
        }
    }
}

void c_app_context::add_event_listener(c_node *node, c_event_listener *listener)
{
    // std::cout << "add_event_listener " << listener << std::endl;
    _event_listeners.push_back(listener);
}

void c_app_context::remove_transitions_for_node(c_node *node)
{
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
             std::cout << "remove event listener for node" << std::endl;
          //  delete listener;
            return true;
        }
        return false; }),
                           _event_listeners.end());
}
void c_app_context::remove_event_listener(c_event_listener *listener)
{

    std::cout << "listener " << listener << std::endl;
    auto new_end = std::remove_if(_event_listeners.begin(), _event_listeners.end(), [listener](c_event_listener *list)
                                  {
        if (listener == list) {
            std::cout << "removing event listener: " << list << std::endl;
            return true;
        }
        return false; });

    _event_listeners.erase(new_end, _event_listeners.end());

    std::cout << "_event_listeners.size() " << _event_listeners.size() << std::endl;
}

void c_app_context::for_each_node_if(std::function<bool(c_node *)> _if_callback, std::function<void(c_node *)> _callback)
{
    for (auto &node : _nodes)
        if (_if_callback(node))
            _callback(node);
}

std::vector<uint8_t> &c_app_context::get_image_buffer()
{
    return image_buffer;
}

bool c_app_context::render()
{
    

    bool _dirty_layout = false;

    if (!root->require_rerender(_dirty_layout))
        return false;

    std::cout << "c_window::render " << std::endl;

    if (_dirty_layout)
    {
        YGNodeCalculateLayout((YGNodeRef)root->getRef(), 1920.f, 1080.f, YGDirectionLTR);
        std::cout << "c_window::layout update " << std::endl;
        BLPointI point = BLPointI(YGNodeLayoutGetLeft((YGNodeRef)root->getRef()), YGNodeLayoutGetTop((YGNodeRef)root->getRef()));

        root->layout_update(point);
        root->dirty_layout = false;
    }
    BLContext context(texture);
    context.clearAll();

   std::vector<c_node*> absolute_nodes;
    for(auto& node :  c_app_context::get_current()->_nodes) {
        if (node->node_ref == nullptr) {
            std::cout << "found null noderef " << std::endl;
            continue;;
        }
        if ( YGNodeStyleGetPositionType((YGNodeRef)node->getRef()) == YGPositionTypeAbsolute && node->_style->get_z_index()  > 0)
            absolute_nodes.push_back(node);
    }

    root->render(context);

    std::sort(absolute_nodes.begin(), absolute_nodes.end(), [](const c_node* a, const c_node* b)
              { return a->_style->get_z_index() > b->_style->get_z_index(); });
    for(auto& node : absolute_nodes)
        node->render(context);

    context.end();

    BLImageData data;
    texture.getData(&data);

    memcpy(image_buffer.data(), data.pixelData, image_buffer.size());
    root->dirty = false;

    return true;
}

void c_app_context::set_node_root(c_node *node){
    root = node;
}
