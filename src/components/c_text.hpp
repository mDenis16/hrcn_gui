#pragma once
#include <base/node.hpp>
#include <base/secure_string.hpp>

class c_font;


class c_text : public c_node {
public:
    c_font* _font;

    c_text();

    ~c_text();

    void render(BLContext &context) override;

    inline void set_font(c_font* font) { this->_font = font; }

    
    std::optional<runtime_secure_string> _string = std::nullopt;

    void set_string(runtime_secure_string string) ;
   




    static YGSize measure(YGNodeConstRef node,
                          float width,
                          YGMeasureMode widthMode,
                          float height,
                          YGMeasureMode heightMode);
};
