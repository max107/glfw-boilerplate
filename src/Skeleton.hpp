#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include "util/imgui_glfw.h"

#include "util/shaderhelper.hpp"
#include "util/colorhelper.hpp"

#include "easylogging++.h"

#include <iostream>
#include <memory>

using std::string;

class Skeleton {
private:
    static constexpr int SKULL_COMPONENT_COUNT = 7 * 2 * 3 * 2;
    static const GLfloat SKULL_VERTICES[SKULL_COMPONENT_COUNT];

    unsigned int width;
    unsigned int height;
    unsigned int framerate;
    string appName;

    double currentTime;
    double lastTime;

    GLFWwindow * window;

    GLint posId;
    GLint colourId;
    GLint scaleId;
    GLint matrixId;
    GLuint vertexbuffer;
    GLuint vertexArrayId;
    GLuint programId;

    glm::mat4 mvp;

    void initGL();
    void drawSkull(glm::vec2 pos, float scale, glm::vec4 colour);

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

    // GLFW
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void focusEvent(GLFWwindow* window, int focused);
};

