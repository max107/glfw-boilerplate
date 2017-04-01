#include "Skeleton.hpp"

Skeleton::Skeleton(const string & appName, unsigned int width, unsigned int height)
{
    this->appName = appName;
    this->width = width;
    this->height = height;
}

Skeleton::~Skeleton()
{

}

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

    // Make window the current OpenGL context
    LOG(INFO) << " - Making window the current OpenGL context";
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, this);
    glfwSetWindowFocusCallback(window, &focusEvent);

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

    // Set OpenGL Options
    LOG(INFO) << " - Setting OpenGL Options";
    glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
}

void Skeleton::drawSkull(glm::vec2 pos, float scale, glm::vec4 colour)
{
    glUniformMatrix4fv(matrixId, 1, GL_FALSE, & mvp[0][0]);

    glUniform2fv(posId, 1, &pos[0]);
    glUniform4fv(colourId, 1, &colour[0]);
    glUniform1f(scaleId, scale);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void *>(0));

    glDrawArrays(GL_TRIANGLES, 0, sizeof(SKULL_VERTICES) / sizeof(GLfloat));

    glDisableVertexAttribArray(0);
}

void Skeleton::debugInfo() {
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    bool showOverlay = true;
    if (!ImGui::Begin("Debug overlay", &showOverlay, ImVec2(0, 0), 0.3f,
                      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                      ImGuiWindowFlags_NoSavedSettings)) {
        ImGui::End();
    }
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::Separator();
    ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    ImGui::End();
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
    scaleId       = glGetUniformLocation(programId, "scale");
    matrixId      = glGetUniformLocation(programId, "mvp");

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
    glm::mat4 model = glm::mat4(1.0f);

    mvp = projection * view * model;

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(SKULL_VERTICES), SKULL_VERTICES, GL_STATIC_DRAW);
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

void Skeleton::focusEvent(GLFWwindow* window, int focused) {
    Skeleton *skeleton = static_cast<Skeleton*>(glfwGetWindowUserPointer(window));
    if (focused) {
        skeleton->framerate = 60;
    } else {
        skeleton->framerate = 30;
    }
}

void Skeleton::render() {
    ImGui_ImplGlfwGL3_NewFrame();
    debugInfo();

    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(programId);

    drawSkull(
        {
            static_cast<float>(width) / 2,
            static_cast<float>(height) / 2
        },
        1.6f,
        colorhelper::rgbaHexToVec4("FFFFFF", 0.4f)
    );

    ImGui::Render();
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Skeleton::loop()
{
    if (framerate > 0) {
        renderfps(framerate);
    } else {
        render();
    }
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
    return glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS
        && glfwWindowShouldClose(window) == 0;
}

const GLfloat Skeleton::SKULL_VERTICES[] =
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
