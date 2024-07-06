#pragma once
#include "transition.hpp"

enum class e_edge : uint8_t;
class c_node;

class c_transition_margin : public c_transition {
public:

    e_edge _edge;
    float old_value = 0.f;
    float new_value = 0.f;
    c_transition_margin(c_node* node, e_edge edge, float new_value, int milliseconds);
    

    void run() override;
};



