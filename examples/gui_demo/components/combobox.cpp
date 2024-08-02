
#include "combobox.h"

#include <base/app_context.hpp>
#include <components/c_text.hpp>


c_combobox::c_combobox(c_font* _font, std::vector<runtime_secure_string> items) {
    set_debug_descriptor("c_combobox");
    _items = items;
    font = _font;

    style()
    .border_color(c_color(0,255,255,255))
    .background_color(c_color(255, 47, 57, 255)).width(200).height(60)
    .display(e_display::flex).align_items(e_align::center).justify_content(e_justify::center);

    bind_init(std::bind(&c_combobox::on_init, this));
}

c_combobox::~c_combobox() {

}

void c_combobox::outside_click(c_node_event* event) {
    if (!selector) return;

    std::cout << "outside_click clicked " << std::endl;
    event->stop_propagation();

    selector->safe_destroy();
    selector = nullptr;
}
void c_combobox::on_click(c_node_event* event) {

    if (selector) {
        return;
    }

    selector = new c_node();

    selector->style()
    .position_type(e_position::position_type_absolute)
    .width_percent(100)
    .height(100)
    .z_index(1)
    .overflow_hidden()
    .background_color(c_color(0,255,0,255));

    for(auto item : _items) {
        auto combo_item = new c_node();


        combo_item->add_event_listener(e_node_event_type::mouse_down_event, std::bind(&c_combobox::select_item, this, std::placeholders::_1));
        {
            auto item_text = new c_text();
            item_text->set_string(item);
            item_text->style().color(c_color(255,255,255,255));
            item_text->set_font(font);
            combo_item->add_child(item_text);
        }
        combo_item->style()
        .justify_content(e_justify::center)
        .align_items(e_align::center)
        .height(40).width_percent(100).border_color(c_color(0,0,255, 255));
        selector->add_child(combo_item);


    }


    auto root = app_context->get_node_by_hash<"Root">();

    assert(root);

    root->add_event_listener(e_node_event_type::mouse_down_event, std::bind(&c_combobox::outside_click, this, std::placeholders::_1));



    add_child(selector);
}

void c_combobox::on_init() {
    add_event_listener(e_node_event_type::mouse_down_event,std::bind(&c_combobox::on_click, this, std::placeholders::_1));
}

void c_combobox::select_item(c_node_event* event) {
    auto node = event->target;

    selector->safe_destroy();
    selector = nullptr;
    event->stop_propagation();



    std::cout << "c_combobox::select_item clicked " << std::endl;
}