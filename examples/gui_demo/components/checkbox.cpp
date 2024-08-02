//
// Created by Denis Topor on 31.07.2024.
//

#include "checkbox.h"


c_checkbox::c_checkbox() {
    set_debug_descriptor("c_checkbox");
    this->use_state(&state);

    style().background_color(c_color(35, 47, 57, 255 * 0.7)).width(40).height(20)
    .display(e_display::flex).align_items(e_align::center).justify_content(e_justify::center);


    dot = new c_node();
    dot->style()
    .background_color(c_color(62, 108, 137, 255))
    .position_type(e_position::position_type_absolute)
    .position(e_edge::left, 0)
    .width(22).height(22);



    add_child(dot);

    add_event_listener(e_node_event_type::mouse_down_event,std::bind(&c_checkbox::on_click, this, std::placeholders::_1));
}
c_checkbox::~c_checkbox() {

}

void c_checkbox::on_click(c_node_event* event) {
    state.value  = !state.value ;

   //dot->style().background_color(c_color(state.value ? 0 : 255, 0, 255, 255));

    dot->transitions(100).position(e_edge::left, state.value ? (box.w - dot->box.w) : 0);
    state.update();
}