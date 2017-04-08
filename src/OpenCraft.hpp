#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

#include <imgui.h>
#include "util/imgui_glfw.h"

#include "util/shaderhelper.hpp"
#include "util/colorhelper.hpp"

#include "easylogging++.h"

#include "State.hpp"
#include "LoadingState.hpp"
#include "Config.hpp"
#include "Window.hpp"
#include "StateManager.hpp"

#include <iostream>
#include <memory>
#include <list>

using std::string;

class OpenCraft : public StateManager {
private:   
    // the stack of states
    std::list<State *> states;
    
    Config _config;

    double currentTime;
    double lastTime;

    Window *_window;

    void initGL();
    void update();
    Window * getWindow() { return this->_window; }
    void renderfps(unsigned int framerate);
    void debugInfo();
    void setup();
    
public:
    OpenCraft(Config config) : _config(config) {
    };
    
    Config getConfig() { return this->_config; };
    
    void pushState(State *state);
    
    void run();
    void render();
    void teardown();
};

