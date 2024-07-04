#pragma once

/*
onclick	The user clicks on an element
oncontextmenu	The user right-clicks on an element
ondblclick	The user double-clicks on an element
onmousedown	A mouse button is pressed over an element
onmouseenter	The pointer is moved onto an element
onmouseleave	The pointer is moved out of an element
onmousemove	The pointer is moving over an element
onmouseout	The mouse pointer moves out of an element
onmouseover	The mouse pointer is moved over an element
onmouseup

 **/
enum class e_event_type : uint8_t {
    min,
    mouse,
    keyboard,
    scroll,
    max
};

class c_node_event {
public:
    e_event_type ev_type;

    void stop_propagation() {
        _stop_propagation = true;
    }
    bool _stop_propagation = false;




    template<typename T>
    T* as() {
        return (T*)(this);
    }
};