//
//  UiState.hpp
//  opencraft
//
//  Created by Максим Фалалеев on 08/04/2017.
//
//

#ifndef UiState_hpp
#define UiState_hpp

#include "easylogging++.h"

#include <imgui.h>
#include "util/imgui_glfw.h"

#include "State.hpp"

class OpenCraft;

class UiState : public State {
public:
    UiState();
    virtual void render();
    virtual void update();
    virtual void enter(OpenCraft *sm);
    virtual void exit(OpenCraft *sm);
};

#endif /* UiState_hpp */
