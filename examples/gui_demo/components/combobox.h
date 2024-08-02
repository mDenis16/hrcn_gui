#pragma once
#include <base/base.hpp>

class c_font;
class c_combobox_state : public c_state {
public:
    int value = 0;
};

class c_combobox : public c_node {
public:
    c_combobox(c_font* _font, std::vector<runtime_secure_string> items);
    ~c_combobox();

    c_font* font = nullptr;
    std::vector<runtime_secure_string> _items;
    c_combobox_state state;


    c_node* selector = nullptr;

    void on_click(c_node_event* event);
    void outside_click(c_node_event* event);


    void on_init();

    void select_item(c_node_event* event);
};

