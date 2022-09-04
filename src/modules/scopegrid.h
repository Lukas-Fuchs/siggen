#pragma once

#include "module.h"

#include <vector>

#include "ringbuffer.h"
#include <imgui_plot.h>

struct ScopeGrid : public Module {
  mutable Ringbuffer<float> ys{100};

  ScopeGrid();

  void setScale(float lower, float upper);
  void setBufferSize(size_t size);

  void paint() const override;
  void calculate() override;

private:
  mutable ImGui::PlotConfig cfg;
};