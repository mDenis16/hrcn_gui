#pragma once
#include <blend2d.h>
#include <string>
#include <vector>
class c_font_face;

class c_font {
public:

    BLFont _font;
    c_font_face* _face;
    c_font(c_font_face* face, float size);


    inline BLFont &get() { return _font; }
};