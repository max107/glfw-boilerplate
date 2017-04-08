#include "OpenCraft.hpp"

// void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//     std::cout <<"MOUSE POS: " << xpos << ","<< ypos << std::endl;
// }

void OpenCraft::initGL()
{
    LOG(INFO) << "Initialising OpenGL";

    // Initialise GLFW
    LOG(INFO) << "Initialising GLFW";
    if (!glfwInit())
    {
        throw "Failed to initialise GLFW";
    }

    // Create window with GLFW
    LOG(INFO) << " - Creating window with GLFW";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = new Window(this->getConfig());

    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    

    // Initialise GLEW
    LOG(INFO) << " - Initialising GLEW";
    glewExperimental = (GLboolean) true;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw "Failed to initialise GLEW";
    }

    // Set the required callback functions
//    glfwSetWindowUserPointer(window, this);
//    glfwSetWindowFocusCallback(window, &focusEvent);
//    glfwSetKeyCallback(window, &keyCallback);
//    glfwSetCursorPosCallback(window, &mouseMoveCallback);
    
    // not use me glfwSetWindowUserPointer(window, window);

    // Set OpenGL Options
    LOG(INFO) << " - Setting OpenGL Options";
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void OpenCraft::debugInfo() {

}

void OpenCraft::setup()
{
    LOG(INFO) << string(64, '=');
    LOG(INFO) << "Starting up " << this->getConfig().getAppName() << "!";
    LOG(INFO) << string(64, '=');

    try
    {
        initGL();
    }
    catch (const char * error)
    {
        LOG(INFO) << error;
        throw error;
    }
    
    LOG(INFO) << "Set LoadingState";
    this->pushState(new LoadingState());
    this->pushState(new UiState());
}

void OpenCraft::renderfps(unsigned int framerate) 
{ 
    currentTime = glfwGetTime(); 
    if (currentTime - lastTime >= 1.0 / framerate)
    {
        lastTime = currentTime;
        render(); 
    }
}

void OpenCraft::render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (auto& s : states)
    {
        s->render();
    }

    glfwSwapBuffers(this->getWindow()->getGlfwWindow());
}

void OpenCraft::pushState(State *state) {
    // Put in states list
    try {
        LOG(INFO) << "Enter to new state";
        state->enter(this);
    }
    catch (const std::string & error)
    {
        LOG(ERROR) << error;
        throw error;
    }
    
    states.push_back(state);
}

void OpenCraft::update()
{
    glfwPollEvents();
    
    for (auto& s : states)
    {
        s->update();
    }
}

void OpenCraft::run() {
    this->setup();
    
    while (this->getWindow()->isActive()) {
        this->update();
        this->renderfps(this->getConfig().getFramerate());
    }
    
    this->teardown();
}

void OpenCraft::teardown()
{
    for (auto& s : states)
    {
        s->exit(this);
    }

    LOG(INFO) << " - Terminating GLFW";
    glfwTerminate();
}
