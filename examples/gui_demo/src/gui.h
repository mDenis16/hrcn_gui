//
// Created by Denis Topor on 31.07.2024.
//

#ifndef GUI_H
#define GUI_H
#include <vector>


class c_gui {
public:
    c_gui();
    ~c_gui();


    void setup();


    class c_app* app;
    class c_input_context* input_context;


    bool swap_buffer(std::vector<uint8_t>& buff);
    void cursor_callback(int x, int y);
    void keyboard_callback(int key, int scancode, int action);
    void mouse_callback(int button, int action);
    void scroll_callback(float offsetX, float offsetY) ;
};



#endif //GUI_H
