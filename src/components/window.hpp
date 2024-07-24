#pragma once
#include "../base/node.hpp"
#include <vector>
class c_window : public c_node
{
private:
    /* data */
public:
    c_window(BLSizeI size);
    ~c_window();


    bool _updated = false;
    BLImage texture;

    void render(BLContext& context) override;

    void add_child(c_node * node) override;

    void on_event(c_node_event *event) override;


    void * parent_ref = nullptr;



    std::vector<uint8_t> image_buffer;

    std::vector<uint8_t>& get_image_buffer();




};
