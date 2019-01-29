cmake_minimum_required(VERSION 3.13)


#set(2D_ONLY on)

project(CrossGameEngine)

set(CMAKE_CXX_STANDARD 17)
#Set preprossessor definitions
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_DEBUG} -DNDEBUG")

if (2D_ONLY)
    add_compile_definitions(NO_3D)
    message("what")
endif (2D_ONLY)

#Check if all the needed package are there
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED)
if (NOT 2D_ONLY)
    find_package(tinyxml2 REQUIRED)
endif ()
#include package include directory
include_directories(${Boost_INCLUDE_DIR})
#Add the include directory
include_directories(include)
#We have to set the freetype directory or else the compiler won't find some needed files
include_directories("/usr/include/freetype2")
#Set the output directory
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(CrossGameEngine
        src/GUI/Button.cpp
        src/GUI/GUIComponent.cpp
        src/GUI/GUIRenderer.cpp
        src/GUI/GUIShader.cpp
        src/GUI/Panel.cpp
        src/IO/Display.cpp
        src/IO/Input.cpp
        src/Loaders/Loader.cpp
        src/Loaders/FileLoader/OBJLoader.cpp
        src/Loaders/RessourceManager.cpp
        src/Loaders/Texture.cpp
        src/Shader/ShaderProgram.cpp
        src/State/StateManager.cpp
        src/Text/TextRenderer.cpp
        src/Text/TextShader.cpp
        src/Utils/FileManager.cpp
        src/Utils/GLDebug.cpp
        src/Utils/TimeUtils.cpp
        src/Engine.cpp
        src/Shader/ModelShader/BasicShader.cpp
        src/extern/stb_image.c
        src/View/Camera.cpp
        src/Loaders/FileLoader/DAELoader.cpp
        src/Loaders/Models/Model.cpp
        src/Loaders/Models/TexturedModel.cpp
        src/Animation/TextureAnimation.cpp
        src/Animation/ModelAnimation.cpp
        src/Loaders/Models/TwoDAnimatedModel.cpp
        src/Animation/Animator.cpp
        src/Utils/XMLElementArrayLoader.cpp
        src/Entities/Entity.cpp)

#Add the testing project
#add_subdirectory(Tester)