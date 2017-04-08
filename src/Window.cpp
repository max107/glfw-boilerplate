//
//  Window.cpp
//  opencraft
//
//  Created by Максим Фалалеев on 08/04/2017.
//
//

#include "Window.hpp"

Window::Window(Config config) : _config(config) {
    // Make GLFW Window
    // TODO: Control which monitor it goes to and figure out last parameter
    _window = glfwCreateWindow(config.getWidth(), config.getHeight(), config.getAppName().c_str(), NULL, NULL);
    
    // Check that Window opened
    if (_window == nullptr)
    {
        glfwTerminate();
        throw "Failed to create window with GLFW.";
    }
    
    // Make window the current OpenGL context
    LOG(INFO) << " - Making window the current OpenGL context";    
    glfwMakeContextCurrent(_window);
    
    // Disable vsync
    glfwSwapInterval(GLFW_FALSE);
    
    // Set callback for changing window size
    glfwSetWindowSizeCallback(_window, resizeCallback);
    
    // Set mouse mode to be captured
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set mouse position to center
    glfwSetCursorPos(_window, 0, 0);
    
    // Set GLFW Options
    LOG(INFO) << " - Setting GLFW Options";
    glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
}

bool Window::isActive() {
    return glfwWindowShouldClose(this->_window) == 0;
}

void Window::resizeCallback(GLFWwindow *window, int newWidth, int newHeight)
{
    // Change glViewport to new window size
    glViewport(0, 0, newWidth, newHeight);
    
    // Update Perspective Matrix
    // Set the perspective matrix of this window
    // window->projectionMatrix = glm::perspective(90.0f, float(newWidth / newHeight), 0.0f, 100.0f);
}

Window::~Window() {
    // Destroy window in GLFW
    glfwDestroyWindow(_window);
}
