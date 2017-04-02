//
//  State.hpp
//  opencraft
//
//  Created by Максим Фалалеев on 02/04/2017.
//
//

#ifndef State_hpp
#define State_hpp

class State {
    
public:
    virtual void enter() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void exit() = 0;
    virtual ~State() {}
    
};

#endif /* State_hpp */
