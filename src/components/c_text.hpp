#pragma once
#include <base/node.hpp>
#include <base/secure_string.hpp>


class c_text : public c_node {
public:
    c_font* _font;

    c_text();

    ~c_text();

    void render(BLContext &context) override;

    inline void set_font(c_font* font) { this->_font = font; }

    

    YGNodeRef _inner;

    BLRgba32 color;

    YGNodeRef base;
  
    char8_t local_Str[128];
    size_t str_size;

    std::optional<runtime_secure_string> _string = std::nullopt;

    void set_string(runtime_secure_string string) {
        _string = string;
        YGNodeMarkDirty(node_ref);
        mark_layout_as_dirty();
    }

    void set_raw_string(const char* string) {

        YGNodeMarkDirty(node_ref);
        mark_layout_as_dirty();
    }


    inline void set_color(BLRgba32 color) {
        this->color = color;
    }

    



    static YGSize measure(YGNodeConstRef node,
                          float width,
                          YGMeasureMode widthMode,
                          float height,
                          YGMeasureMode heightMode);
};
