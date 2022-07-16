#include "display_context.h"

#include <iostream>

static void glfw_error_callback(int error, const char *msg)
{
    std::cerr << "GLFW Error " << error << ": " << msg << std::endl;
}

std::optional<DisplayContext> setup_display()
{
    DisplayContext ctx;
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        return std::nullopt;
    }

#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char *glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#else
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    ctx.window = glfwCreateWindow(1280, 720, "siggen", NULL, NULL);
    if (ctx.window == nullptr)
        return std::nullopt;

    glfwMakeContextCurrent(ctx.window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGuiIO &io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(ctx.window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return ctx;
}