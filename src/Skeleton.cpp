#include "Skeleton.hpp"
#include <iostream>

Skeleton::Skeleton(const string & appName, unsigned int width, unsigned int height)
{
    this->appName = appName;
    this->width = width;
    this->height = height;

    LOG(INFO) << "AppVersion: " << version;
}

Skeleton::~Skeleton()
{

}

// void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//     std::cout <<"MOUSE POS: " << xpos << ","<< ypos << std::endl;
// }

void Skeleton::initGL()
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

    window = glfwCreateWindow(
        width, 
        height, 
        appName.c_str(), 
        nullptr, // glfwGetPrimaryMonitor(), 
        nullptr
    );

    if (window == nullptr)
    {
        glfwTerminate();
        throw "Failed to create window with GLFW.";
    }

    // glfwSetCursorPosCallback(window, mouse_callback);
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Make window the current OpenGL context
    LOG(INFO) << " - Making window the current OpenGL context";
    glfwMakeContextCurrent(window);

    glfwSwapInterval(GLFW_FALSE);

    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(window, true);

    // Apply imgui skin
    ImGuiStyle &style = ImGui::GetStyle();

    style.WindowPadding = ImVec2(8, 8);
    style.WindowRounding = 2.0f;
    style.ChildWindowRounding = 2.0f;
    style.FramePadding = ImVec2(5, 5);
    style.FrameRounding = 2.0f;
    style.ItemSpacing = ImVec2(8, 10);
    style.ItemInnerSpacing = ImVec2(8, 10);
    style.IndentSpacing = 15.0f;
    style.ScrollbarSize = 15.0f;
    style.ScrollbarRounding = 2.0f;
    style.GrabMinSize = 10.0f;
    style.GrabRounding = 2.0f;

    style.Colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.59f, 0.59f, 0.59f, 0.78f);
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.04f, 0.04f, 0.04f, 0.94f);
    style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.27f, 0.27f, 0.27f, 0.84f);
    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.20f);
    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.25f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.44f, 1.00f);
    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 1.00f, 0.75f);
    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.59f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 0.67f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 0.39f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.59f, 1.00f, 0.88f);
    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.59f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.67f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.39f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.59f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.67f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.39f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.00f, 0.59f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.59f, 1.00f, 0.20f);
    style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.67f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.00f, 0.39f, 1.00f, 1.00f);
    style.Colors[ImGuiCol_CloseButton] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(1.00f, 0.39f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(1.00f, 0.23f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 1.00f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.93f, 0.31f, 0.00f, 1.00f);
    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.59f, 1.00f, 0.43f);
    style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

    // Load imgui font
    ImGuiIO &io = ImGui::GetIO();
    // io.Fonts->AddFontDefault();
    io.Fonts->AddFontFromFileTTF("assets/font.ttf", 16.0f);

    // Initialise GLEW
    LOG(INFO) << " - Initialising GLEW";
    glewExperimental = (GLboolean) true;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        throw "Failed to initialise GLEW";
    }

    // Set GLFW Options
    LOG(INFO) << " - Setting GLFW Options";
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set the required callback functions
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowFocusCallback(window, &focusEvent);
    glfwSetKeyCallback(window, &keyCallback);
    glfwSetCursorPosCallback(window, &mouseMoveCallback);
    // glfwSetWindowUserPointer(window, window);

    // Set OpenGL Options
    LOG(INFO) << " - Setting OpenGL Options";
    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void Skeleton::debugInfo() {
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    bool showOverlay = true;
    if (!ImGui::Begin("Debug overlay", &showOverlay, ImVec2(0, 0), 0.8f,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                      ImGuiWindowFlags_NoSavedSettings)) {
        ImGui::End();
    }
    
    ImGui::Text("FPS %.3f ms/frame (%.1f FPS)", 
        1000.0f / ImGui::GetIO().Framerate,
        ImGui::GetIO().Framerate);
    
    // ImGui::Text("Mouse: (%.1f,%.1f)", 
    //     ImGui::GetIO().MousePos.x, 
    //     ImGui::GetIO().MousePos.y);
    
    ImGui::Text("Mouse: (%.1f,%.1f)", 
        xpos, 
        ImGui::GetIO().MousePos.y);
    
    ImGui::Text("Angle: (%.1f,%.1f,%.1f)", 
        angle.x, 
        angle.y,
        angle.z);
    
    ImGui::Text("Up: (%.1f,%.1f,%.1f)", 
        up.x, 
        up.y,
        up.z);
    
    ImGui::Text("Forward: (%.1f,%.1f,%.1f)", 
        forward.x, 
        forward.y,
        forward.z);
    
    ImGui::Text("Right: (%.1f,%.1f,%.1f)", 
        right.x, 
        right.y,
        right.z);
    
    ImGui::Text("Lookat: (%.1f,%.1f,%.1f)", 
        lookat.x, 
        lookat.y,
        lookat.z);
    
    ImGui::Text("Position: (%.1f,%.1f,%.1f)", 
        position.x, 
        position.y,
        position.z);
    
    ImGui::End();
}

