#pragma once

class c_node;
class c_app_context;
class c_custom_allocator;

class c_app
{
public:
    c_app_context *ctx = nullptr;
    c_custom_allocator* allocator = nullptr;

    void on_frame();

    c_app(int width, int height);
    ~c_app();

    c_node *root;

    void set_root(c_node *node);

    void process_events();

    
};
