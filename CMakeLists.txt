cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(siggen)

get_test_property(${PROJECT_NAME} WORKING_DIRECTORY test_dir)
message("My test's working directory: ${test_dir}")

add_library(IMGUI STATIC)
target_sources(IMGUI
    PRIVATE
        imgui/imgui.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_tables.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_glfw.cpp)

target_include_directories(IMGUI
    PUBLIC
        imgui
        imgui/backends)

        
add_executable(siggen src/main.cpp)
add_dependencies(siggen IMGUI)

target_sources(siggen
    PUBLIC
        src/display_context.cpp)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(siggen PUBLIC glfw)
set(OPENGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
target_link_libraries(siggen PUBLIC OpenGL::GL)
target_link_libraries(siggen PUBLIC IMGUI)
target_include_directories(siggen PUBLIC src widgets imgui)