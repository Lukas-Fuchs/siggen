cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_COMPILER g++-10)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")


project(siggen)

message("Siggen's working directory: ${PROJECT_SOURCE_DIR}")

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
        src/display_context.cpp
        imgui-plot/src/imgui_plot.cpp
        src/widgets/generator_widget.cpp
        src/widgets/module_widget.cpp
        src/widgets/module_table.cpp
        src/modules/module_manager.cpp
        src/modules/scopegrid.cpp
        src/modules/signal_generator.cpp
        imnodes/imnodes.cpp)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)
target_link_libraries(siggen PUBLIC Eigen3::Eigen)
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(siggen PUBLIC glfw)
set(OPENGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
target_link_libraries(siggen PUBLIC OpenGL::GL)
target_link_libraries(siggen PUBLIC IMGUI ${CMAKE_DL_LIBS})
target_include_directories(siggen PUBLIC src src/util src/modules src/widgets eigen imgui imnodes imgui-plot/include)