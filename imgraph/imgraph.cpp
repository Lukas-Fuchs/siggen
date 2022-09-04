#include "imgraph.h"
#include "imgui.h"
#include "imgui_internal.h"

namespace ImGui {

void Graph(GraphSettings& settings, const std::span<float>& ys){
    auto* window = ImGui::GetCurrentWindow();

    // No need to draw here
    if(!window || window->SkipItems) return;

    ImRect clip(window->DC.CursorPos, window->DC.CursorPos + settings.dimensions);
    ItemAdd(clip, 0);

    RenderFrame(clip.Min, clip.Max, true);
}

}