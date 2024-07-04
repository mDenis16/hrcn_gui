#pragma once
#include "../base/node.hpp"
class c_navbar : public c_node{
public:

    c_navbar();
    ~c_navbar();

    void add_child(c_node *node) override;

    void render(BLContext &context)  override;

    void on_event(c_node_event *event) override;
};