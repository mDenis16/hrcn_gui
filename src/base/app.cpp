#include <base/app.hpp>
#include <base/app_context.hpp>
#include <base/node.hpp>




c_app::c_app(int width, int height){
    ctx = new c_app_context(width, height);

}

c_app::~c_app()
{
}

 void c_app::set_root(c_node* node){
    node->app_context = ctx;
    node->is_root = true;
    ctx->set_node_root(node);
    node->propagate_context(ctx);
 }