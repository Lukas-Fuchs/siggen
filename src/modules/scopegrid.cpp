#include "scopegrid.h"
#include "imgui.h"

#include "imgraph.h"

#include <iostream>
#include <math.h>

size_t input_idx_cont;
size_t input_idx_bulk;

size_t output_idx_cont;
size_t output_idx_bulk;

ScopeGrid::ScopeGrid() {
  input_idx_cont = inputs.size();
  inputs.emplace_back(Port("cont", 1, 1));
  input_idx_bulk = inputs.size();
  inputs.emplace_back(Port("bulk", 1, 1));

  output_idx_cont = outputs.size();
  outputs.emplace_back(Port("cont", 1, 1));
  output_idx_bulk = outputs.size();
  outputs.emplace_back(Port("bulk", 1, 1));

  ys.resize(100);

  // cfg.grid_x.show = true;
  cfg.grid_y.show = true;
  cfg.scale.min = -100;
  cfg.scale.max = 100;
  cfg.line_thickness = 2.0;
  cfg.values.count = ys.size();
  cfg.values.ys_count = ys.size();
  cfg.tooltip.show = true;
  cfg.tooltip.format = "x=%.2f, y=%.2f";
}

void ScopeGrid::paint() const {
  inputs[input_idx_bulk].visible = inputs[input_idx_cont].connection_count == 0;
  outputs[output_idx_cont].visible = inputs[input_idx_cont].visible;
  inputs[input_idx_cont].visible = inputs[input_idx_bulk].connection_count == 0;
  outputs[output_idx_bulk].visible = inputs[input_idx_bulk].visible;

  cfg.values.ys = ys.data();
  cfg.frame_size = ImVec2(150, 100);
  // ImGui::Plot("", cfg);

  ImGui::GraphSettings settings;
  settings.dimensions = {250, 100};
  settings.max_y = 2.0f;
  settings.min_y = -2.0f;
  settings.offset = ys.offset();
  Graph(settings, {ys.begin(), ys.size()});
}

void ScopeGrid::calculate() {
  auto in_cont = inputs[input_idx_cont].get();
  ys.put(in_cont[0].real());

  static float y = 0;
  outputs[output_idx_cont].put({{ys.back(), 0.0f}});

  outputs[output_idx_bulk].put(inputs[input_idx_bulk].get());
}

void ScopeGrid::setScale(float lower, float upper) {
  cfg.scale.min = lower;
  cfg.scale.max = upper;
}

void ScopeGrid::setBufferSize(size_t size) {
  ys.resize(size);
  cfg.values.ys_count = size;
  cfg.values.count = size;
}