void Skeleton::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    Skeleton *skeleton = static_cast<Skeleton*>(glfwGetWindowUserPointer(window));

    static const float mousespeed = 0.001;

    skeleton->xpos = xpos;
    skeleton->ypos = ypos;
    
    skeleton->angle.x -= xpos * mousespeed;
    skeleton->angle.y -= ypos * mousespeed;

    if (skeleton->angle.x < -M_PI) {
        skeleton->angle.x += M_PI * 2;
    }

    if (skeleton->angle.x > M_PI) {
        skeleton->angle.x -= M_PI * 2;
    }

    if (skeleton->angle.y < -M_PI / 2) {
        skeleton->angle.y = -M_PI / 2;
    }

    if (skeleton->angle.y > M_PI / 2) {
        skeleton->angle.y = M_PI / 2;
    }

    skeleton->updateVectors();
}

void Skeleton::updateVectors() {
    // Calculate the forward, right and lookat vectors from the angle vector
    forward.x = sinf(angle.x);
    forward.y = 0;
    forward.z = cosf(angle.x);

    right.x = -cosf(angle.x);
    right.y = 0;
    right.z = sinf(angle.x);

    lookat.x = sinf(angle.x) * cosf(angle.y);
    lookat.y = sinf(angle.y);
    lookat.z = cosf(angle.x) * cosf(angle.y);

    up = glm::cross(right, lookat);
}

void Skeleton::setup()
{
    LOG(INFO) << string(64, '=');
    LOG(INFO) << "Starting up " << appName << "!";
    LOG(INFO) << string(64, '=');

    try
    {
        initGL();
    }
    catch (const char * error)
    {
        LOG(INFO) << error;
        exit(-1);
    }

    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    try {
        programId = shaderhelper::createProgram("shaders/2dcolor.vert", "shaders/2dcolor.frag");
    } 
    catch (const string & error) 
    {
        LOG(ERROR) << error;
        teardown();
        exit(-1);
    }

    posId         = glGetUniformLocation(programId, "position");
    colourId      = glGetUniformLocation(programId, "color");
    matrixId      = glGetUniformLocation(programId, "mvp");

    position = glm::vec3(0, CY + 1, 0);
    angle = glm::vec3(0, -0.5, 0);
    updateVectors();

    glm::mat4 projection = glm::perspective(
        45.0f, 
        1.0f * static_cast<float>(width) / static_cast<float>(height), 
        0.01f, 
        1000.0f);

    /*
    glm::mat4 projection = glm::ortho(
        0.f,  static_cast<float>(width),
        0.f,  static_cast<float>(height),
        0.0f, 1.0f
    );
    glm::mat4 view = glm::lookAt(
        glm::vec3(0, 0, 1),
        glm::vec3(0, 0, 0),
        glm::vec3(0, 1, 0)
    );
    */

    glm::mat4 view = glm::lookAt(position, position + lookat, up);

    mvp = projection * view;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SKULL_VERTICES), SKULL_VERTICES, GL_STATIC_DRAW);

    glEnable(GL_DEPTH_TEST); // Depth Testing
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Skeleton::renderfps(unsigned int framerate) 
{ 
    currentTime = glfwGetTime(); 
    if (currentTime - lastTime >= 1.0 / framerate) 
    {
        lastTime = currentTime;
        render(); 
    }
}

