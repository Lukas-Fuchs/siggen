#include "scopegrid.h"
#include "../imgui/imgui.h"

#include <iostream>

ScopeGrid::ScopeGrid(float w, float h)
{
    this->w = w;
    this->h = h;
    cfg.frame_size = ImVec2(w - 30, h - 30);
    cfg.grid_x.show = true;
    cfg.grid_y.show = true;
    cfg.scale.min = -100;
    cfg.scale.max = 100;
    cfg.line_thickness = 2.0;
    cfg.values.ys_count = 1;
    cfg.tooltip.show = true;
    cfg.tooltip.format = "x=%.2f, y=%.2f";
}

void ScopeGrid::paint() const
{
    ImGui::Plot("", cfg);
}

void ScopeGrid::setScale(float lower, float upper)
{
    cfg.scale.min = lower;
    cfg.scale.max = upper;
}

void ScopeGrid::setData(std::vector<float> data)
{
    ys = data;
    cfg.values.ys = ys.data();
    cfg.values.count = ys.size();
}