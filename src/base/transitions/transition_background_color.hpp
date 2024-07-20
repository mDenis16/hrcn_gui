#pragma once
#include "transition.hpp"
#include <base/style/color.hpp>
enum class e_edge : uint8_t;
class c_node;

class c_transition_background_color : public c_transition {
public:

    e_edge _edge;
  
    c_color old_color;
    c_color new_color;

    c_transition_background_color(c_node* _node,  c_color _new_color, int _milliseconds);
    ~c_transition_background_color();


    void run() override;
};



