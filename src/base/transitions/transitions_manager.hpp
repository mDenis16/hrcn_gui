#pragma once
#include <vector>
#include <cstdint>
#include <base/style/color.hpp>
class c_node;
class c_transition;
enum class e_edge : uint8_t;

class c_transitions_manager
{
public:
    c_node *node;
    int milliseconds = 0;
    c_transitions_manager(c_node *_node);
    ~c_transitions_manager();


    c_transitions_manager &margin(e_edge edge, float value);
    c_transitions_manager &position(e_edge edge, float value);
    c_transitions_manager &background_color(c_color color);
    c_transitions_manager &border_color(c_color color);

    std::vector<c_transition *> _list;
    
};