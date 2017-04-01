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

#include <iostream>
#include <memory>

#include "World.h"
#include "skull.hpp"

using std::string;

class Skeleton {
private:
    unsigned int version = 1;

    unsigned int width;
    unsigned int height;
    string appName;

    // FPS limits
    unsigned int defaultFramerate = 60;
    unsigned int unfocusFramerate = 30;
    unsigned int framerate = 60;

    double currentTime;
    double lastTime;

    GLFWwindow * window;

    GLint posId;
    GLint colourId;
    GLint matrixId;
    GLuint vertexbuffer;
    GLuint vertexArrayId;
    GLuint programId;

    glm::mat4 mvp;

    double xpos, ypos;

    glm::vec3 up;
    glm::vec3 lookat;
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 angle;

    void initGL();
    void drawLogo(glm::vec2 pos, glm::vec4 colour);
    void drawCube();

public:
    Skeleton(const string & appName, unsigned int width, unsigned int height);
    ~Skeleton();

    void debugInfo();
    void setup();
    void render();
    void renderfps(unsigned int framerate);
    void loop();
    void teardown();
    bool isActive();
    void updateVectors();

    // GLFW
    static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void focusEvent(GLFWwindow* window, int focused);
};

