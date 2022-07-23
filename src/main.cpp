#include <iostream>
#include <vector>
#include <cmath>

#include "display_context.h"
#include "widgets/widget.h"
#include "widgets/scopegrid.h"
#include "widgets/generator_widget.h"
#include "widgets/module_table.h"
#include "imgui.h"

std::vector<Widget *> widgets;

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

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    bool showdemo = true;

    ScopeGrid scope(500, 200);
    scope.setData({1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89});
    widgets.emplace_back(&scope);
    widgets[0]->title = "test";
    widgets.emplace_back(new GeneratorWidget());
    widgets.emplace_back(new ModuleTable());

    unsigned char it_cnt = 0;
    float y = 0;

    while (!glfwWindowShouldClose(display_ctx.window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&showdemo);

        for (const auto &w : widgets)
        {
            if (w && w->show)
            {
                ImGui::SetNextWindowSize(ImVec2(w->w, w->h));
                ImGui::Begin(w->title.c_str());
                w->paint();
                ImGui::End();
            }
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
    ImNodes::DestroyContext();
    ImGui::DestroyContext();

    glfwDestroyWindow(display_ctx.window);
    glfwTerminate();

    return 0;
}