#pragma once

#include "widget.h"
#include "imgui_plot.h"

#include <vector>

struct ScopeGrid : public Widget
{
    std::vector<float> ys;

    ImGui::PlotConfig cfg;

    ScopeGrid() { ScopeGrid(1000, 500); }
    ScopeGrid(float w, float h);
    void setScale(float lower, float upper);
    void setData(std::vector<float> data);

    void paint() const override;
};