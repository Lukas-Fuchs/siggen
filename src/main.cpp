#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "display_context.h"
#include "global.h"
#include "imgui.h"
#include "modules/scopegrid.h"
#include "modules/signal_generator.h"
#include "widgets/generator_widget.h"
#include "widgets/module_table.h"
#include "widgets/widget.h"

std::vector<Widget *> widgets;

int main() {
  DisplayContext display_ctx;
  if (auto maybe_ctx = setup_display(); maybe_ctx) {
    display_ctx = maybe_ctx.value();
  } else {
    std::cerr << "Display setup failed" << std::endl;
    return 1;
  }

  int display_w, display_h;
  glfwGetFramebufferSize(display_ctx.window, &display_w, &display_h);

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  widgets.emplace_back(new GeneratorWidget());
  auto mm = std::make_shared<ModuleManager>();
  ModuleTable mt(mm, display_w, float(display_h) / 2);

  auto m0 = std::make_shared<ScopeGrid>();
  m0->setBufferSize(100);
  mm->addModule(m0);

  auto m1 = std::make_shared<ScopeGrid>();
  m1->setBufferSize(1000);
  mm->addModule(m1);

  auto m2 = std::make_shared<SignalGenerator>();
  mm->addModule(m2);

  mt.modules.emplace_back(ModuleWidget(m0));
  mt.modules.emplace_back(ModuleWidget(m1));
  mt.modules.emplace_back(ModuleWidget(m2));
  widgets.emplace_back(&mt);

  unsigned char it_cnt = 0;
  float y = 0;

  global::get_initial_time();

  while (!glfwWindowShouldClose(display_ctx.window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    global::advance_time();
    mm->calculate();
    mm->deliver_messages();
    for (const auto &w : widgets) {
      if (w && w->show) {
        ImGui::SetNextWindowSize(ImVec2(w->w, w->h));
        ImGui::Begin(w->title.c_str());
        w->paint();
        ImGui::End();
      }
    }

    // Rendering
    ImGui::Render();
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                 clear_color.z * clear_color.w, clear_color.w);
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