void Skeleton::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Skeleton *skeleton = static_cast<Skeleton*>(glfwGetWindowUserPointer(window));

    float speed = 10.f;

    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_A) {
            skeleton->position -= skeleton->right * speed;
        }
        
        if (key == GLFW_KEY_D) {
            skeleton->position += skeleton->right * speed;
        }
        
        if (key == GLFW_KEY_W) {
            skeleton->position += skeleton->forward * speed;
        }
        
        if (key == GLFW_KEY_S) {
            skeleton->position -= skeleton->forward * speed;
        }
        
        /*
        if (key == GLFW_KEY_SPACE) {
            skeleton->position.y += speed;
        }

        if (key == GLFW_KEY_CTRL) {
            skeleton->position.y -= speed;
        }
        */
    }

    std::cout << "Key: " << key << std::endl;
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

void Skeleton::focusEvent(GLFWwindow* window, int focused) {
    Skeleton *skeleton = static_cast<Skeleton*>(glfwGetWindowUserPointer(window));
    if (focused) {
        skeleton->framerate = skeleton->defaultFramerate;
    } else {
        skeleton->framerate = skeleton->unfocusFramerate;
    }
}

void Skeleton::drawCube()
{
    GLfloat vertices[] =
    {
        -1, -1, -1,   -1, -1,  1,   -1,  1,  1,   -1,  1, -1,
        1, -1, -1,    1, -1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1, -1,  1,    1, -1,  1,    1, -1, -1,
        -1,  1, -1,   -1,  1,  1,    1,  1,  1,    1,  1, -1,
        -1, -1, -1,   -1,  1, -1,    1,  1, -1,    1, -1, -1,
        -1, -1,  1,   -1,  1,  1,    1,  1,  1,    1, -1,  1
    };

    GLfloat colors[] =
    {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
        0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
        0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
    };

    static float alpha = 0;
    //attempt to rotate cube
    glRotatef(alpha, 0, 1, 0);

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, 24);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    alpha += 1;
}

void Skeleton::drawLogo(glm::vec2 pos, glm::vec4 colour)
{
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

    glUniform2fv(posId, 1, &pos[0]);
    glUniform4fv(colourId, 1, &colour[0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));
    glDrawArrays(GL_TRIANGLES, 0, sizeof(SKULL_VERTICES) / sizeof(GLfloat));

    glDisableVertexAttribArray(0);
}

void Skeleton::render() {
    ImGui_ImplGlfwGL3_NewFrame();
    debugInfo();
    // glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(mvp));
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glUseProgram(programId);

    glViewport(0, 0, width, height);
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION_MATRIX);
    glLoadIdentity();
    gluPerspective( 60, (double)width / (double)height, 0.1, 100 );
    glMatrixMode(GL_MODELVIEW_MATRIX);
    glTranslatef(0,0,-5);
    drawCube();

    /*
    drawLogo(
        { 
            static_cast<float>(width) / 2, 
            static_cast<float>(height) / 2 
        },
        colorhelper::rgbaHexToVec4("000000", 0.4f)
    );
    */

    /*
    drawCube();
    */

    ImGui::Render();
    glfwSwapBuffers(window);
}

void Skeleton::loop()
{
    glfwPollEvents();
    renderfps(framerate);
}

void Skeleton::teardown()
{
    LOG(INFO) << "Cleaning up OpenGL";

    LOG(INFO) << " - Deleting OpenGL resources";
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programId);
    glDeleteVertexArrays(1, &vertexArrayId);

    LOG(INFO) << " - Terminating IMGUI";
    ImGui_ImplGlfwGL3_Shutdown();

    LOG(INFO) << " - Terminating GLFW";
    glfwTerminate();
}

bool Skeleton::isActive()
{
    return glfwWindowShouldClose(window) == 0;
}
