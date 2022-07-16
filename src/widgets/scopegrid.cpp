#include "scopegrid.h"
#include "../imgui/imgui.h"

#include <iostream>

void ScopeGrid::paint() const
{
    ImGui::BeginChild("##data", ImVec2(ImGui::GetContentRegionAvail().x / 2, ImGui::GetContentRegionAvail().y * 20));
    ImGui::PlotLines("", ys.data(), ys.size());
    ImGui::EndChild();
}