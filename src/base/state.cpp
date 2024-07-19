#include <base/state.hpp>
#include <base/node.hpp>
#include <base/effect.hpp>

c_state::c_state(){

}
c_state::~c_state(){
    
}
void c_state::consume_update(){
    std::cout << "Consume state update " << std::endl;

    for(auto& effect : _effects) {
        if ( effect->callback)
        effect->callback();
    }

    _update  = false;
}