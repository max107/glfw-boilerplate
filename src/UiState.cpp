//
//  UiState.cpp
//  opencraft
//
//  Created by Максим Фалалеев on 08/04/2017.
//
//

#include "UiState.hpp"

UiState::UiState() {
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
}

void UiState::render() {
    ImGui_ImplGlfwGL3_NewFrame();
    ImGui::Render();
}

void UiState::update() {
    
}

void UiState::enter(OpenCraft *sm) {
    // Setup ImGui binding
    ImGui_ImplGlfwGL3_Init(sm->getWindow()->getGlfwWindow(), true);
    
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

void UiState::exit(OpenCraft *sm) {
    LOG(INFO) << " - Terminating IMGUI";
    ImGui_ImplGlfwGL3_Shutdown();
}
