#pragma once
#include <functional>
#include <base/state.hpp>

class c_node;

class c_effect {
public:
    c_node* node;
    c_effect(c_node* _node, std::function<void()>  _callback,std::vector<c_state *> _states);
    ~c_effect();
    std::function<void()> callback;
    std::vector<c_state*> states;

};