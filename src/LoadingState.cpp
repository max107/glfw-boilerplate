//
//  LoadingState.cpp
//  opencraft
//
//  Created by Максим Фалалеев on 02/04/2017.
//
//

#include "LoadingState.hpp"

void LoadingState::enter(OpenCraft *sm) {
    LOG(INFO) << "Loading State:";
    LOG(INFO) << " - Enter";
    
    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);
    
    programId = shaderhelper::createProgram("shaders/loading.vert", "shaders/loading.frag");

    posId         = glGetUniformLocation(programId, "position");
    colourId      = glGetUniformLocation(programId, "color");
    matrixId      = glGetUniformLocation(programId, "mvp");
    scaleId       = glGetUniformLocation(programId, "scale");

    glm::mat4 projection = glm::ortho(
        0.f,  static_cast<float>(800),
        0.f,  static_cast<float>(600),
        0.0f, 1.0f
    );
    glm::mat4 view = glm::lookAt(
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    glm::mat4 model = glm::mat4(1.0f);

    mvp = projection * view * model;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SKULL_VERTICES), SKULL_VERTICES, GL_STATIC_DRAW);
    
    colour = colorhelper::rgbaHexToVec4("FFFFFF", 0.4f);
    pos = {
        static_cast<float>(800) / 2,
        static_cast<float>(600) / 2
    };
}

void LoadingState::render() {
    glUseProgram(programId);
    
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, & mvp[0][0]);
    
    glUniform2fv(posId, 1, &pos[0]);
    glUniform4fv(colourId, 1, &colour[0]);
    glUniform1f(scaleId, _scale);
    
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));
    
    glDrawArrays(GL_TRIANGLES, 0, sizeof(SKULL_VERTICES) / sizeof(GLfloat));
    
    glDisableVertexAttribArray(0);
}

void LoadingState::update() {
    // todo: do something for complete loading state
    if (_up) {
        _scale += _delta;
        if (_scale >= 2.f) {
            _up = false;
        }
    } else {
        _scale -= _delta;
        if (_scale <= 1.f) {
            _up = true;
        }
    }
}

void LoadingState::exit(OpenCraft *sm) {
    LOG(INFO) << " - Deleting OpenGL resources";
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programId);
    glDeleteVertexArrays(1, &vertexArrayId);
}
