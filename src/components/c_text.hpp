#pragma once
#include <base/node.hpp>
#include <base/secure_string.hpp>


class c_text : public c_node {
public:
    BLFont font ;

    c_text();

    ~c_text();

    void render(BLContext &context) override;

    inline void set_font(BLFont font) { this->font = font; }


    YGNodeRef _inner;

    BLRgba32 color;

    YGNodeRef base;
    BLGlyphBuffer gb;
    BLGlyphRun gn;
    char8_t local_Str[128];
    size_t str_size;
    template<secure_string str>
    constexpr void set_text() {
        //  memcpy(str, str.get(), str.size());
        for(int i = 0; i < str.size(); i++)
            local_Str[i ] = str.at(i);

        local_Str[str.size()] = '\0';

        str_size = str.size();
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
