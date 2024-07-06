#pragma once
class c_node;
class c_transitions_manager {
public:
    c_node* node;
    c_transitions_manager(c_node* _node);
    ~c_transitions_manager();
};