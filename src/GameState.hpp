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
#include "StateManager.hpp"

class GameState : public State {
public:
    virtual void render();
    virtual void update();
    virtual void enter(StateManager *sm);
    virtual void exit(StateManager *sm);
    virtual ~GameState();
};

#endif /* GameState_hpp */
