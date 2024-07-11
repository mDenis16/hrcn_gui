#pragma once
#include "transition.hpp"
#include <blend2d.h>
enum class e_edge : uint8_t;
class c_node;

class c_transition_background_color : public c_transition {
public:

    e_edge _edge;
  
    BLRgba32 old_color;
    BLRgba32 new_color;

    c_transition_background_color(c_node* _node,  BLRgba32 _new_color, int _milliseconds);
    ~c_transition_background_color();


    void run() override;
};



