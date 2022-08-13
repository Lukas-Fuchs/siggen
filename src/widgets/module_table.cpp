#include "module_table.h"
#include "../imgui/imgui.h"
#include "../imnodes/imnodes.h"

#include <iostream>

ModuleTable::ModuleTable(std::shared_ptr<ModuleManager> manager, float width,
                         float height) {
  this->manager = manager;
  w = width;
  h = height;
  title = "Module Editor";
}

void ModuleTable::paint() const {

  int deleted_link;
  if (ImNodes::IsLinkDestroyed(&deleted_link)) {
    const auto conn = manager->connections[deleted_link];
    const auto &src = manager->modules[conn.src];
    const auto &dst = manager->modules[conn.dst];
    size_t src_port = src->outputs[conn.src_port].id;
    size_t dst_port = dst->inputs[conn.dst_port].id;

    manager->disconnect(src_port, dst_port);
  }

  ImNodes::BeginNodeEditor();

  for (const auto &m : modules) {
    m.paint();
  }

  size_t link_id = 0; // Link IDs are local
  for (const auto &conn : manager->connections) {
    const auto &src = manager->modules[conn.src];
    const auto &dst = manager->modules[conn.dst];
    size_t src_port = src->outputs[conn.src_port].id;
    size_t dst_port = dst->inputs[conn.dst_port].id;

    ImNodes::Link(link_id++, src_port, dst_port);
  }

  ImNodes::EndNodeEditor();

  int src, dst;
  if (ImNodes::IsLinkCreated(&src, &dst)) {
    manager->connect(src, dst);
  }

  /*ImGui::BeginTable("modules", modules.size());
  for (size_t x = 0; x < modules.size(); ++x)
  {
      ImGui::PushID(x);
      for (size_t y = 0; y < modules[x].size(); ++y)
      {
          ImGui::PushID(y);
          if (modules[x][y])
          {
              modules[x][y]->paint();
          }
          ImGui::TableNextColumn();
          ImGui::PopID();
      }
      ImGui::TableNextRow();
      ImGui::PopID();
  }
  ImGui::EndTable();*/
}