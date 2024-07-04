//
// Created by Denis Topor on 30.06.2024.
//

#include "navbutton.h"
#include <iostream>

#include "../../../../../../Library/Developer/CommandLineTools/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/CoreGraphics.framework/Headers/CGPDFDictionary.h"
#include "base/mouse_event.hpp"


c_navbutton::c_navbutton() {

    style()
    .background_color(BLRgba32(35, 47, 57, 0.7f * 255.f))
    .border_color(BLRgba32(38, 62, 79, 255))
    .height(50)
    .width_percent(100)
    .flex_direction(e_flex_direction::row)
    .margin_auto(e_edge::all)
    .display(e_display::flex);


    YGNodeStyleSetDisplay(node_ref, YGDisplayFlex);
    YGNodeStyleSetJustifyContent(node_ref, YGJustifyCenter);
    YGNodeStyleSetAlignContent(node_ref, YGAlignCenter);


    auto test = new c_node();
    {

        YGNodeStyleSetHeightAuto(test->node_ref);
        YGNodeStyleSetDisplay(test->node_ref, YGDisplayFlex);
        YGNodeStyleSetDisplay(test->node_ref, YGDisplayFlex);
        YGNodeStyleSetJustifyContent(test->node_ref, YGJustifyCenter);
        YGNodeStyleSetAlignContent(test->node_ref, YGAlignCenter);


        text = new c_text();
        text->style().color(BLRgba32(255,255,255, 255));
        test->add_child(text);
    }
    add_child(test);
}
//rgba(35, 47, 57, 0.7)
c_navbutton::~c_navbutton() {

}

void c_navbutton::render(BLContext &context) {

    context.setCompOp(BL_COMP_OP_SRC_OVER);

    BLRgba32 shadowColor(0, 0, 0, 35);

    context.setFillStyle(shadowColor);
    context.fillRoundRect(BLRoundRect(BLRect(box.x, box.y, box.w + 4, box.h + 4), 5, 5));



    c_node::render(context);

    int circle_size = 2;

    context.setFillStyle(dots_color);
    context.fillCircle(box.x + circle_size, box.y + circle_size, circle_size );
    context.fillCircle(box.x + box.w - circle_size, box.y + circle_size, circle_size);
    context.fillCircle(box.x + circle_size, box.y + box.h - circle_size, circle_size);
    context.fillCircle(box.x + box.w - circle_size, box.y + box.h - circle_size, circle_size);


}

void c_navbutton::on_event(c_node_event *event) {
    /* std::cout << "c_navbutton::on_event" << (int)(event->as<c_mouse_event>()->mouse_event_type) << std::endl;

     bg_color = BLRgba32(bg_color.r(), bg_color.g() + 15, bg_color.b(), 255);

     mark_as_dirty();

     event->as<c_mouse_event>()->stop_propagation();*/
}