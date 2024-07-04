#pragma once
#include <base/node.hpp>
#include <components/c_text.hpp>
#include <base/secure_string.hpp>
class c_navbutton : public c_node {
public:
    c_navbutton();
    ~c_navbutton();

    void render(BLContext &context) override;
    void on_event(c_node_event *event) override;

    c_text* text = nullptr;


    template<secure_string str>
    constexpr void set_text() {
        if (text)
        text->set_text<str>();
    }

    inline void set_font(BLFont font) {
        if (text)
        text->set_font(font);
    }
    BLRgba32 dots_color = BLRgba32(155, 184, 207, 255);
};
