#include <base/font_face.hpp>

c_font_face::c_font_face(){

};

c_font_face::c_font_face(std::vector<uint8_t> &buffer)
{
    from_memory(buffer);
}
c_font_face::c_font_face(std::string filepath)
{
    from_file(filepath);
}

void c_font_face::from_file(std::string filepath)
{
    _face.createFromFile(filepath.c_str());
}
void c_font_face::from_memory(std::vector<uint8_t> &buffer)
{
      BLFontData fontData;
      BLArray<std::uint8_t> container;
      container.resize(buffer.size(), 0);
      memcpy((void*)container.data(), buffer.data(), buffer.size());

    fontData.createFromData(container);

    _face.createFromData(fontData, 0);
}
