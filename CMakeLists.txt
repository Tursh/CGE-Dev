cmake_minimum_required(VERSION 3.13)

project(CrossGameEngine)

option(BUILD_SHARED_LIBS "Compile CGE as a shared library" OFF)
option(CompileTest "Compile the test project" OFF)

set(CMAKE_CXX_STANDARD 17)

#Check if all the needed package are there
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
find_package(Freetype REQUIRED)
find_package(GLEW REQUIRED)
find_package(tinyxml2 REQUIRED)
find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLEWSTATIC -DGLEW_BUILD -static-libstdc++ -static-libgcc -static")
    link_libraries(opengl32 bz2)
endif ()

#Add the include directory
include_directories(include)
#We have to set the freetype directory or else the compiler won't find some needed files
include_directories("/usr/include/freetype2")

if (BUILD_SHARED_LIBS)
    set(LIBRARY_TYPE SHARED)

    if (NOT WIN32)
        set(LIBRARIES_LOCATION "/usr/local/lib64")

        link_libraries(
                "${LIBRARIES_LOCATION}/libglfw3.a"
                "${LIBRARIES_LOCATION}/libGLEW.a"
                "${LIBRARIES_LOCATION}/libfreetype.a"
                "${LIBRARIES_LOCATION}/libtinyxml2.a"
                pthread
        )
    else ()
        set(LIBRARIES_LOCATION "/usr/i686-w64-mingw32")


        link_libraries(
                "${LIBRARIES_LOCATION}/lib/libglfw3.a"
                "${LIBRARIES_LOCATION}/lib/libglew32.a"
                "${LIBRARIES_LOCATION}/lib/libfreetype.a"
                "${LIBRARIES_LOCATION}/bin/libbz2-1.dll"
                "${LIBRARIES_LOCATION}/bin/libtinyxml2.dll"
                "${LIBRARIES_LOCATION}/lib/libwinpthread.a"
                "${LIBRARIES_LOCATION}/lib/libopengl32.a"
                "${LIBRARIES_LOCATION}/lib/libpng.a"
                "${LIBRARIES_LOCATION}/lib/libz.a"
                "${LIBRARIES_LOCATION}/lib/libpthread.a"
        )
        link_libraries()
    endif ()

else ()
    set(LIBRARY_TYPE STATIC)
endif ()

add_library(CrossGameEngine ${LIBRARY_TYPE}
        src/GUI/Button.cpp
        src/GUI/GUIComponent.cpp
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
        src/Entities/Entity.cpp src/GUI/GUIManager.cpp include/GUI/GUIManager.h)

#Add the testing project
if (${CompileTest})
    add_subdirectory(test)
endif ()