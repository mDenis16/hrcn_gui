#pragma once
#include <blend2d.h>
#include <string>
#include <vector>

class c_font_face
{
public:
    BLFontFace _face;

    c_font_face();
    c_font_face(std::vector<uint8_t> &buffer);
    c_font_face(std::string filepath);

    void from_file(std::string filepath);
    void from_memory(std::vector<uint8_t> &buffer);

    inline BLFontFace &get() { return _face; }
};