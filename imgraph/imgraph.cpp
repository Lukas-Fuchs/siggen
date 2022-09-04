#include "imgraph.h"

#include <algorithm>

#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif

#include "imgui.h"
#include "imgui_internal.h"

namespace ImGui {

ImVec2 lerp_point(const float x, const float y, const ImRect bb) {
  int x_lerp = ImLerp(bb.Min.x, bb.Max.x, x);
  int y_lerp = ImLerp(bb.Min.y, bb.Max.y, y);
  return {x_lerp, y_lerp};
}

void Graph(GraphSettings &settings, const std::span<float> &ys) {
  auto *window = ImGui::GetCurrentWindow();

  // No need to draw here
  if (!window || window->SkipItems)
    return;

  ImRect clip(window->DC.CursorPos, window->DC.CursorPos + settings.dimensions);
  ItemAdd(clip, 0);

  RenderFrame(clip.Min, clip.Max, true);

  // Draw data
  const auto y0 = (std::clamp(ys[settings.offset % ys.size()], settings.min_y,
                              settings.max_y) -
                   settings.min_y) /
                  (settings.max_y - settings.min_y);

  auto p0 = lerp_point(0.0f, y0, clip);
  for (size_t i = 0; i < ys.size(); ++i) {
    const auto y = (std::clamp(ys[(i + settings.offset) % ys.size()],
                               settings.min_y, settings.max_y) -
                    settings.min_y) /
                   (settings.max_y - settings.min_y);
    const auto p1 = lerp_point(float(i) / ys.size(), y, clip);

    window->DrawList->AddLine(p0, p1, IM_COL32(200, 200, 0, 255));
    p0 = p1;
  }
}

} // namespace ImGui