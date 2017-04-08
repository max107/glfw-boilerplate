//
//  State.hpp
//  opencraft
//
//  Created by Максим Фалалеев on 02/04/2017.
//
//

#ifndef State_hpp
#define State_hpp

class OpenCraft;

class State {
    
public:
    virtual void enter(OpenCraft *sm) = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void exit(OpenCraft *sm) = 0;
    
};

#endif /* State_hpp */
