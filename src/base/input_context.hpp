#pragma once
#include <components/window.hpp>

class c_input_context {
public:
    c_window* window;
    c_input_context(c_window* _window);

    BLPointI cursor;



    ~c_input_context();
    void cursor_callback(int x, int y);

    void keyboard_callback(int key, int scancode, int action);

    void mouse_callback(int button, int action);

    void scroll_callback(float offsetX, float offsetY) ;
};


