#include "module_widget.h"

#include "imgui.h"
#include "imnodes.h"

void ModuleWidget::paint() const {
  if (!module)
    return;

  ImNodes::GetStyle().NodePadding = ImVec2(5, 0);

  ImNodes::BeginNode(module->id);
  size_t port_id = module->id;
  const auto &dims = module->preferred_dims;

  ImGui::BeginChild("##inputs", ImVec2(30, dims.y));
  for (const auto &input : module->inputs) {
    if (!input.visible)
      continue;
    ImNodes::BeginInputAttribute(input.id);
    ImGui::Text("%s", input.name.c_str());
    ImNodes::EndInputAttribute();
  }
  ImGui::EndChild();

  ImGui::SameLine(0.0f, 0.0f);

  ImGui::BeginChild("##content", ImVec2(dims));
  module->paint();
  ImGui::EndChild();

  ImGui::SameLine(0.0f, 0.0f);

  ImGui::BeginChild("##outputs", ImVec2(30, dims.y));
  for (const auto &output : module->outputs) {
    if (!output.visible)
      continue;
    ImNodes::BeginOutputAttribute(output.id);

    ImGui::Text("%s", output.name.c_str());
    ImNodes::EndOutputAttribute();
  }
  ImGui::EndChild();

  ImNodes::EndNode();
}