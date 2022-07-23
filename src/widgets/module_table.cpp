#include "module_table.h"
#include "../imgui/imgui.h"
#include "../imnodes/imnodes.h"

ModuleTable::ModuleTable(float width, float height)
{
    w = width;
    h = height;
    title = "Module Editor";
}

void ModuleTable::paint() const
{
    ImNodes::BeginNodeEditor();
    
    ImNodes::BeginNode(1337);
    ImGui::Dummy(ImVec2(80.0f, 45.0f));
    ImNodes::EndNode();

    ImNodes::EndNodeEditor();
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