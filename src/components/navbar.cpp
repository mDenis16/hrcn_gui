//
// Created by Denis Topor on 30.06.2024.
//
#include "navbar.hpp"
#include <iostream>

c_navbar::c_navbar() {
    YGNodeStyleSetWidth(node_ref, 232);
    YGNodeStyleSetHeightPercent(node_ref, 100);
    YGNodeStyleSetDisplay(node_ref, YGDisplayFlex);
    YGNodeStyleSetGap(node_ref, YGGutterRow, 20);

    YGNodeStyleSetFlexDirection(node_ref, YGFlexDirectionColumn);
    bg_color = BLRgba32(17, 27, 34, 0.85f * 255.f);
    border_color = BLRgba32(255, 27, 34, 0.85f * 255.f);
}

c_navbar::~c_navbar() {

}

void c_navbar::add_child(c_node* node) {
    c_node::add_child(node);
}

void c_navbar::render(BLContext &context) {
    c_node::render(context);


  
}

void c_navbar::on_event(c_node_event *event) {
    std::cout << "c_navbar::on_event " << std::endl;
}