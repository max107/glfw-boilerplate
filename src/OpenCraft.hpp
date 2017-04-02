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
#include "Game.hpp"

#include <iostream>
#include <memory>

using std::string;

class OpenCraft : public Game {
private:
    unsigned int version = 1;

    unsigned int width;
    unsigned int height;
    string appName;

    unsigned int framerate = 60;

    double currentTime;
    double lastTime;
    
    State * _state;

    GLFWwindow * window;

    void initGL();
    void update();

public:
    OpenCraft(const string & appName, unsigned int width, unsigned int height);
    ~OpenCraft();
    
    int getWidth() {
        return width;
    }
    
    int getHeight() {
        return height;
    }

    void debugInfo();
    void setup();
    void render();
    void renderfps(unsigned int framerate);
    void loop();
    void changeState(State *state);
    void teardown();
    bool isActive();
};

