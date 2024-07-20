#include <base/app_context.hpp>
#include <cassert>
#include <base/transitions/transitions_manager.hpp>
#include <base/transitions/transition_position.hpp>
#include <base/transitions/transition_background_color.hpp>
#include <base/transitions/transition_border_color.hpp>
#include <base/node.hpp>
#include <base/yg_enums.hpp>

#include "transition_margin.hpp"

c_transitions_manager::c_transitions_manager(c_node *_node) : node(_node)
{
}
c_transitions_manager::~c_transitions_manager(){
    _list.clear();
}
c_transitions_manager &c_transitions_manager::margin(e_edge edge, float value) {
    auto transition = new c_transition_margin(node, edge, value, milliseconds);
    _list.push_back(transition);
    assert(node->app_context);

    node->app_context->_transitions.push_back(transition);
    return *this;
}
c_transitions_manager &c_transitions_manager::position(e_edge edge, float value)
{

    auto transition = new c_transition_position(node, edge, value, milliseconds);
    _list.push_back(transition);
    assert(node->app_context);

    node->app_context->_transitions.push_back(transition);
    return *this;
}
c_transitions_manager &c_transitions_manager::background_color(c_color color)
{
    
    auto transition = new c_transition_background_color(node, color, milliseconds);
    _list.push_back(transition);
    assert(node->app_context);
    
    node->app_context->_transitions.push_back(transition);
    return *this;
}
c_transitions_manager &c_transitions_manager::border_color(c_color color)
{
    auto transition = new c_transition_border_color(node, color, milliseconds);
    _list.push_back(transition);
    assert(node->app_context);

    node->app_context->_transitions.push_back(transition);
    return *this;
}