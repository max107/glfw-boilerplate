//
//  GameState.hpp
//  opencraft
//
//  Created by Максим Фалалеев on 03/04/2017.
//
//

#ifndef GameState_hpp
#define GameState_hpp

#include "State.hpp"

class GameState : public State {
public:
    virtual void render();
    virtual void update();
    virtual void enter();
    virtual void exit();
    virtual ~GameState();
};

#endif /* GameState_hpp */
