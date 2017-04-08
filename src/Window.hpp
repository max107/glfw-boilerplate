//
//  Window.hpp
//  opencraft
//
//  Created by Максим Фалалеев on 08/04/2017.
//
//

#ifndef Window_hpp
#define Window_hpp

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "easylogging++.h"

#include "Config.hpp"

class Window {
public:
    Window(Config config);
    ~Window();
    bool isActive();
    GLFWwindow* getGlfwWindow() { return this->_window; }
    
private:
    Config _config;
    GLFWwindow *_window;
    static void resizeCallback(GLFWwindow *window, int newWidth, int newHeight);
};

#endif /* Window_hpp */
