//
//  LoadingState.hpp
//  opencraft
//
//  Created by Максим Фалалеев on 02/04/2017.
//
//

#ifndef LoadingState_hpp
#define LoadingState_hpp

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "State.hpp"
#include "util/colorhelper.hpp"
#include "util/shaderhelper.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OpenCraft.hpp"
#include <iostream>
#include "StateManager.hpp"

class LoadingState : public State {
public:
    virtual void enter(StateManager *state);
    virtual void render();
    virtual void update();
    virtual void exit(StateManager *state);
    virtual ~LoadingState();

private:
	GLint posId;
    GLint colourId;
    GLint matrixId;
    GLuint vertexbuffer;
    GLuint vertexArrayId;
    GLuint programId;

    glm::mat4 mvp;
    
    glm::vec4 colour;
    glm::vec2 pos;
};

const GLfloat SKULL_VERTICES[84] =
{
    // top of skull
    60, 50,
    60,  0,
    -60,  0,
    -60, 50,
    60, 50,
    -60,  0,
    
    // left of eyes
    -60,   0,
    -40,   0,
    -60, -30,
    -60, -30,
    -40,   0,
    -40, -30,
    
    // centre of eyes
    -10,   0,
    10,   0,
    -10, -30,
    -10, -30,
    10,   0,
    10, -30,
    
    // right of eyes
    60,   0,
    40,   0,
    60, -30,
    60, -30,
    40,   0,
    40, -30,
    
    // left of nose
    -60, -30,
    0, -30,
    -10, -40,
    -10, -40,
    -60, -40,
    -60, -30,
    
    // right of nose
    0, -30,
    60, -30,
    10, -40,
    10, -40,
    60, -30,
    60, -40,
    
    // jaw
    -30, -40,
    30, -40,
    -30, -55,
    -30, -55,
    30, -40,
    30, -55,
};

#endif /* LoadingState_hpp */
