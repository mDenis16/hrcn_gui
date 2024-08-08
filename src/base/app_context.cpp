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

c_app_context::c_app_context(int width, int height)
{
    this->width = width;
    this->height = height;
    texture = BLImage(width, height, BL_FORMAT_PRGB32);
    image_buffer.resize(width * height * 4);
}
c_app_context::~c_app_context()
{
}

void c_app_context::execute()
{

    for (size_t i = 0; i < _states.size(); i++)
    {
        auto& state = _states.at(i);
        if (state == nullptr)
            continue;
        if (state->require_update())
            state->consume_update();

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
         delete event;
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
                        auto ev =  c_mouse_enter_event();
                        std::cout << "c_mouse_enter_event " << std::endl;
                        ev->target = listener->node;

                        listener->callback((c_node_event *)&ev);
                        listener->node->hovering = true;
                    }
                    else if (listener->type == e_node_event_type::mouse_move_event)
                    {
                        auto ev =  c_mouse_move_event();
                        ev->position = cursor;
                        ev->target = listener->node;

                        listener->callback((c_node_event *)&ev);
                    }
                }
                else
                {
                    if (listener->type == e_node_event_type::mouse_exit_event && listener->node->hovering)
                    {
                        auto ev =  c_mouse_exit_event();
                        ev->target = listener->node;
                        std::cout << "c_mouse_exit_event " << std::endl;
                        listener->callback((c_node_event *)&ev);
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
        process_event_for_listeners(event, _event_listeners);
    }
}
void c_app_context::process_event_for_listeners(c_node_event *event, std::vector<c_event_listener *> listeners, bool absolute) {
    for (int i = 0; i < listeners.size(); i++)
    {
        auto &listener = listeners.at(i);
        if (event->type != listener->type)
            continue;;

        if (listener->node == nullptr)
            continue;

        if (event->_stop_propagation)
            continue;


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
            event->target = listener->node;
            listener->callback(event);
        }

        if (event->_stop_propagation)
            break;
    }
}

void c_app_context::add_event_listener(c_node *node, c_event_listener *listener)
{
    std::cout << "add_event_listener " << std::endl;
    if (std::find(_event_listeners.begin(), _event_listeners.end(), listener) != _event_listeners.end()) {
        assert("Duplicate event listener");
        return;
    }

    _event_listeners.push_back(listener);


    listener->absolute = node->absolute_anchestor(listener->z_index);


    if ( listener->absolute ) {
        std::cout << "got absolute " << std::endl;
    }
    std::ranges::sort(_event_listeners, [](const c_event_listener *a, const c_event_listener *b)
{

        if ( a->absolute && !b->absolute)
            return true;
        if (b->absolute && !a->absolute)
            return false;

        if (a->absolute == b->absolute)
            return (a->z_index < b->z_index) ;

        return a->node->global_index < b->node->global_index;
});





}

void c_app_context::add_state(c_state* state) {
    if (std::find_if(_states.begin(), _states.end(), [state](c_state* _s) {
        return state == _s;
    }) != _states.end())
        return;


    _states.push_back(state);
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

void c_app_context::add_node(c_node *node) {

    if (std::find(_nodes.begin(), _nodes.end(), node) == _nodes.end()) {
        _nodes.push_back(node);
    }

    std::sort(_nodes.begin(), _nodes.end(), [](c_node* a, c_node* b) {
       return a->style().get_z_index() < b->style().get_z_index();
   });

    for(int i = 0; i < _nodes.size(); i++)
        node->global_index = _nodes.size();


}
void c_app_context::enableHighDPI(float scaleFactor) {
    scale_factor = scaleFactor;
}
bool c_app_context::render()
{

    if (root == nullptr) {
        assert("Root node is null in c_app_context::render()");
        return false;
    }


    bool _dirty_layout = false;

    if (!root->require_rerender(_dirty_layout))
        return false;


    if (_dirty_layout)
    {
        YGNodeCalculateLayout((YGNodeRef)root->getRef(), width, height, YGDirectionLTR);

        BLPointI point = BLPointI(YGNodeLayoutGetLeft((YGNodeRef)root->getRef()), YGNodeLayoutGetTop((YGNodeRef)root->getRef()));

        root->layout_update(point);
    }

    BLContext context(texture);

    context.clearAll();

    if (scale_factor > 1.f) {
        context.setTransform(BLMatrix2D::makeScaling(scale_factor));
        context.userToMeta();
    }

    root->render(context);



    for(auto& node : _nodes) {
        if (node->style().get_z_index() > 0)
             node->render(context);
    }


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

void c_app_context::ensure_state_exist(c_state* state) {
    if (std::find(_states.begin(), _states.end(), state) == _states.end())
        _states.push_back(state);
}

c_node* c_app_context::get_node_by_hash(std::uint32_t hash) {
    auto itx=  std::find_if(_nodes.begin(), _nodes.end(), [hash](c_node* a) {
        return a->identifier == hash;
    });

    if (itx == _nodes.end())
        return  nullptr;

    return *itx;
}
