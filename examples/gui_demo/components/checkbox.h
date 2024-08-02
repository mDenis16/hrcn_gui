#pragma once

#include <base/base.hpp>

class c_checkbox_state : public c_state {
public:
    bool value = false;
};

class c_checkbox : public c_node {
public:
    c_checkbox();
    ~c_checkbox();

    c_checkbox_state state;


    c_node* dot;



    void on_click(c_node_event* event);

};


