#include <base/app.hpp>
#include <base/app_context.hpp>
#include <base/node.hpp>
#include <base/allocator.h>



c_app::c_app(){
    ctx = new c_app_context();

}

c_app::~c_app()
{
}

 void c_app::set_root(c_node* node){
    node->app_context = ctx;
    c_app_context::set_current(ctx);
 }