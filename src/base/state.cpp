#include <base/state.hpp>
#include <base/node.hpp>
#include <base/effect.hpp>

c_state::c_state(){

}
c_state::~c_state(){
    
}
void c_state::consume_update(){
    std::cout << "Consume state update " << std::endl;
    if ( effect->callback){
    effect->callback();
    }
    else{
        std::cout << "callback is empty " << std::endl;
    }
    _update  = false;
}