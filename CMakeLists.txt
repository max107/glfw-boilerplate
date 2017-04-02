#
# Project Properties
#
CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(opencraft)
SET(APPLICATION_NAME "GLFW Skeleton")
SET(APPLICATION_CODENAME "${PROJECT_NAME}")
SET(APPLICATION_COPYRIGHT_YEARS "2014-2016")
SET(APPLICATION_VERSION_MAJOR 4)
SET(APPLICATION_VERSION_MINOR 0)
SET(APPLICATION_VERSION_PATCH 0)
SET(APPLICATION_VERSION_TYPE "RELEASE")
SET(APPLICATION_VERSION_STRING "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}.${APPLICATION_VERSION_PATCH}-${APPLICATION_VERSION_TYPE}")
SET(APPLICATION_ID "${PROJECT_NAME}")

#
# Cmake
#
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${MAINFOLDER}/cmake_modules/")

#
# Debugging Options
#
SET(CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

#
# Project Output Paths
#
SET(MAINFOLDER ${PROJECT_SOURCE_DIR})
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

#
# Project Search Paths
#
LIST(APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
INCLUDE_DIRECTORIES("${MAINFOLDER}/src")

#
# Set compiler warnings
#
SET(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wextra -Werror -Wfloat-equal -Wno-unused-parameter -Wno-unknown-pragmas -Wno-deprecated-declarations -Wno-pessimizing-move")

#
# glfw
#
OPTION(GLFW_BUILD_EXAMPLES  "Build the GLFW example programs"   OFF)
OPTION(GLFW_BUILD_TESTS     "Build the GLFW test programs"      OFF)
OPTION(GLFW_BUILD_DOCS      "Build the GLFW documentation"      OFF)
OPTION(GLFW_INSTALL         "Generate installation target"      OFF)
ADD_SUBDIRECTORY(lib/glfw)
SET(GLFW_INCLUDE_PATH "${MAINFOLDER}/lib/glfw/include")

#
# imgui
#
SET(IMGUI_INCLUDE_PATH "${MAINFOLDER}/lib/imgui")
add_library(
        imgui STATIC
        ${IMGUI_INCLUDE_PATH}/imconfig.h
        ${IMGUI_INCLUDE_PATH}/imgui.cpp
        ${IMGUI_INCLUDE_PATH}/imgui.h
        ${IMGUI_INCLUDE_PATH}/imgui_demo.cpp
        ${IMGUI_INCLUDE_PATH}/imgui_draw.cpp
        ${IMGUI_INCLUDE_PATH}/imgui_internal.h
        ${IMGUI_INCLUDE_PATH}/stb_rect_pack.h
        ${IMGUI_INCLUDE_PATH}/stb_textedit.h
        ${IMGUI_INCLUDE_PATH}/stb_truetype.h
        )

#
# glew
#
OPTION(glew-cmake_BUILD_SHARED "Build the shared glew library" OFF)
ADD_SUBDIRECTORY(lib/glew)
SET(GLEW_INCLUDE_PATH "${MAINFOLDER}/lib/glew/include")

#
# glm
#
SET(GLM_INCLUDE_PATH "${MAINFOLDER}/lib/glm")

#
# EasyLogging++
#
SET(EASYLOGGINGPP_INCLUDE_PATH "${MAINFOLDER}/lib/easyloggingpp/src")

#
# Add project sources
#
ADD_SUBDIRECTORY(src)
