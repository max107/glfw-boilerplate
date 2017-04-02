#include "OpenCraft.hpp"
#include <iostream>

OpenCraft::OpenCraft(const string & appName, unsigned int width, unsigned int height)
{
    this->appName = appName;
    this->width = width;
    this->height = height;

    LOG(INFO) << "AppVersion: " << version;
}

OpenCraft::~OpenCraft()
{

}

void OpenCraft::changeState(State *state) {
    try {
        state->enter();
    }
    catch (const string & error)
    {
        LOG(ERROR) << error;
        teardown();
        exit(1);
    }
    this->_state = state;
}

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
    
    ImGui::End();
}

void OpenCraft::setup()
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
    
    this->changeState(new LoadingState());
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
    
    ImGui_ImplGlfwGL3_NewFrame();
    debugInfo();
    
    this->_state->render();

    ImGui::Render();
    glfwSwapBuffers(window);
}

void OpenCraft::update()
{
    glfwPollEvents();
}

void OpenCraft::loop()
{
    update();
    this->_state->update();
    renderfps(framerate);
}

void OpenCraft::teardown()
{
    LOG(INFO) << "Cleaning up OpenGL";

    LOG(INFO) << " - Terminating IMGUI";
    ImGui_ImplGlfwGL3_Shutdown();

    LOG(INFO) << " - Terminating GLFW";
    glfwTerminate();
}

bool OpenCraft::isActive()
{
    return glfwWindowShouldClose(window) == 0;
}
