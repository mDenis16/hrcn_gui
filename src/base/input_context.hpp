#pragma once
#include <components/window.hpp>

class c_input_context {
public:
    c_window* window;
    c_input_context(c_window* _window);
    ~c_input_context();
    void cursor_callback(int x, int y);
};

