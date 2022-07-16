#include <iostream>
#include <vector>

#include "display_context.h"
#include "widgets/widget.h"
#include "imgui.h"

std::vector<Widget> widgets;

int main()
{

    DisplayContext display_ctx;
    if (auto maybe_ctx = setup_display(); maybe_ctx)
    {
        display_ctx = maybe_ctx.value();
    }
    else
    {
        std::cerr << "Display setup failed" << std::endl;
        return 1;
    }
    std::cout << "display setup finished" << std::endl;

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool showdemo = true;

    while (!glfwWindowShouldClose(display_ctx.window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&showdemo);

        for (const auto &w : widgets)
        {
            w.paint();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(display_ctx.window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(display_ctx.window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(display_ctx.window);
    glfwTerminate();

    return 0;
}