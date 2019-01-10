project(CGETester)

include_directories(../include)

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

add_executable(CGETester
        src/Main.cpp
        src/States/PlayingState.h
        src/States/PlayingState.cpp
        )

#Link the CGE to the tester
target_link_libraries(CGETester CrossGameEngine)

#target_link_libraries(GameEngineTester glm)
target_link_libraries(CGETester glfw GL freetype)

add_custom_command(TARGET CGETester PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/Tester/res $<TARGET_FILE_DIR:CGETester>/res)