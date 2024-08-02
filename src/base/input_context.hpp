#pragma once
#include <blend2d.h>
#include <mutex>
#include <deque>

class c_node_event;
class c_input_context {
public:
    c_input_context();

    BLPointI cursor;



    ~c_input_context();
    void cursor_callback(int x, int y);

    void keyboard_callback(int key, int scancode, int action);

    void mouse_callback(int button, int action);

    void scroll_callback(float offsetX, float offsetY) ;


    void process_events();

    std::deque<c_node_event*> _node_events;
    std::mutex _node_events_mutex;
    
};


