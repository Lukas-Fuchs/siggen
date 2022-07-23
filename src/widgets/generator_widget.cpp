#include "generator_widget.h"
#include "../imgui/imgui.h"

void GeneratorWidget::paint() const
{
    ImGui::Combo("##signal type", &current_stype, signal_types, IM_ARRAYSIZE(signal_types));
}