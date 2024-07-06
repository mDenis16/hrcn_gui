
#pragma once
#include <iostream>
#include <chrono>

class c_node;
enum class e_transition_type : uint8_t;

class c_transition {
public:

    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
    std::chrono::time_point<std::chrono::high_resolution_clock> _end;

    e_transition_type type;
    bool executed = false;

    c_node* node = nullptr;


    c_transition(c_node* _node, int milliseconds);
    
    ~c_transition() {

    }

    virtual  void run()  =0;
};
