#include "signal_generator.h"

#include "global.h"
#include "imgui.h"
#include <cmath>

void SignalGenerator::paint() const {
  switch (type) {
  case SignalType::Sin:
    ImGui::InputFloat("amplitude", &amplitude);
    ImGui::InputFloat("frequency", &sin_frequency);
    ImGui::InputFloat("phase", &sin_phase);
    break;
  case SignalType::Chirp:
    break;
  case SignalType::Rect:
    break;
  }
}

void SignalGenerator::calculate() {
  double t = double(global::get_time()) / 1'000'000;
  outputs[0].put({{amplitude * std::sin(sin_frequency * (t + sin_phase) * M_PI_2), 0.0f}});
}